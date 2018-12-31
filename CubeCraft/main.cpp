#include"glut.h"
#include"fac.h"
#include"block.h"
#include"entity.h"
#include<cmath>
#include<windows.h>

double angl, elev, winh = 800, winw = 800;

void init() {
	player.t = EntPoint{ 5, 10, 5 };
	player.hp = 20;

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	texts[0] = glLoadTex(".\\texture\\dirt.bmp");
	texts[1] = glLoadTex(".\\texture\\grassen.bmp");
	texts[2] = glLoadTex(".\\texture\\grassen_side.bmp");
	texts[3] = glLoadTex(".\\texture\\stone.bmp");
	texts[4] = glLoadTex(".\\texture\\bedrock.bmp");
	texts[5] = glLoadTex(".\\texture\\arrow.bmp");

	for (int j = 0; j < 64; ++j)
		for (int k = 0; k < 64; ++k)
			at(j, 0, k).id = bedrock, at(j, 0, k).t = Point{ j, 0, k };
	for (int i = 1; i <= 5; ++i)
		for (int j = 0; j < 64; ++j)
			for (int k = 0; k < 64; ++k)
				at(j, i, k).id = stone, at(j, i, k).t = Point{ j, i, k };
	for (int i = 6; i <= 8; ++i)
		for (int j = 0; j < 64; ++j)
			for (int k = 0; k < 64; ++k)
				at(j, i, k).id = dirt, at(j, i, k).t = Point{ j, i, k };
	for (int j = 0; j < 64; ++j)
		for (int k = 0; k < 64; ++k)
			at(j, 9, k).id = grass, at(j, 9, k).t = Point{ j, 9, k };

	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glOrtho(-32, 32, -32, 32, -32, 32);
	gluPerspective(100, 1, 0, 1280);
}

void render() {
	static bool a = false;
	if (!a) a = !a, init();

	POINT mouse;
	GetCursorPos(&mouse);
	double px = (400 - mouse.x) / 400.0 * 32, py = (400 - mouse.y) / 400.0 * 32;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	angl = mouse.x / winw * 2 * 3.14;
	elev = mouse.y / winh * 3.14 - 1.57;

	gluLookAt(player.t.x, player.t.y + 1.8, player.t.z, player.t.x - cos(angl), player.t.y - sin(elev) + 1.8, player.t.z - sin(angl),
		0, 1, 0);

	glBindTexture(GL_TEXTURE_2D, texts[5]);
	glRasterPos3d(player.t.x - cos(angl), player.t.y - sin(elev) + 1.8, player.t.z - sin(angl));
	glString("+");

	for (int i = 0; i < 64; ++i)
		for (int j = 0; j < 64; ++j)
			for (int k = 0; k < 64; ++k)
				at(i, j, k).draw();

	glPopMatrix();
	glutSwapBuffers();
}

void whenchange(int w, int h) {
	if (!w) w = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glOrtho(-32, 32, -32, 32, -32, 32);
	gluPerspective(5, double(winw = w) / (winh = h), 0, 1280);
}

void keyboard(unsigned char a, int x, int y) {
	switch (a) {
	case 's':
		player.t.z += sin(angl);
		player.t.x += cos(angl);
		break;
	case 'w':
		player.t.z -= sin(angl);
		player.t.x -= cos(angl);
		break;
	case 'd':
		player.t.z -= cos(angl);
		player.t.x += sin(angl);
		break;
	case 'a':
		player.t.z += cos(angl);
		player.t.x -= sin(angl);
		break;
	case ' ':
		++player.t.y;
		break;
	case 'b':
		--player.t.y;
		break;
	case 27:
		exit(0);
	}
}

void mouse(int button, int state, int x, int y) {
	double yk = sin(elev) / cos(angl), yb = player.t.y + 1.8 - yk * player.t.x, zk = tan(angl), zb = player.t.z - zk * player.t.x;
	int bx = -1, by = -1, bz = -1;
	for (int x = player.t.x; x <= player.t.x + 7; ++x) {
		double y = x * yk + yb, z = x * zk + zb;
		if (at(x, y, z).id != air) {
			bx = x, by = y, bz = z;
			break;
		}
	}
	if (!~bx) return;
	if (button == GLUT_LEFT_BUTTON) {
		put_inv(at(bx, by, bz));
		at(bx, by, bz).id = air;
	}
	if (button == GLUT_RIGHT_BUTTON) {
		at(bx, by, bz).id = stone;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(300, 100);
	glutInitWindowSize(800, 800);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Minecraft' 0.1.0");
	glutDisplayFunc(render);
	glutReshapeFunc(whenchange);
	glutIdleFunc(render);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glClearColor(100 / 255.0, 149 / 255.0, 237 / 255.0, 0.5);
	glutMainLoop();
}