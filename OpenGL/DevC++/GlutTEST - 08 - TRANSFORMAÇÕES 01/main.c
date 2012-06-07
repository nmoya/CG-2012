// Transformações, Pilha de Matrizes,  primeiro exemplo
#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <gl/glu.h>			//Util library

GLfloat nRange = 50.0f;

void DesenhaEixos(void)
	{
	GLint factor =1;
	GLushort pattern = 0X0F0F;
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(factor, pattern);
	glColor3f(1.0f, 1.0f, 1.0f);

	//glBegin(GL_LINE_LOOP);
//		glVertex3f(nRange-1, nRange-1, 0);
//		glVertex3f(nRange-1, -nRange+1, 0);
//		glVertex3f(-nRange+1, -nRange+1, 0);
//		glVertex3f(-nRange+1, nRange-1, 0);
//	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0, nRange,0);
		glVertex3f(0, -nRange,0);
        glVertex3f(-nRange,0,0);
		glVertex3f(nRange,0,0);
//		glVertex3f(0,0,-nRange);
//		glVertex3f(0,0,nRange);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
	//Limpa a janela de visualização com a cor de fundo especificada 
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	DesenhaEixos();
	
    glTranslatef(nRange/3,0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutWireSphere(nRange/10, 10, 10);			// esfera 1 - VERDE
	
    // Inicializa o sistema de coordenadas
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
	// ou faz a Translacao de retorno
	glTranslatef(-nRange/3,0.0f,0.0f);	

	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f,nRange/3,0.0f);
	glutWireSphere(nRange/10, 10, 10);			// esfera 2 - AZUL
	
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
