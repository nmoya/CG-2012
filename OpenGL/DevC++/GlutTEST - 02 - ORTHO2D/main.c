#include <windows.h>   // use as needed for your system
#include <gl/gl.h>
#include <gl/glut.h>
#include <gl/glu.h>			//Util library

// Função callback chamada para fazer o desenho
void Desenha(void)
{
	//Limpa a janela de visualização com a cor de fundo especificada 
	glClear(GL_COLOR_BUFFER_BIT);
	//Executa os comandos OpenGL 
	glBegin(GL_POINTS);
		glVertex2i(100, 50);         // draw three points
		glVertex2i(100, 130);
		glVertex2i(150, 130);
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
	gluOrtho2D(-640.0, 640.0, -480.0, 480.0);
}

// Programa Principal 
int main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Primeiro Programa");
	glutDisplayFunc(Desenha);
	Inicializa();
	glutMainLoop();
}




