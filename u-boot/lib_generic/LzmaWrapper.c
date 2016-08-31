/******************************************************************************
**
** FILE NAME    : LzmaWrapper.c
** PROJECT      : bootloader
** MODULES      : U-boot
**
** DATE         : 2 Nov 2006
** AUTHOR       : Lin Mars
** DESCRIPTION  : LZMA decoder support for U-boot 1.1.5
** COPYRIGHT    :       Copyright (c) 2006
**                      Infineon Technologies AG
**                      Am Campeon 1-12, 85579 Neubiberg, Germany
**
**    This program is free software; you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation; either version 2 of the License, or
**    (at your option) any later version.
**
** HISTORY
** $Date        $Author         $Comment
** 2 Nov 2006   Lin Mars        init version which derived from LzmaTest.c from
**                              LZMA v4.43 SDK
*******************************************************************************/
#include <config.h>
#include <common.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <malloc.h>

#ifdef CONFIG_LZMA

#include "LzmaDecode.h"
#include "LzmaWrapper.h"

static int MyReadFileAndCheck(unsigned char *src,
			      void *dest,
			      size_t size,
			      size_t *rpos)
{
	if (size == 0)
		return 0;

	memcpy(dest, src + *rpos, size);
	*rpos += size;

	return 1;
}

int lzma_inflate(unsigned char *source,
		 int s_len,
		 unsigned char *dest,
		 int *d_len)
{
	/*
	 * We use two 32-bit integers to construct 64-bit integer for file size.
	 * You can remove outSizeHigh, if you don't need >= 4GB supporting,
	 * or you can use UInt64 outSize, if your compiler supports 64-bit integers
	 */
	unsigned char *outStream;
	UInt32 outSize = 0;
	SizeT outSizeFull;

	size_t rpos = 0;

	/*
	 * waitEOS = 1, if there is no uncompressed size in headers,
	 * so decoder will wait EOS (End of Stream Marker) in compressed stream
	 */
	int waitEOS = 1;

	SizeT compressedSize;
	unsigned char *inStream;

	/* It's about 24-80 bytes structure, if int is 32-bit */
	CLzmaDecoderState state;
	unsigned char properties[LZMA_PROPERTIES_SIZE];

	int res;

	compressedSize = (SizeT)(s_len - (LZMA_PROPERTIES_SIZE + 8));

	/* Read LZMA properties for compressed stream */
	if (!MyReadFileAndCheck(source, properties,
				sizeof(properties), &rpos)) {
		return LZMA_RESULT_DATA_ERROR;
	}

	/* Read uncompressed size */
	int i;
	for (i = 0; i < 8; i++) {
		unsigned char b;

		if (!MyReadFileAndCheck(source, &b, 1, &rpos))
			return LZMA_RESULT_DATA_ERROR;

		if (b != 0xFF)
			waitEOS = 0;

		if (i < 4)
			outSize += (UInt32)(b) << (i * 8);
	}

	if (waitEOS)
		return LZMA_RESULT_DATA_ERROR;

	outSizeFull = (SizeT)outSize;

	if ((UInt32)(SizeT)outSize != outSize)
		return LZMA_RESULT_DATA_ERROR;

	/* Decode LZMA properties and allocate memory */
	if (LzmaDecodeProperties(&state.Properties, properties,
				 LZMA_PROPERTIES_SIZE) != LZMA_RESULT_OK)
		return LZMA_RESULT_DATA_ERROR;

	state.Probs = (CProb *)malloc(LzmaGetNumProbs(&state.Properties)
				      * sizeof(CProb));

	if (outSizeFull == 0) {
		outStream = 0;
	} else {
		if (outSizeFull > (int)d_len)
			outStream = 0;
		else
			outStream = dest;
	}

	if (compressedSize == 0) {
		inStream = 0;
	} else {
		if ((compressedSize + rpos) > s_len )
			inStream = 0;
		else
			inStream = source + rpos;
	}

	if (state.Probs == 0 ||
	    (outStream == 0 && outSizeFull != 0) ||
	    (inStream == 0 && compressedSize != 0)) {
		free(state.Probs);
		return LZMA_RESULT_DATA_ERROR;
	}

	/* Decompress */
	SizeT inProcessed;
	SizeT outProcessed;

	res = LzmaDecode(&state, inStream, compressedSize, &inProcessed,
			 outStream, outSizeFull, &outProcessed);
	if (res != 0)
		res = 1;
	else
		*d_len = outProcessed;

	free(state.Probs);

	return res;
}

#endif /* CONFIG_LZMA */
