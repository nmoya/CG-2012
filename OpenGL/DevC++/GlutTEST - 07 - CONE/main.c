// CONE
#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <gl/glu.h>			//Util library

void cone(void)
	{
	GLfloat x,y,angle;  // Storage for coordinates and angles
	int iPivot = 1;		// Used to flag alternating colors
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// ============================================================================
	glTranslatef(50.0f, 50.0f, 0.0f);
//	glRotatef(45, 1.0f, 0.0f, 0.0f);
//	glRotatef(45, 0.0f, 1.0f, 0.0f);
	
	// Desenhando a base do cone
	glBegin(GL_TRIANGLE_FAN);
	// Centro do FAN é a origem (0,0,0)
	glVertex2f(0.0f, 0.0f);
	for(angle = 0.0f; angle < (2.0f*3.1415f); angle += (3.1415f/24.0f))
		{
		// Calculate x and y position of the next vertex
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
			// Alternate color between red and green
		if((iPivot %2) == 0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
		// Increment pivot to change color next time
		iPivot++;
		// Specify the next vertex for the triangle fan
		glVertex2f(x, y);
		}

	// Done drawing the fan that covers the bottom
	glEnd();

	// Desenhando a lateral do cone
	glBegin(GL_TRIANGLE_FAN);

	// Pinnacle of cone is shared vertex for fan, moved up Z axis
	// to produce a cone instead of a circle
	glVertex3f(0.0f, 0.0f, 75.0f);
	
	// Loop around in a circle and specify even points along the circle
	// as the vertices of the triangle fan
	for(angle = 0.0f; angle < (2.0f*3.1415f); angle += (3.1415f/8.0f))
		{
		// Calculate x and y position of the next vertex
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
			// Alternate color between red and green
		if((iPivot %2) == 0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
		// Increment pivot to change color next time
		iPivot++;
		// Specify the next vertex for the triangle fan
		glVertex2f(x, y);
		}
	// Done drawing fan for cone
	glEnd();
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
	//Limpa a janela de visualização com a cor de fundo especificada 
	glClear(GL_COLOR_BUFFER_BIT);
    cone();
	glFlush();		                 // send all output to display 
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{   
    glClearColor(0.0,0.0,0.0,0.0);       // set white background color
//	glMatrixMode(GL_PROJECTION); 
//	glLoadIdentity();
	
// ========================== testes de modo de desenho ======================
//	Modo de definição de cor
	glShadeModel(GL_FLAT);
//	glShadeModel(GL_SMOOTH);	

// Turn culling 
//	glEnable(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);

// Habilitando o teste de profundidade 
//	glEnable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);

// Desenhando a parte posterior somente como linha
//	glPolygonMode(GL_BACK,GL_LINE);
	glPolygonMode(GL_BACK,GL_FILL);
}

void reshape(int w, int h)
{
	if (h==0)				//prevenindo divisão por zero
		h=1;
	glViewport(0,0,w,h);	//ajusta viewport  para as dimensões da Janela
	glLoadIdentity();		//reseta sistema de coordenadas
    if (w<=h)
		glOrtho(0,100,0,100*h/w,-100.0,100.0);
    else
		glOrtho(0,100*w/h,0,100,-100.0,100.0);
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




