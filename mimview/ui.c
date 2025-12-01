#include "mimview.h"

#include <stb_ds.h>

static void* help_about;
int	     current = 0;

static void menu_menu(MwWidget handle, void* user, void* client) {
	if(client == help_about) {
		MDEAboutDialog(window, "mimview", VERSION, pxprojector);
	}
}

static void bprev_activate(MwWidget handle, void* user, void* client) {
	current--;
	if(current == -1) current = arrlen(images) - 1;
	if(current == -1) current = 0;
	if(current < arrlen(images)) {
		image_init();
		image_render();
	}
}

static void bnext_activate(MwWidget handle, void* user, void* client) {
	current++;
	if(current == arrlen(images)) current = 0;
	if(current < arrlen(images)) {
		image_init();
		image_render();
	}
}

static void bzoomin_activate(MwWidget handle, void* user, void* client) {
	if(current < arrlen(images)) {
		if(images[current].scale >= 0.2) {
			images[current].scale /= 2;
		}
		image_init();
		image_render();
	}
}

static void bzoomout_activate(MwWidget handle, void* user, void* client) {
	if(current < arrlen(images)) {
		images[current].scale *= 2;
		image_init();
		image_render();
	}
}

void ui_init(void) {
	void* m;

	m	   = MwMenuAdd(menu, NULL, "?Help");
	help_about = MwMenuAdd(menu, m, "About");

	MwAddUserHandler(menu, MwNmenuHandler, menu_menu, NULL);
	MwAddUserHandler(bprev, MwNactivateHandler, bprev_activate, NULL);
	MwAddUserHandler(bnext, MwNactivateHandler, bnext_activate, NULL);
	MwAddUserHandler(bzoomin, MwNactivateHandler, bzoomin_activate, NULL);
	MwAddUserHandler(bzoomout, MwNactivateHandler, bzoomout_activate, NULL);
}
