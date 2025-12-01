#ifndef __MIMVIEW_H__
#define __MIMVIEW_H__

#define VERSION "0.0.0"

#include "config.h"

/* Milsko */
#include <MDE/Foundation.h>
#include <Mw/Milsko.h>

/* External */

/* Standard */
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

typedef struct image {
	char*	       path;
	unsigned char* data;
	int	       width;
	int	       height;
	int	       x;
	int	       y;
	double	       scale;
} image_t;

/* main.c */
extern MwWidget	  window, menu, image;
extern MwLLPixmap pxprojector, pxdata;
extern MwWidget	  bprev, bnext, bzoomin, bzoomout;

/* ui.c */
extern int current;
void	   ui_init(void);

/* image.c */
extern image_t* images;
void		image_init(void);
void		image_add(const char* path);
void		image_render(void);

#endif
