// TRIANGULOS
#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <gl/glu.h>			//Util library

GLfloat nRange = 50.0f;

// Função callback chamada para fazer o desenho
void Desenha(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	int i;
	for(i=1; i<360; i++)
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
			glColor3f(1.0f,1.0f,1.0f);
			glVertex3f(10.0f, 10.0f, 10.0f);
			glVertex3f(20.0f, 10.0f, 10.0f);
			glVertex3f(15.0f, 20.0f, 10.0f);

			glColor3f(1.0f,0.0f,1.0f);
			glVertex3f(-10.0f, -10.0f, -10.0f);
			glVertex3f(-15.0f, -20.0f, -10.0f);	
			glVertex3f(-20.0f, -10.0f, -10.0f);
		glEnd();
		glRotatef(1.0f,0.0f,1.0f,0.0f);
		printf("%d\n",i);
		glFlush();
		glutSwapBuffers();
		Sleep(30);
    }
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{   
    glClearColor(1.0,1.0,1.0,0.0);       // set white background color
    glColor3f(0.0f, 0.0f, 0.0f);          // set the drawing color 
 	glPointSize(4.0);		       // a ‘dot’ is 4 by 4 pixels
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
}

void reshape(int w, int h)
{
 // glMatrixMode(GL_PROJECTION);  /* Start modifying the projection matrix. */
  	// Prevent a divide by zero
	if(h == 0)
		h = 1;
	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);
	// Reset coordinate system
	glLoadIdentity();
	// Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
}

// Programa Principal 
int main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("OpenGL+GLUT");
	glutDisplayFunc(Desenha);
	Inicializa();
    glutReshapeFunc(reshape);
	glutMainLoop();
}




