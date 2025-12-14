#include "mimview.h"

#include <stb_image.h>
#include <stb_ds.h>

image_t*	      images = NULL;
static int	      oldw = 0, oldh = 0;
static unsigned char* buffer = NULL;

void image_init(void) {
	unsigned char* d = MwPixmapGetRaw(pxdata);
	MwRect	       rc;

	MwPixmapGetSize(pxdata, &rc);

	if(oldw != rc.width || oldh != rc.height) {
		int y, x;
		if(buffer != NULL) free(buffer);
		for(y = 0; y < rc.height; y++) {
			for(x = 0; x < rc.width; x++) {
				unsigned char* px = &d[(y * rc.width + x) * 4];
				if(((y / 16) + (x / 16)) % 2) {
					px[0] = px[1] = px[2] = 128;
				} else {
					px[0] = px[1] = px[2] = 64;
				}
				px[3] = 255;
			}
		}
		buffer = malloc(rc.width * rc.height * 4);
		memcpy(buffer, d, rc.width * rc.height * 4);
	} else {
		memcpy(d, buffer, rc.width * rc.height * 4);
	}
	oldw = rc.width;
	oldh = rc.height;

	MwLLPixmapUpdate(pxdata);
	MwForceRender(image);
}

void image_add(const char* path) {
	image_t img;
	img.path   = MDEStringDuplicate(path);
	img.data   = NULL;
	img.width  = 0;
	img.height = 0;
	img.x	   = 0;
	img.y	   = 0;
	img.scale  = 0;
	arrput(images, img);
}

void image_render(void) {
	if(current < arrlen(images) && images[current].data == NULL) {
		int	       w, h, ch;
		unsigned char* d;
	again:;
		d = stbi_load(images[current].path, &w, &h, &ch, 4);
		if(d != NULL) {
			int    dw, dh;
			int    pw, ph;
			double sw, sh;
			MwRect rc;

			MwPixmapGetSize(pxdata, &rc);

			pw = rc.width;
			ph = rc.height;

			MwGetScreenSize(window, &rc);

			dw = MwGetInteger(window, MwNwidth) - pw;
			dh = MwGetInteger(window, MwNheight) - ph;

			/* this way is kinda terrible... but it kinda works */
			if((rc.width - dw - 32) > w && (rc.height - dh - 32) > h) {
				pw = w;
				ph = h;
				MwVaApply(window,
					  MwNwidth, pw + dw,
					  MwNheight, ph + dh,
					  NULL);
			} else {
				pw = rc.width - 32 - dw;
				ph = rc.height - 32 - dh;
				MwVaApply(window,
					  MwNwidth, pw + dw,
					  MwNheight, ph + dh,
					  NULL);
			}

			sw = (double)w / pw;
			sh = (double)h / ph;

			images[current].data   = d;
			images[current].width  = w;
			images[current].height = h;
			images[current].scale  = sw > sh ? sw : sh;
		} else {
			free(images[current].path);
			arrdel(images, current);
			if(arrlen(images) <= current) {
				current = 0;
			}
			goto again;
		}
	}

	if(current < arrlen(images)) {
		unsigned char* d = MwPixmapGetRaw(pxdata);
		int	       y;
		int	       x;
		MwRect	       rc;
		char	       str[128];
		int	       ox, oy;

		MwPixmapGetSize(pxdata, &rc);

		ox = (rc.width - images[current].width / images[current].scale) / 2 - images[current].x / images[current].scale;
		oy = (rc.height - images[current].height / images[current].scale) / 2 - images[current].y / images[current].scale;

		sprintf(str, "mimview [%d of %d] %s", current + 1, arrlen(images), images[current].path);

		MwVaApply(window,
			  MwNtitle, str,
			  NULL);

		for(y = (oy < 0 ? 0 : 0); y < rc.height + (oy < 0 ? -oy : -oy * 2); y++) {
			for(x = (ox < 0 ? 0 : 0); x < rc.width + (ox < 0 ? -ox : -ox * 2); x++) {
				if(0 <= (y + oy) && (y + oy) < rc.height && 0 <= (x + ox) && (x + ox) < rc.width) {
					int	       ix = x * images[current].scale;
					int	       iy = y * images[current].scale;
					unsigned char* opx;
					unsigned char* ipx;

					if(0 <= iy && iy < images[current].height && 0 <= ix && ix < images[current].width) {
						int i;
						opx = &d[((y + oy) * rc.width + x + ox) * 4];
						ipx = &images[current].data[(iy * images[current].width + ix) * 4];

						for(i = 0; i < 3; i++) {
							opx[i] *= (255 - ipx[3]) / 255.0;
							opx[i] += ipx[i] * (ipx[3] / 255.0);
						}
					}
				}
			}
		}
		MwLLPixmapUpdate(pxdata);
		MwForceRender(image);
	}
}
