#include "mauplay.h"

#include "skipback.xpm"
#include "play.xpm"
#include "pause.xpm"
#include "stop.xpm"
#include "skipfwd.xpm"

#include "repeat.xpm"
#include "shuffle.xpm"

MwWidget window;
MwWidget menu, album, infoframe, infosep, bskipback, bplay, bpause, bstop, bskipfwd, modesep, brepeat, bshuffle, mainsep;
MwLLPixmap pxalbum, pxskipback, pxplay, pxpause, pxstop, pxskipfwd, pxrepeat, pxshuffle;

static void resize(MwWidget handle, void* user, void* client){
	int ww = MwGetInteger(window, MwNwidth);
	int wh = MwGetInteger(window, MwNheight) - MwGetInteger(menu, MwNheight);
	int y = MwGetInteger(menu, MwNheight);

	MwVaApply(album,
		MwNx, 5,
		MwNy, y + 5,
		MwNwidth, 32,
		MwNheight, 32,
	NULL);

	MwVaApply(infoframe,
		MwNx, 5 + 32 + 5,
		MwNy, y + 5,
		MwNwidth, ww - 5 - 32 - 5 - 5 - 10 - 10 - 32 * 7,
		MwNheight, 32,
	NULL);

	MwVaApply(infosep,
		MwNx, 5 + 32 + 5 + MwGetInteger(infoframe, MwNwidth),
		MwNy, y + 5,
		MwNwidth, 10,
		MwNheight, 32,
	NULL);

	MwVaApply(bskipback,
		MwNx, 5 + 32 + 5 + MwGetInteger(infoframe, MwNwidth) + 10,
		MwNy, y + 5,
		MwNwidth, 32,
		MwNheight, 32,
	NULL);

	MwVaApply(bplay,
		MwNx, 5 + 32 + 5 + MwGetInteger(infoframe, MwNwidth) + 10 + 32,
		MwNy, y + 5,
		MwNwidth, 32,
		MwNheight, 32,
	NULL);

	MwVaApply(bpause,
		MwNx, 5 + 32 + 5 + MwGetInteger(infoframe, MwNwidth) + 10 + 32 + 32,
		MwNy, y + 5,
		MwNwidth, 32,
		MwNheight, 32,
	NULL);

	MwVaApply(bstop,
		MwNx, 5 + 32 + 5 + MwGetInteger(infoframe, MwNwidth) + 10 + 32 + 32 + 32,
		MwNy, y + 5,
		MwNwidth, 32,
		MwNheight, 32,
	NULL);

	MwVaApply(bskipfwd,
		MwNx, 5 + 32 + 5 + MwGetInteger(infoframe, MwNwidth) + 10 + 32 + 32 + 32 + 32, 
		MwNy, y + 5,
		MwNwidth, 32,
		MwNheight, 32,
	NULL);

	MwVaApply(modesep,
		MwNx, 5 + 32 + 5 + MwGetInteger(infoframe, MwNwidth) + 10 + 32 * 5,
		MwNy, y + 5,
		MwNwidth, 10,
		MwNheight, 32,
	NULL);

	MwVaApply(brepeat,
		MwNx, 5 + 32 + 5 + MwGetInteger(infoframe, MwNwidth) + 10 + 32 * 5 + 10,
		MwNy, y + 5,
		MwNwidth, 32,
		MwNheight, 32,
	NULL);

	MwVaApply(bshuffle,
		MwNx, 5 + 32 + 5 + MwGetInteger(infoframe, MwNwidth) + 10 + 32 * 5 + 10 + 32,
		MwNy, y + 5,
		MwNwidth, 32,
		MwNheight, 32,
	NULL);

	MwVaApply(mainsep,
		MwNx, 5,
		MwNy, y + 5 + 32,
		MwNwidth, ww - 5 - 5,
		MwNheight, 10,
	NULL);
}

int main() {
	MwLibraryInit();

	window = MwVaCreateWidget(MwWindowClass, "main", NULL, MwDEFAULT, MwDEFAULT, 640, 400,
		MwNtitle, "mauplay",
	NULL);
	menu = MwCreateWidget(MwMenuClass, "menu", window, 0, 0, 0, 0);
	album = MwCreateWidget(MwImageClass, "album", window, 0, 0, 0, 0);
	infoframe = MwVaCreateWidget(MwFrameClass, "info", window, 0, 0, 0, 0,
		MwNbackground, "#000",
		MwNforeground, "#0f0",
		MwNhasBorder, 1,
		MwNinverted, 1,
	NULL);
	infosep = MwVaCreateWidget(MwSeparatorClass, "infosep", window, 0, 0, 0, 0,
		MwNorientation, MwVERTICAL,
	NULL);
	bskipback = MwVaCreateWidget(MwButtonClass, "skipback", window, 0, 0, 0, 0,
		MwNflat, 1,
	NULL);
	bplay = MwVaCreateWidget(MwButtonClass, "play", window, 0, 0, 0, 0,
		MwNflat, 1,
	NULL);
	bpause = MwVaCreateWidget(MwButtonClass, "pause", window, 0, 0, 0, 0,
		MwNflat, 1,
	NULL);
	bstop = MwVaCreateWidget(MwButtonClass, "stop", window, 0, 0, 0, 0,
		MwNflat, 1,
	NULL);
	bskipfwd = MwVaCreateWidget(MwButtonClass, "skipfwd", window, 0, 0, 0, 0,
		MwNflat, 1,
	NULL);
	modesep = MwVaCreateWidget(MwSeparatorClass, "modesep", window, 0, 0, 0, 0,
		MwNorientation, MwVERTICAL,
	NULL);
	brepeat = MwVaCreateWidget(MwButtonClass, "repeat", window, 0, 0, 0, 0,
		MwNflat, 1,
	NULL);
	bshuffle = MwVaCreateWidget(MwButtonClass, "shuffle", window, 0, 0, 0, 0,
		MwNflat, 1,
	NULL);
	mainsep = MwVaCreateWidget(MwSeparatorClass, "mainsep", window, 0, 0, 0, 0,
		MwNorientation, MwHORIZONTAL,
	NULL);

	pxalbum = MwLoadIcon(window, MwIconError);
	pxskipback = MwLoadXPM(window, skipback_xpm);
	pxplay = MwLoadXPM(window, play_xpm);
	pxpause = MwLoadXPM(window, pause_xpm);
	pxstop = MwLoadXPM(window, stop_xpm);
	pxskipfwd = MwLoadXPM(window, skipfwd_xpm);

	pxrepeat = MwLoadXPM(window, repeat_xpm);
	pxshuffle = MwLoadXPM(window, shuffle_xpm);

	MwSetVoid(album, MwNpixmap, pxalbum);

	MwSetVoid(bskipback, MwNpixmap, pxskipback);
	MwSetVoid(bplay, MwNpixmap, pxplay);
	MwSetVoid(bpause, MwNpixmap, pxpause);
	MwSetVoid(bstop, MwNpixmap, pxstop);
	MwSetVoid(bskipfwd, MwNpixmap, pxskipfwd);

	MwSetVoid(brepeat, MwNpixmap, pxrepeat);
	MwSetVoid(bshuffle, MwNpixmap, pxshuffle);

	MwAddUserHandler(window, MwNresizeHandler, resize, NULL);

	resize(window, NULL, NULL);

	MwLoop(window);
}
