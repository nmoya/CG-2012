#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <gl/glu.h>			//Util library

GLfloat nRange = 50.0f;


void cubo(float aresta) // ordem correta
{
	printf("desenhado cubo de aresta %f", aresta);
	glShadeModel(GL_FLAT);
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(1,0,0); // vermelho
		glVertex3f(-aresta/2, -aresta/2, aresta/2);
		glVertex3f(aresta/2, -aresta/2, aresta/2);
		glVertex3f(-aresta/2, -aresta/2, -aresta/2);
		glVertex3f(aresta/2, -aresta/2, -aresta/2);
		glColor3f(0,1,0); // verde
		glVertex3f(-aresta/2, aresta/2, -aresta/2);
		glVertex3f(aresta/2, aresta/2, -aresta/2);
		glColor3f(0,0,1); // azul
		glVertex3f(-aresta/2, aresta/2, aresta/2);
		glVertex3f(aresta/2, aresta/2, aresta/2);
		glColor3f(1,1,1); // branco
		glVertex3f(-aresta/2, -aresta/2, aresta/2);
		glVertex3f(aresta/2, aresta/2, aresta/2);
		glVertex3f(aresta/2, -aresta/2, aresta/2);
	glEnd();
}
/*
void cubo(float aresta) // ordem incorreta
{
	printf("desenhado cubo de aresta %f", aresta);
	glShadeModel(GL_FLAT);
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0,0,1); // azul
		glVertex3f(-aresta/2, aresta/2, aresta/2);
		glVertex3f(aresta/2, aresta/2, aresta/2);
		glColor3f(1,1,1); // branco
		glVertex3f(-aresta/2, -aresta/2, aresta/2);
		glVertex3f(aresta/2, aresta/2, aresta/2);
		glVertex3f(aresta/2, -aresta/2, aresta/2);		
        glColor3f(1,0,0); // vermelho
		glVertex3f(-aresta/2, -aresta/2, aresta/2);
		glVertex3f(aresta/2, -aresta/2, aresta/2);
		glVertex3f(-aresta/2, -aresta/2, -aresta/2);
		glVertex3f(aresta/2, -aresta/2, -aresta/2);		
        glColor3f(0,1,0); // verde
		glVertex3f(-aresta/2, aresta/2, -aresta/2);
		glVertex3f(aresta/2, aresta/2, -aresta/2);
	glEnd();
}
*/

// Função callback chamada para fazer o desenho
void Desenha(void)
{
	//Limpa a janela de visualização com a cor de fundo especificada 
	glClear(GL_COLOR_BUFFER_BIT);
    glRotatef(20.0f,1,1,1);
	cubo(25.0f);
	glFlush();		                 // send all output to display 
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{   
    glClearColor(0.0,0.0,0.0,0.0);       // set white background color
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




