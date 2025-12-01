#include "mimview.h"

#include <stb_ds.h>

static void* help_about;
static void* file_open_a_file;
static void* file_open_a_directory;
int	     current = 0;

static void file_fc_chosen(MwWidget handle, void* user, void* client) {
	int i;

	for(i = 0; i < arrlen(images); i++) {
		free(images[i].path);
		if(images[i].data != NULL) free(images[i].data);
	}
	arrfree(images);

	current = 0;
	image_add(client);
	image_init();
	image_render();
}

static void file_dc_scan(const char* path, int dir, int symlink, void* uesr) {
	if(dir) return;

	image_add(path);
}

static void file_dc_chosen(MwWidget handle, void* user, void* client) {
	int i;

	for(i = 0; i < arrlen(images); i++) {
		free(images[i].path);
		if(images[i].data != NULL) free(images[i].data);
	}
	arrfree(images);

	MDEDirectoryScan(client, file_dc_scan, NULL);

	current = 0;
	image_init();
	image_render();
}

static void menu_menu(MwWidget handle, void* user, void* client) {
	if(client == help_about) {
		MDEAboutDialog(window, "mimview", VERSION, pxprojector);
	} else if(client == file_open_a_file) {
		MwWidget fc = MwFileChooser(window, "Open a file");
		MwAddUserHandler(fc, MwNfileChosenHandler, file_fc_chosen, NULL);
	} else if(client == file_open_a_directory) {
		MwWidget dc = MwDirectoryChooser(window, "Open a directory");
		MwAddUserHandler(dc, MwNdirectoryChosenHandler, file_dc_chosen, NULL);
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

	m		      = MwMenuAdd(menu, NULL, "File");
	file_open_a_file      = MwMenuAdd(menu, m, "Open a file");
	file_open_a_directory = MwMenuAdd(menu, m, "Open a directory");

	m	   = MwMenuAdd(menu, NULL, "?Help");
	help_about = MwMenuAdd(menu, m, "About");

	MwAddUserHandler(menu, MwNmenuHandler, menu_menu, NULL);
	MwAddUserHandler(bprev, MwNactivateHandler, bprev_activate, NULL);
	MwAddUserHandler(bnext, MwNactivateHandler, bnext_activate, NULL);
	MwAddUserHandler(bzoomin, MwNactivateHandler, bzoomin_activate, NULL);
	MwAddUserHandler(bzoomout, MwNactivateHandler, bzoomout_activate, NULL);
}
