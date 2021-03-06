#include "main.h"

//translation
float cubeX = 0.0;
float cubeY = 0.0;
float cubeZ = -4.0;

//rotation
float pitch = 0.0;
float yaw = 0.0;
float roll = 0.0;

GLint single_cube_List;

void draw_cube();
void display();
void reshape(GLsizei width, GLsizei height);
void timer(int value);
void init();
void special(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);


int nStep = 0;






void keyboard(unsigned char key, int x, int y)
{
	//esc key to exit the program
	if (key == 27)
	{
		exit(0);
	}
	else if (key == 43) // '+'
	{
		roll += 1.0;
	}
	else if (key == 45) //'-'
	{
		roll -= 1.0;
	}
	else if (key == 113) //'q'
	{
		cubeZ += 0.1;
	}
	else if (key == 119) //'w'
	{
		cubeZ -= 0.1;
	}
	else if (key == 97) //'a'
	{
		cubeY += 0.1;
	}
	else if (key == 115) //'s'
	{
		cubeY -= 0.1;
	}
	else if (key == 122) //'z'
	{
		cubeX += 0.1;
	}
	else if (key == 120) //'x'
	{
		cubeX -= 0.1;
	}
	else if (key == 32)
	{
		nStep++;
		if (nStep > 2)
			nStep = 0;
	}

	glutPostRedisplay();
}

GLuint List1() { //cube

	GLuint CubeDL;
	CubeDL = glGenLists(1);

	glNewList(CubeDL, GL_COMPILE);

	draw_cube();



	glEndList();

	return(CubeDL);
}

static void cubebase(GLuint texture)
{
	//glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_POLYGON);
	glVertex3d(-0.5, -0.5, -0.5); glTexCoord2f(0, 0);
	glVertex3d(-0.5, 0.5, -0.5);  glTexCoord2f(1, 0);
	glVertex3d(0.5, 0.5, -0.5);	  glTexCoord2f(1, 1);
	glVertex3d(0.5, -0.5, -0.5);  glTexCoord2f(0, 1);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	//glDepthMask(GL_TRUE);
}

void draw_cube()
{
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	glColor3f(1, 1, 1);
	//glColor3f(0.0f, 1.0f, 0.0f);     // Green, -Z축 방향
	cubebase(texture1);

	glPushMatrix();
	/*construct side on +x axis*/
	glTranslated(1.0, 0.0, 0.0);
	glRotated(90.0, 0.0, 1.0, 0.0);
	//glColor3f(0.0f, 0.0f, 1.0f);     // Blue, +X축 방향
	cubebase(texture2);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-1.0, 0.0, 0.0);
	glRotated(-90.0, 0.0, 1.0, 0.0);
	//glColor3f(1.0f, 0.5f, 0.0f);     // Orange, -X축 방향
	cubebase(texture3);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 1.0, 0.0);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	//glColor3f(1.0f, 0.0f, 0.0f);     // Red, +Y축 방향
	cubebase(texture4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, -1.0, 0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	//glColor3f(1.0f, 1.0f, 0.0f);     // Yellow, -Y축 방향
	cubebase(texture5);
	glPopMatrix();

	//glColor3f(1.0f, 0.0f, 1.0f);     // Magenta, +Z축 방향
	//glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glBegin(GL_POLYGON);
	glVertex3d(-0.5, -0.5, 0.5);
	glVertex3d(0.5, -0.5, 0.5);
	glVertex3d(0.5, 0.5, 0.5);
	glVertex3d(-0.5, 0.5, 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	//glDepthMask(GL_TRUE);

	glPopMatrix();

	glFlush();
}

void display()
{



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 10, 0, 0, 0, 0.0f, 1.0f, 0.0f);
	glTranslatef(cubeX, cubeY, cubeZ);
	glRotatef(pitch, 1.0, 0.0, 0.0); //rotate on x-axis
	glRotatef(yaw, 0.0, 1.0, 0.0); //rotate on y-axis
	glRotatef(roll, 0.0, 0.0, 1.0); //roate on z-axis

	if (nStep == 0) {
		glEnable(GL_LINE_SMOOTH);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		for (int k = -1; k < 2; k++) {
			for (int j = -1; j < 2; j++) {
				for (int i = -1; i < 2; i++)
				{
					glPushMatrix();

					glTranslatef(i*1.1, j*1.1, k*1.1);
					glCallList(single_cube_List);

					glPopMatrix();
				}
			}
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_LINE_SMOOTH);
	}
	else {

		for (int k = -1; k < 2; k++) {
			for (int j = -1; j < 2; j++) {
				for (int i = -1; i < 2; i++)
				{
					glPushMatrix();

					glTranslatef(i*1.1, j*1.1, k*1.1);
					glCallList(single_cube_List);

					glPopMatrix();
				}
			}
		}
	}

	glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, (GLfloat)width / (GLfloat)height, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(30, timer, 0);
}

GLuint imageLoader(const char* file) {
	GLuint id = SOIL_load_OGL_texture(
		file,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	if (0 == id)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
	else {
		printf("%s loaded successfully\n", file);
	}
	return id;
}
void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClearDepth(1.0);

	glEnable(GL_DEPTH_TEST);


	GLfloat    lightPosition[] = { 1.0, 2.0, 3.0, 1.0 };
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_NORMALIZE);

	texture1 = imageLoader("1.jpg");
	texture2 = imageLoader("2.jpg");
	texture3 = imageLoader("3.bmp");
	texture4 = imageLoader("4.jpg");
	texture5 = imageLoader("5.jpg");
	texture6 = imageLoader("6.jpg");


	single_cube_List = List1();
}
void special(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		pitch += 1.0;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		pitch -= 1.0;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		yaw += 1.0;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		yaw -= 1.0;
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Rubix Cube");

	init();

	glutDisplayFunc(display);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);

	glutMainLoop();

	return 0;
}