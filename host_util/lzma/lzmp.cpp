/*
 * LZMA command line tool similar to gzip to encode and decode LZMA files.
 *
 * Copyright (C) 2005 Ville Koskinen
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */

#include "Common/MyInitGuid.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>
using std::string;
#include <vector>
using std::vector;
typedef vector<string> stringVector;

#include <unistd.h>
#include <getopt.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>
#include <sys/time.h> // futimes()

// For Solaris
#ifndef HAVE_FUTIMES
//#define futimes(fd, tv) futimesat(fd, NULL, tv)
#endif

#if defined(_WIN32) || defined(OS2) || defined(MSDOS)
#include <fcntl.h>
#include <io.h>
#define MY_SET_BINARY_MODE(file) setmode(fileno(file),O_BINARY)
#else
#define MY_SET_BINARY_MODE(file)
#endif

#include "FileStreams.h"

#include "Common/Types.h"

#include "LzmaDecoder.h"
#include "LzmaEncoder.h"

#include "Exception.h"

#include "lzma_version.h"

namespace lzma {

const char *PROGRAM_VERSION = PACKAGE_VERSION;
const char *PROGRAM_COPYRIGHT = "Copyright (C) 2006 Ville Koskinen";

/* LZMA_Alone switches:
    -a{N}:  set compression mode - [0, 2], default: 2 (max)
    -d{N}:  set dictionary - [0,28], default: 23 (8MB)
    -fb{N}: set number of fast bytes - [5, 255], default: 128
    -lc{N}: set number of literal context bits - [0, 8], default: 3
    -lp{N}: set number of literal pos bits - [0, 4], default: 0
    -pb{N}: set number of pos bits - [0, 4], default: 2
    -mf{MF_ID}: set Match Finder: [bt2, bt3, bt4, bt4b, pat2r, pat2,
                pat2h, pat3h, pat4h, hc3, hc4], default: bt4
*/

struct lzma_option {
	short compression_mode;			// -a
	short dictionary;			// -d
	short fast_bytes;			// -fb
	wchar_t *match_finder;			// -mf
	short literal_context_bits;		// -lc
	short literal_pos_bits;			// -lp
	short pos_bits;				// -pb
};

/* The following is a mapping from gzip/bzip2 style -1 .. -9 compression modes
 * to the corresponding LZMA compression modes. Thanks, Larhzu, for coining
 * these. */
const lzma_option option_mapping[] = {
	{ 0,  0,  0,    NULL, 0, 0, 0},		// -0 (needed for indexing)
	{ 0, 16, 64,  L"hc4", 3, 0, 2},		// -1
	{ 0, 20, 64,  L"hc4", 3, 0, 2},		// -2
	{ 1, 19, 64,  L"bt4", 3, 0, 2},		// -3
	{ 2, 20, 64,  L"bt4", 3, 0, 2},		// -4
	{ 2, 21, 128, L"bt4", 3, 0, 2},		// -5
	{ 2, 22, 128, L"bt4", 3, 0, 2},		// -6
	{ 2, 23, 128, L"bt4", 3, 0, 2},		// -7
	{ 2, 24, 255, L"bt4", 3, 0, 2},		// -8
	{ 2, 25, 255, L"bt4", 3, 0, 2},		// -9
};

struct extension_pair {
	char *from;
	char *to;
};

const extension_pair known_extensions[] = {
	{ ".lzma", "" },
	{ ".tlz", ".tar" },
	{ NULL, NULL }
};

/* Sorry, I just happen to like enumerations. */
enum PROGRAM_MODE {
	PM_COMPRESS = 0,
	PM_DECOMPRESS,
	PM_TEST,
	PM_HELP,
	PM_LICENSE,
	PM_VERSION
};

enum {
	STATUS_OK = 0,
	STATUS_ERROR = 1,
	STATUS_WARNING = 2
};

/* getopt options. */
/* struct option { name, has_arg, flag, val } */
const struct option long_options[] = {
	{ "stdout", 0, 0, 'c' },
	{ "decompress", 0, 0, 'd' },
	{ "compress", 0, 0, 'z' },
	{ "keep", 0, 0, 'k' },
	{ "force", 0, 0, 'f' },
	{ "test", 0, 0, 't' },
	{ "suffix", 1, 0, 'S' },
	{ "quiet", 0, 0, 'q' },
	{ "verbose", 0, 0, 'v' },
	{ "help", 0, 0, 'h' },
	{ "license", 0, 0, 'L' },
	{ "version", 0, 0, 'V' },
	{ "fast", 0, 0, '1' },
	{ "best", 0, 0, '9' },
	{ 0, 0, 0, 0 }
};

/* getopt option string (for the above options). */
const char option_string[] = "cdzkftS:qvhLV123456789A:D:F:";

/* Defaults. */
PROGRAM_MODE program_mode = PM_COMPRESS;
int	verbosity			= 0;
bool	stdinput			= false;
bool	stdoutput			= false;
bool	keep				= false;
bool	force				= false;
int	compression_mode		= 7;
//char	*suffix				= strdup(".lzma");
char	*suffix				= strdup(known_extensions[0].from);
lzma_option	advanced_options 	= { -1, -1, -1, NULL, -1, -1, -1 };

void print_help(const char *const argv0)
{
	// Help goes to stdout while other messages go to stderr.
	cout << "\nlzma " << PROGRAM_VERSION
		<< " " << PROGRAM_COPYRIGHT << "\n"
		"Based on LZMA SDK " << LZMA_SDK_VERSION_STRING << " "
		<< LZMA_SDK_COPYRIGHT_STRING
		<< "\n\nUsage: " << argv0
		<< " [flags and input files in any order]\n"
"  -c --stdout       output to standard output\n"
"  -d --decompress   force decompression\n"
"  -z --compress     force compression\n"
"  -k --keep         keep (don't delete) input files\n"
"  -f --force        force overwrite of output file and compress links\n"
"  -t --test         test compressed file integrity\n"
"  -S .suf  --suffix .suf   use suffix .suf on compressed files\n"
"  -q --quiet        suppress error messages\n"
"  -v --verbose      be verbose\n"
"  -h --help         print this message\n"
"  -L --license      display the license information\n"
"  -V --version      display version numbers of LZMA SDK and lzma\n"
"  -1 .. -2          fast compression\n"
"  -3 .. -9          good to excellent compression. -7 is the default.\n"
"     --fast         alias for -1\n"
"     --best         alias for -9 (usually *not* what you want)\n\n"
"  Memory usage depends a lot on the chosen compression mode -1 .. -9.\n"
"  See the man page lzma(1) for details.\n\n";
}

void print_license(void)
{
	cout << "\n  LZMA command line tool " << PROGRAM_VERSION << " - "
		<< PROGRAM_COPYRIGHT
		<< "\n  LZMA SDK " << LZMA_SDK_VERSION_STRING << " - "
		<< LZMA_SDK_COPYRIGHT_STRING
		<< "\n  This program is a part of the LZMA utils package.\n"
		"  http://tukaani.org/lzma/\n\n"
"  This program is free software; you can redistribute it and/or\n"
"  modify it under the terms of the GNU General Public License\n"
"  as published by the Free Software Foundation; either version 2\n"
"  of the License, or (at your option) any later version.\n"
"\n"
"  This program is distributed in the hope that it will be useful,\n"
"  but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"  GNU General Public License for more details.\n"
"\n";
}

void print_version(void)
{
	cout << "LZMA command line tool " << PROGRAM_VERSION << "\n"
		<< "LZMA SDK " << LZMA_SDK_VERSION_STRING << "\n";
}

short str2int (const char *str, const int &min, const int &max)
{
	int value = -1;
	char *endptr = NULL;
	if (str == NULL || str[0] == '\0')
		throw ArgumentException("Invalid integer option");
	value = strtol (str, &endptr, 10);
	if (*endptr != '\0' || value < min || value > max)
		throw ArgumentException("Invalid integer option");
	return value;
}

void parse_options(int argc, char **argv, stringVector &filenames)
{
	/* Snatched from getopt(3). */
	int c;

	/* Check how we were called */
	{
		char *p = strrchr (argv[0], '/'); // Remove path prefix, if any
		if (p++ == NULL)
			p = argv[0];
		if (strstr (p, "un") != NULL) {
			program_mode = PM_DECOMPRESS;
		} else if (strstr (p, "cat") != NULL) {
			program_mode = PM_DECOMPRESS;
			stdoutput = true;
		}
	}

	while (-1 != (c = getopt_long(argc, argv, option_string,
			long_options, NULL))) {
		switch (c) {
			// stdout
			case 'c':
				stdoutput = true;
				break;

			// decompress
			case 'd':
				program_mode = PM_DECOMPRESS;
				break;

			// compress
			case 'z':
				program_mode = PM_COMPRESS;
				break;

			// keep
			case 'k':
				keep = true;
				break;

			// force
			case 'f':
				force = true;
				break;

			// test
			case 't':
				program_mode = PM_TEST;
				break;

			// suffix
			case 'S':
				if (optarg) {
					free(suffix);
					suffix = strdup(optarg);
				}
				break;

			// quiet
			case 'q':
				verbosity = 0;
				break;

			// verbose
			case 'v':
				verbosity++;
				break;

			// help
			case 'h':
				program_mode = PM_HELP;
				break;

			// license
			case 'L':
				program_mode = PM_LICENSE;
				break;

			// version
			case 'V':
				program_mode = PM_VERSION;
				break;

			case '1': case '2': case '3': case '4': case '5':
			case '6': case '7': case '8': case '9':
				compression_mode = c - '0';
				break;

			// Advanced options //
			// Compression mode
			case 'A':
				advanced_options.compression_mode =
						str2int (optarg, 0, 2);
				break;

			// Dictionary size
			case 'D':
				advanced_options.dictionary =
						str2int (optarg, 0, 28);
				break;

			// Fast bytes
			case 'F':
				advanced_options.fast_bytes =
						str2int (optarg, 0, 273);
				break;

			default:
				throw ArgumentException("");
				break;
		} // switch(c)
	} // while(1)

	for (int i = optind; i < argc; i++) {
		if (strcmp("-", argv[i]) == 0)
			continue;
		filenames.push_back(argv[i]);
	}
} // parse_options

void set_encoder_properties(NCompress::NLzma::CEncoder *encoder,
		lzma_option &opt)
{
	/* Almost verbatim from LzmaAlone.cpp. */
	    PROPID propIDs[] =
	{
		NCoderPropID::kDictionarySize,
		NCoderPropID::kPosStateBits,
		NCoderPropID::kLitContextBits,
		NCoderPropID::kLitPosBits,
		NCoderPropID::kAlgorithm,
		NCoderPropID::kNumFastBytes,
		NCoderPropID::kMatchFinder,
		NCoderPropID::kEndMarker
	};
	const int kNumProps = sizeof(propIDs) / sizeof(propIDs[0]);
#define VALUE(x) (advanced_options.x >= 0 ? advanced_options.x : opt.x)
	PROPVARIANT properties[kNumProps];
	for (int p = 0; p < 6; p++)
		properties[p].vt = VT_UI4;
	properties[0].ulVal = UInt32(1 << VALUE (dictionary));
	properties[1].ulVal = UInt32(VALUE (pos_bits));
	properties[2].ulVal = UInt32(VALUE (literal_context_bits));
	properties[3].ulVal = UInt32(VALUE (literal_pos_bits));
	properties[4].ulVal = UInt32(VALUE (compression_mode));
	properties[5].ulVal = UInt32(VALUE (fast_bytes));
#undef VALUE

	properties[6].vt = VT_BSTR;
	properties[6].bstrVal = (BSTR)opt.match_finder;

	properties[7].vt = VT_BOOL;
	properties[7].boolVal = stdinput ? VARIANT_TRUE : VARIANT_FALSE;

	if (encoder->SetCoderProperties(propIDs, properties, kNumProps) != S_OK)
		throw Exception("SetCoderProperties() error");
}

void encode(NCompress::NLzma::CEncoder *encoderSpec,
		CMyComPtr<ISequentialInStream> inStream,
		CMyComPtr<ISequentialOutStream> outStream,
		lzma_option encoder_options,
		UInt64 fileSize)
{
	set_encoder_properties(encoderSpec, encoder_options);

	encoderSpec->WriteCoderProperties(outStream);

	for (int i = 0; i < 8; i++)
	{
		Byte b = Byte(fileSize >> (8 * i));
		if (outStream->Write(&b, sizeof(b), 0) != S_OK)
			throw Exception("Write error while encoding");
	}

	HRESULT result = encoderSpec->Code(inStream, outStream, 0, 0, 0);

	if (result == E_OUTOFMEMORY)
		throw Exception("Cannot allocate memory");
	else if (result != S_OK) {
		char buffer[33];
		snprintf(buffer, 33, "%d", (unsigned int)result);
		throw Exception(string("Encoder error: ") + buffer);
	}
}

void decode(NCompress::NLzma::CDecoder *decoderSpec,
		CMyComPtr<ISequentialInStream> inStream,
		CMyComPtr<ISequentialOutStream> outStream)
{
	const UInt32 kPropertiesSize = 5;
	Byte properties[kPropertiesSize];
	UInt32 processedSize;
	UInt64 fileSize = 0;

	if (inStream->Read(properties, kPropertiesSize, &processedSize) != S_OK)
		throw Exception("Read error");
	if (processedSize != kPropertiesSize)
		throw Exception("Read error");
	if (decoderSpec->SetDecoderProperties2(properties, kPropertiesSize) != S_OK)
		throw Exception("SetDecoderProperties() error");

	for (int i = 0; i < 8; i++)
	{
		Byte b;

		if (inStream->Read(&b, sizeof(b), &processedSize) != S_OK)
			throw Exception("Read error");
		if (processedSize != 1)
			throw Exception("Read error");

		fileSize |= ((UInt64)b) << (8 * i);
	}

	if (decoderSpec->Code(inStream, outStream, 0, &fileSize, 0) != S_OK)
		throw Exception("Decoder error");
}

int open_instream(const string infile,
		CMyComPtr<ISequentialInStream> &inStream,
		UInt64 &fileSize)
{
	CInFileStream *inStreamSpec = new CInFileStream;
	inStream = inStreamSpec;
	if (!inStreamSpec->Open(infile.c_str()))
		throw Exception("Cannot open input file " + infile);

	inStreamSpec->File.GetLength(fileSize);

	return inStreamSpec->File.GetHandle();
}

int open_outstream(const string outfile,
		CMyComPtr<ISequentialOutStream> &outStream)
{
	COutFileStream *outStreamSpec = new COutFileStream;
	outStream = outStreamSpec;

	bool open_by_force = (program_mode == PM_TEST) | force;

	if (!outStreamSpec->Create(outfile.c_str(), open_by_force))
		throw Exception("Cannot open output file " + outfile);

	return outStreamSpec->File.GetHandle();
}

double get_ratio(int inhandle, int outhandle)
{
	struct stat in_stats, out_stats;
	fstat(inhandle, &in_stats);
	fstat(outhandle, &out_stats);

	return (double)out_stats.st_size / (double)in_stats.st_size;
}

mode_t get_file_mode(string filename)
{
	struct stat in_stat;
	lstat(filename.c_str(), &in_stat);

	return in_stat.st_mode;
}

bool string_ends_with(string str, string ending)
{
	return equal(ending.rbegin(), ending.rend(), str.rbegin());
}

bool extension_is_known(string filename)
{
	bool known_format = false;
	extension_pair extension; int i = 1;

	extension = known_extensions[0];
	while (extension.from != NULL) {
		if (string_ends_with(filename, extension.from)) {
			known_format = true;
			break;
		}
		extension = known_extensions[i];
		i++;
	}

	if (!known_format) {
		if (!string_ends_with(filename, suffix)) {
			return false;
		}
	}

	return true;
}

string replace_extension(string filename)
{
	int suffix_starts_at = filename.length() - strlen (suffix);
	string from_suffix = filename.substr(suffix_starts_at, strlen (suffix));
	string ret = filename.substr(0, suffix_starts_at);
	extension_pair extension; int i = 1;

	extension = known_extensions[0];
	while (extension.from != NULL) {
		if (from_suffix.compare(extension.from) == 0) {
			ret += extension.to;
			break;
		}

		extension = known_extensions[i];
		i++;
	}

	return ret;
}

string pretty_print_status(string filename, string output_filename,
		string ratio)
{
	string ret = "";

	ret += filename;
	ret += ":\t ";

	if (program_mode == PM_TEST) {
		ret += "decoded succesfully";

		return ret;
	}

	if (!stdinput && !stdoutput) {
		ret += ratio;
		ret += " -- ";
	}

	if (program_mode == PM_COMPRESS) {
		if (keep) {
			ret += "encoded succesfully";

			return ret;
		}

		ret += "replaced with ";
		ret += output_filename;

		return ret;
	}

	if (program_mode == PM_DECOMPRESS) {
		if (keep) {
			ret += "decoded succesfully";

			return ret;
		}

		ret += "replaced with ";
		ret += output_filename;

		return ret;
	}

	return ret;
}

static string archive_name; // I know, it is crude, but I haven't found any other
    // way then making a global variable to transfer filename to handler

void signal_handler (int signum)
{
    unlink (archive_name.c_str()); // deleting
    signal (signum, SIG_DFL); // we return the default function to used signal
    kill (getpid(), signum); // and then send this signal to the process again
}

} // namespace lzma


