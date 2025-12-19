#include "mbiff.h"

#include "mailempty.xpm"
#include "mailfull.xpm"

MwWidget     window, image, mail;
MwLLPixmap   empty, full;
static int   waiting = 0;
static void* help_about;

static void resize(MwWidget handle, void* user, void* client) {
	int w  = MwGetInteger(handle, MwNwidth);
	int h  = MwGetInteger(handle, MwNheight);
	int iw = w < h ? w : h;

	(void)user;
	(void)client;

	MwVaApply(image,
		  MwNx, (w - iw) / 2,
		  MwNy, (h - iw) / 2,
		  MwNwidth, iw,
		  MwNheight, iw,
		  NULL);
}

static void tick(MwWidget handle, void* user, void* client) {
	(void)handle;
	(void)user;
	(void)client;

	waiting += MwWaitMS;
	if(waiting >= 1000) {
		check_mail();

		waiting = 0;
	}
}

static void mouseUp(MwWidget handle, void* user, void* client) {
	(void)handle;
	(void)user;
	(void)client;

	MwVaApply(image,
		  MwNpixmap, empty,
		  NULL);
}

int main() {
	void* m;

	init_mail();

	MwLibraryInit();

	window = MwVaCreateWidget(MwWindowClass, "main", NULL, MwDEFAULT, MwDEFAULT, 128, 128,
				  MwNtitle, "mbiff",
				  MwNmodernLook, 0,
				  NULL);

	empty = MwLoadImage(window, ICON128DIR "/mailempty.png");
	full  = MwLoadImage(window, ICON128DIR "/mailfull.png");
	mail  = MwLoadImage(window, ICON128DIR "/mail.png");
	if(empty == NULL) empty = MwLoadXPM(window, mailempty);
	if(full == NULL) full = MwLoadXPM(window, mailfull);
	if(mail == NULL) mail = MwLoadXPM(window, mailempty);

	MwVaApply(window, MwNiconPixmap, mail, NULL);

	image = MwVaCreateWidget(MwImageClass, "image", window, 0, 0, 0, 0,
				 MwNpixmap, empty,
				 NULL);

	resize(window, NULL, NULL);

	MwAddUserHandler(image, MwNmouseUpHandler, mouseUp, NULL);
	MwAddUserHandler(window, MwNtickHandler, tick, NULL);
	MwAddUserHandler(window, MwNresizeHandler, resize, NULL);

	MwLoop(window);
}
