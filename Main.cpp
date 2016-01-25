#include "glut.h"
#include <windows.h>
#include "camera.h"
#include "Game.h"
#include "Player.h"

#define ShowUpvector

Game* game = nullptr;

void prepareGlut(int argc, char **argv);

int main(int argc, char **argv) {
	prepareGlut(argc, argv);

	game = new Game();

	glutMainLoop();

	return 0;
}

void timerCB(int millisec) {
	glutTimerFunc(millisec, timerCB, millisec);
	glutPostRedisplay();
}

void reshape(int x, int y) {
	if (y == 0 || x == 0) return;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(4.0, (GLdouble)x / (GLdouble)y, 0.15, 200.0);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	game->update();
	game->display();

	glFlush();
	glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		PostQuitMessage(0);
		break;

	default:
		game->setKey(key, true);
		break;
	}
}

void keyUp(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		PostQuitMessage(0);
		break;

	default:
		game->setKey(key, false);
		break;
	}
}

void prepareGlut(int argc, char **argv) {
	const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

	const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat high_shininess[] = { 100.0f };

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("Shooter");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc(33, timerCB, 33); // redraw every 33 millisec (30fps)

	glClearColor(0.1, 0.1, 0.1, 1);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}