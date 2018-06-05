// Basic.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
#include "main.h"


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	int id = glutCreateWindow(TITLE);
	if (!initialize())
	{
		glutDestroyWindow(id);
		return EXIT_FAILURE;
	}

	glutDisplayFunc(display_callback);
	glutReshapeFunc(&ReSizeGLScene);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	timer_callback(0);

	glutMainLoop();

	return 0;
}

void display_callback() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'z':
		break;
	case 'x':
		break;
	default:
		return;
	}
}

void specialKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	default:
		return;
	}
}

void timer_callback(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer_callback, 0);
}


void ReSizeGLScene(int Width, int Height)
{
	if (Height == 0)                // Prevent A Divide By Zero If The Window Is Too Small
		Height = 1;

	glViewport(0, 0, Width, Height);        // Reset The Current Viewport And Perspective Transformation

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(-45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

bool initialize() {

	return true;
}