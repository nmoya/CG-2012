#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <gl/glu.h>			//Util library

GLfloat nRange = 2000.0f;

// Função callback chamada para fazer o desenho
void Desenha(void)
{
	//Limpa a janela de visualização com a cor de fundo especificada 
	glClear(GL_COLOR_BUFFER_BIT);
	//Executa os comandos OpenGL 
	glBegin(GL_TRIANGLES);
		glVertex2i(100, 100);         // draw three points
		glVertex2i(200, 100);
		glVertex2i(200, 200);
	glEnd();	
	glFlush();		                 // send all output to display 
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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("OpenGL+GLUT");
	glutDisplayFunc(Desenha);
	Inicializa();
    glutReshapeFunc(reshape);
	glutMainLoop();
}




