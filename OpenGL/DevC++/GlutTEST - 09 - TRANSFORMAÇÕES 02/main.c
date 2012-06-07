// Transformações, Pilha de Matrizes,  segundo exemplo
//#include <windows.h>   
#include <gl/gl.h>
#include <gl/glut.h>
#include <gl/glu.h>	
//#include <iostream>

GLfloat nRange = 100.0f;
GLfloat Angulo =   0.0f;
GLfloat Angulo1 =  0.0f;

void DesenhaSolidos(void)
	{
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(-50.0f, 12.5f, 0.0f);
	glutWireCube(25.0f);						// 1 - BRANCO
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(25.0f, 0.0f, 0.0f);
	glutWireCube(25.0f);						// 2 - VERMELHO
	
    // Salva a matriz e faz a translação e a rotação do cubo
	glPushMatrix();
		glTranslatef(25.0f, 0.0f, 0.0f); 
		glRotatef(45.0f+Angulo1, 1.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glutWireCube(25.0f);						// 3 - VERDE
		
	// Restaura a matriz
	glPopMatrix();
	glTranslatef(50.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);	
    glutWireCube(25.0f);						// 4 - AZUL
    
//	glPopMatrix();	
	glTranslatef(25.0f, 0.0f, 0.0f);	

	glColor3f(1.0f, 1.0f, 0.0f);
    glutWireCube(25.0f);						// 5 - AMARELO

	glFlush();
	}
	
void DesenhaEixos(void)
	{
	GLint factor =1;
	GLushort pattern = 0X0F0F;
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(factor, pattern);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_LINE_LOOP);
		glVertex3f(nRange-1, nRange-1, 0);
		glVertex3f(nRange-1, -nRange+1, 0);
		glVertex3f(-nRange+1, -nRange+1, 0);
		glVertex3f(-nRange+1, nRange-1, 0);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0, nRange,0);
		glVertex3f(0, -nRange,0);
		glVertex3f(-nRange,0,0);
		glVertex3f(nRange,0,0);
		glVertex3f(0,0,-nRange);
		glVertex3f(0,0,nRange);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glFlush();
	}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);	
	// Salva a matriz e faz a rotação do observador
	glPushMatrix();
	glLoadIdentity();
	glRotatef(Angulo, 1.0f, 1.0f, 1.0f);
		DesenhaEixos();
		DesenhaSolidos();
	// Restaura a matriz	
	glPopMatrix();
    glFlush();
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

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 31) 
	    Angulo++; else
    if (key == 27) 
       beep();
   	glFlush();  
}

// Programa Principal 
int main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("OpenGL+GLUT");
	glutDisplayFunc(Desenha);
	Inicializa();
    glutReshapeFunc(reshape);
    // Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);
	glutMainLoop();
}
