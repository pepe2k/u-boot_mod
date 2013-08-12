#include <common.h>
#include <exports.h>

DECLARE_GLOBAL_DATA_PTR;

static void dummy(void){
}

unsigned long get_version(void){
	return(XF_VERSION);
}

void jumptable_init(void){
	int i;

	gd->jt = (void **)malloc(XF_MAX * sizeof(void *));

	for(i = 0; i < XF_MAX; i++){
		gd->jt[i] = (void *)dummy;
	}

	gd->jt[XF_get_version] = (void *)get_version;
	gd->jt[XF_malloc] = (void *)malloc;
	gd->jt[XF_free] = (void *)free;
	gd->jt[XF_get_timer] = (void *)get_timer;
	gd->jt[XF_udelay] = (void *)udelay;
}
