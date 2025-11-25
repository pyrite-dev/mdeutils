#include "mcompass.h"

#include <Mw/Widget/OpenGL.h>

MwWidget window, opengl;
int	 ww, wh;

static void resize(MwWidget handle, void* user, void* client) {
	ww = MwGetInteger(window, MwNwidth);
	wh = MwGetInteger(window, MwNheight);

	MwVaApply(opengl,
		  MwNwidth, ww,
		  MwNheight, wh,
		  NULL);

	glViewport(0, 0, ww, wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void tick(MwWidget handle, void* user, void* client) {
	int	i;
	double	rad;
	int	cx, cy;
	MwPoint p;

	cx = MwGetInteger(window, MwNx) + ww / 2;
	cy = MwGetInteger(window, MwNy) + wh / 2;
	MwGetCursorCoord(window, &p);

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 0);
	for(i = 0; i < 360; i += 10) {
		rad = i / 180.0 * M_PI;

		glBegin(GL_LINES);
		glVertex2f(cos(rad), sin(rad));
		glVertex2f(cos(rad) * 0.9, sin(rad) * 0.9);
		glEnd();
	}
	glBegin(GL_LINES);
	glVertex2f(-0.6, 0);
	glVertex2f(0.6, 0);
	glVertex2f(0, -0.6);
	glVertex2f(0, 0.6);
	glEnd();
	glBegin(GL_LINE_STRIP);
	for(i = 0; i <= 360; i += 10) {
		rad = i / 180.0 * M_PI;
		glVertex2f(cos(rad) * 0.2, sin(rad) * 0.2);
	}
	glEnd();

	/* memo: size is 0.2x0.2 */

	glLineWidth(2);

	glColor3f(1, 0, 0);
	glBegin(GL_LINE_STRIP); /* N */
	glVertex2f(-0.1, 0.65);
	glVertex2f(-0.1, 0.85);
	glVertex2f(0.1, 0.65);
	glVertex2f(0.1, 0.85);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP); /* W */
	glVertex2f(-0.85, -0.1);
	glVertex2f(-0.65, -0.05);
	glVertex2f(-0.85, 0);
	glVertex2f(-0.65, 0.05);
	glVertex2f(-0.85, 0.1);
	glEnd();

	glBegin(GL_LINE_STRIP); /* S */
	glVertex2f(-0.1, -0.85);
	glVertex2f(0.1, -0.85);
	glVertex2f(0.1, -0.75);
	glVertex2f(-0.1, -0.75);
	glVertex2f(-0.1, -0.65);
	glVertex2f(0.1, -0.65);
	glEnd();

	glBegin(GL_LINE_STRIP); /* E */
	glVertex2f(0.85, -0.1);
	glVertex2f(0.85, 0.1);
	glVertex2f(0.65, 0.1);
	glVertex2f(0.65, -0.1);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0.75, -0.1);
	glVertex2f(0.75, 0.1);
	glEnd();

	glLineWidth(1);

	rad = atan2(-(p.y - cy), p.x - cx);

	for(i = 0; i < 2; i++) {
		double n = 90 / 180.0 * M_PI;
		if(i == 0) {
			glColor3f(1, 0, 0);
		} else {
			glColor3f(0.2, 0.2, 0.2);
		}
		glBegin(GL_TRIANGLES);
		glVertex2f(cos(rad) * 0.95, sin(rad) * 0.95);
		glVertex2f(cos(rad - n) * 0.05, sin(rad - n) * 0.05);
		glVertex2f(cos(rad + n) * 0.05, sin(rad + n) * 0.05);
		glEnd();

		rad -= n * 2;
	}
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_TRIANGLE_FAN);
	for(i = 0; i <= 360; i += 10) {
		rad = i / 180.0 * M_PI;
		glVertex2f(cos(rad) * 0.05 * 2 / 3, sin(rad) * 0.05 * 2 / 3);
	}
	glEnd();

	MwOpenGLSwapBuffer(opengl);
}

int main() {
	MwLLColor col;
	int	  r, g, b;

	MwLibraryInit();

	window = MwVaCreateWidget(MwWindowClass, "main", NULL, MwDEFAULT, MwDEFAULT, 150, 150,
				  MwNtitle, "mcompass",
				  NULL);

	opengl = MwCreateWidget(MwOpenGLClass, "opengl", window, 0, 0, 150, 150);

	MwOpenGLMakeCurrent(opengl);

	col = MwParseColor(window, MwGetText(window, MwNbackground));
	MwGetColor(col, &r, &g, &b);
	MwLLFreeColor(col);

	glClearColor(r / 255.0, g / 255.0, b / 255.0, 1);

	resize(window, NULL, NULL);

	MwAddUserHandler(window, MwNresizeHandler, resize, NULL);
	MwAddUserHandler(window, MwNtickHandler, tick, NULL);

	MwLoop(window);
}