int main(int argc, char **argv)
{
	using namespace lzma;
	using std::cerr;

	stringVector filenames;

	signal (SIGTERM,signal_handler);
	signal (SIGHUP,signal_handler);
	signal (SIGINT,signal_handler);

	try {
		parse_options(argc, argv, filenames);
	}
	catch (...) {
		return STATUS_ERROR;
	}

	if (program_mode == PM_HELP) {
		print_help(argv[0]);
		return STATUS_OK;
	}
	else if (program_mode == PM_LICENSE) {
		print_license();
		return STATUS_OK;
	}
	else if (program_mode == PM_VERSION) {
		print_version();
		return STATUS_OK;
	}

	if (filenames.empty()) {
		stdinput = true;
		stdoutput = true;

		/* FIXME: get rid of this */
		filenames.push_back("-");
	}

	/* Protection: always create new files with 0600 in order to prevent
	 * outsiders from reading incomplete data. */
	umask(0077);

	bool warning = false;

	for (int i = 0; i < (int)filenames.size(); i++) {
		CMyComPtr<ISequentialInStream> inStream;
		CMyComPtr<ISequentialOutStream> outStream;
		UInt64 fileSize = 0;
		int inhandle = 0, outhandle = 0;
		string output_filename;

		if (stdinput) {
			inStream = new CStdInFileStream;
			MY_SET_BINARY_MODE(stdin);
			fileSize = (UInt64)(Int64)-1;

			inhandle = STDIN_FILENO;

			outStream = new CStdOutFileStream;
			MY_SET_BINARY_MODE(stdout);

			outhandle = STDOUT_FILENO;
		}
		else {
			mode_t infile_mode = get_file_mode(filenames[i]);
			if (!S_ISREG(infile_mode)) {
				if (S_ISDIR(infile_mode)) {
					warning = true;
					cerr << argv[0] << ": " << filenames[i] << ": "
						<< "cowardly refusing to work on directory"
						<< endl;

					continue;
				}
				else if (S_ISLNK(infile_mode)) {
					if (!stdoutput && !force) {
						warning = true;

					cerr << argv[0] << ": " << filenames[i] << ": "
							<< "cowardly refusing to work on symbolic link "
							<< "(use --force to force encoding or decoding)"
							<< endl;

						continue;
					}
				}
				else {
					warning = true;

					cerr << argv[0] << ": " << filenames[i] << ": "
						<< "doesn't exist or is not a regular file"
						<< endl;

					continue;
				}
			}

			// Test if the file already ends with *suffix.
			if (program_mode == PM_COMPRESS && !force
					&& string_ends_with(filenames[i],
						suffix)) {
				warning = true;

				cerr << filenames[i] << " already has "
					<< suffix << " suffix -- unchanged\n";

				continue;
			}

			// Test if the file extension is known.
			if (program_mode == PM_DECOMPRESS
					&& !extension_is_known(filenames[i])) {
				warning = true;

				cerr << filenames[i] << ": "
					<< " unknown suffix -- unchanged"
					<< endl;

				continue;
			}

			try {
				inhandle = open_instream(filenames[i], inStream, fileSize);
			}
			catch (Exception e) {
				cerr << argv[0] << ": " << e.what() << endl;
				return STATUS_ERROR;
			}

			if (stdoutput) {
				outStream = new CStdOutFileStream;
				MY_SET_BINARY_MODE(stdout);

				outhandle = STDOUT_FILENO;
			}
			else {
				/* Testing mode is nothing else but decoding
				 * and throwing away the result. */
				if (program_mode == PM_TEST)
					output_filename = "/dev/null";
				else if (program_mode == PM_DECOMPRESS)
					output_filename = replace_extension(filenames[i]);
				else
					output_filename = filenames[i]
							+ suffix;
				archive_name = output_filename;

				try {
					outhandle = open_outstream(output_filename, outStream);
				}
				catch (Exception e) {
					cerr << argv[0] << ": " << e.what() << endl;
					return STATUS_ERROR;
				}
			}

		}

		// Unless --force is specified, do not read/write compressed
		// data from/to a terminal.
		if (!force) {
			if (program_mode == PM_COMPRESS && isatty(outhandle)) {
				cerr << argv[0] << ": compressed data not "
					"written to a terminal. Use "
					"-f to force compression.\n"
					<< argv[0] << ": For help, type: "
					<< argv[0] << " -h\n";
				return STATUS_ERROR;
			} else if (program_mode == PM_DECOMPRESS
					&& isatty(inhandle)) {
				cerr << argv[0] << ": compressed data not "
					"read from a terminal. Use "
					"-f to force decompression.\n"
					<< argv[0] << ": For help, type: "
					<< argv[0] << " -h\n";
				return STATUS_ERROR;
			}
		}

		if (program_mode == PM_COMPRESS) {
			    NCompress::NLzma::CEncoder *encoderSpec =
				      new NCompress::NLzma::CEncoder;

			lzma_option options = option_mapping[compression_mode];

			try {
				encode(encoderSpec, inStream, outStream, options, fileSize);
			}
			catch (Exception e) {
				cerr << argv[0] << ": " << e.what() << endl;
				unlink(output_filename.c_str());
				delete(encoderSpec);

				return STATUS_ERROR;
			}

			delete(encoderSpec);
		}
		else {			// PM_DECOMPRESS | PM_TEST
		    NCompress::NLzma::CDecoder *decoderSpec =
		        new NCompress::NLzma::CDecoder;

			try {
				decode(decoderSpec, inStream, outStream);
			}
			catch (Exception e) {
				cerr << argv[0] << ": " << e.what() << endl;
				unlink(output_filename.c_str());
				delete(decoderSpec);

				return STATUS_ERROR;
			}

			delete(decoderSpec);
		}

		/* Set permissions and owners. */
		if ( (program_mode == PM_COMPRESS || program_mode == PM_DECOMPRESS )
				&& (!stdinput && !stdoutput) ) {

			int ret = 0;
			struct stat file_stats;
			ret = fstat(inhandle, &file_stats);

			ret = fchmod(outhandle, file_stats.st_mode);
			ret = fchown(outhandle, file_stats.st_uid, file_stats.st_gid);
			// We need to call fchmod() again, since otherwise the SUID bits
			// are lost.
			ret = fchmod(outhandle, file_stats.st_mode);

			struct timeval file_times[2];
			// Access time
			file_times[0].tv_sec = file_stats.st_atime;
			file_times[0].tv_usec = 0;
			// Modification time
			file_times[1].tv_sec = file_stats.st_mtime;
			file_times[1].tv_usec = 0;

			ret = futimes(outhandle, file_times);

			if (!keep)
				unlink(filenames[i].c_str());
		}

		if (verbosity > 0) {
			if (stdoutput) {
				cerr << filenames[i] << ":\t ";
				cerr << "decoded succesfully"
					<< endl;
			}

			else {
				char buf[10] = { 0 };

				if (program_mode == PM_DECOMPRESS)
					snprintf(buf, 10, "%.2f%%",
							(1 - get_ratio(outhandle, inhandle)) * 100);
				if (program_mode == PM_COMPRESS)
					snprintf(buf, 10, "%.2f%%",
							(1 - get_ratio(inhandle, outhandle)) * 100);

				string ratio = buf;
				cerr << pretty_print_status(filenames[i], output_filename,
						ratio)
					<< endl;
			}
		}
	}

	if (warning)
		return STATUS_WARNING;

	return STATUS_OK;
}

