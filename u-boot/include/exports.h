#ifndef __EXPORTS_H__
#define __EXPORTS_H__

#ifndef __ASSEMBLY__

#include <common.h>

/* These are declarations of exported functions available in C code */
unsigned long	get_version(void);
int				getc(void);
int				tstc(void);
void			putc(const char);
void			puts(const char*);
void			printf(const char* fmt, ...);
void			install_hdlr(int, interrupt_handler_t*, void*);
void			free_hdlr(int);
void			*malloc(size_t);
void			free(void*);
void			udelay(unsigned long);
unsigned long	get_timer(unsigned long);
void			do_reset(void);
void			app_startup(char **);

#endif    /* ifndef __ASSEMBLY__ */

enum {
#define EXPORT_FUNC(x) XF_ ## x ,
EXPORT_FUNC(get_version)
EXPORT_FUNC(getc)
EXPORT_FUNC(tstc)
EXPORT_FUNC(putc)
EXPORT_FUNC(puts)
EXPORT_FUNC(printf)
EXPORT_FUNC(install_hdlr)
EXPORT_FUNC(free_hdlr)
EXPORT_FUNC(malloc)
EXPORT_FUNC(free)
EXPORT_FUNC(udelay)
EXPORT_FUNC(get_timer)
EXPORT_FUNC(do_reset)
#undef EXPORT_FUNC
XF_MAX
};

#define XF_VERSION	2

#if defined(CONFIG_I386)
extern gd_t *global_data;
#endif

#endif	/* __EXPORTS_H__ */
