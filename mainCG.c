#include "include/objetoGrafico.h"
#include "include/parser.h"

#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <gl/glu.h>			//Util library

//#define DEBUG_SPIN_SPIN //SPIN, SPIN! Se definido, saia do programa com um CTRL+C na janela de linha de comando

GLfloat nRange = 50.0f;  //XXX acredito que o professor tenha dito que essa variavel tenha que ser ajustada automaticamente (para caber toda a cena?)

objetoGrafico* objetosGraficos;
int objetosGraficos_len;

void Desenha(void)
{
    #ifdef DEBUG_SPIN_SPIN
    while(1){
    #endif
    
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	int i;
	for(i=0; i<objetosGraficos_len; i++){
        desenhaObjetoGrafico(&objetosGraficos[i]);
    }
	glFlush();
	glutSwapBuffers();
	Sleep(30);
    
    #ifdef DEBUG_SPIN_SPIN
	glRotatef(1,0,1,0);
    }
    #endif
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{   
//    glClearColor(1.0,1.0,1.0,0.0);       // set white background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // set black background color
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

// Tipografia de linha
   glEnable(GL_LINE_STIPPLE);
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
    FILE* arqEntrada = fopen("arquivoEntrada.txt","r");
    if(!arqEntrada){
        printf("ERRO: Nao foi possivel abrir o arquivo de entrada");
        getc(stdin); //Pausa para ver o erro antes de sair
        return 1;
    }
    objetosGraficos = carregaObjetosGraficos(arqEntrada, &objetosGraficos_len);
    if(!objetosGraficos){
        getc(stdin); //Pausa para ver o erro antes de sair
        return 1;
    }
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Visualizador");
	glutDisplayFunc(Desenha);
	Inicializa();
    glutReshapeFunc(reshape);
	glutMainLoop();
	
	free(objetosGraficos);
	return 0;
}
