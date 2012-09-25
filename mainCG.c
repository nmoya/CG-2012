#include "include/fisica.h"
#include "include/objetoGrafico.h"
#include "include/parser.h"

#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <gl/glu.h>			//Util library

//#define DEBUG_SPIN_SPIN //SPIN, SPIN! Se definido, saia do programa com um CTRL+C na janela de linha de comando

GLfloat nRange = 57.0f;  //XXX acredito que o professor tenha dito que essa variavel tenha que ser ajustada automaticamente (para caber toda a cena?)
int height, width;
objetoGrafico* objetosGraficos;
int objetosGraficos_len;
grafo *g;
void Desenha(void)
{
    #ifdef DEBUG_SPIN_SPIN
    while(1){
    #endif
    
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	int i;
	verificaColisao(objetosGraficos, objetosGraficos_len, 0);
	for(i=0; i<objetosGraficos_len; i++){
        aplicaAceleracao(&objetosGraficos[i]);
        moveObjeto(&objetosGraficos[i]);
//        colidePlano (&objetosGraficos[i]);
        calculaBBox(&objetosGraficos[i]);
        
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // set black background color
//	glMatrixMode(GL_PROJECTION); 
//	glLoadIdentity();

// ========================== testes de modo de desenho ======================
//	Modo de definição de cor
//	glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);	

// Turn culling 
//	glEnable(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);

// Normaliza normais automaticamente
   glEnable(GL_NORMALIZE);
   
// Habilitando o teste de profundidade 
	glEnable(GL_DEPTH_TEST);
//	glDisable(GL_DEPTH_TEST);

// Desenhando a parte posterior somente como linha
//	glPolygonMode(GL_BACK,GL_LINE);
//	glPolygonMode(GL_BACK,GL_FILL);

// Tipografia de linha
   glEnable(GL_LINE_STIPPLE);
}

void reshape(int w, int h)
{    
     height = h;
     width = w;
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
		//glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
         glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
		//glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
}
// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
     #define INCREMENTO_TECLADO 1.5
     glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        int i;
        for(i=0; i<objetosGraficos_len; i++){
            desenhaObjetoGrafico(&objetosGraficos[i]);
        }
        glFlush();
        glutSwapBuffers();
	if (key == 27)    //ESC
		exit(0);
	if (key == 'w')
	{
	   glRotatef(INCREMENTO_TECLADO,1,0,0);
    }
    else if (key == 'a')
    {         
        glRotatef(-INCREMENTO_TECLADO,0,1,0); 
    }
    else if (key == 's')
    {
         glRotatef(-INCREMENTO_TECLADO,1,0,0);
    }
    else if (key == 'd')
    {
         glRotatef(INCREMENTO_TECLADO,0,1,0); 
    }
    else if (key == 'z')     //Zoom In
    {
         nRange-=INCREMENTO_TECLADO*2;
         reshape(width, height);
    }
    else if (key == 'x')     //Zoom 'Out'
    {
         nRange+=INCREMENTO_TECLADO*2;
         reshape(width, height);
    }
    else if (key == 'i') //Modo wireframe
    {
         static int modoWireframeLigado=0;
         if(!modoWireframeLigado) glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
         else                     glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
         modoWireframeLigado=!modoWireframeLigado;
    }
    else if (key == 'v')
    {
         int id,i;
         printf("Digite a id do objeto que voce queira ligar/desligar a visibilidade:\n");
         fscanf(stdin,"%d",&id);
         printf("id=%d\n",id);
         for(i=0; i<objetosGraficos_len; i++){
             objetoGrafico* og = &objetosGraficos[i];
             if(og->id == id) og->invisivel = !og->invisivel;
         }
    }
    else if (key == 'm')
    {
         atualizaGrafo (objetosGraficos, g);
         imprimeGrafo(g);
    }
    else if (key == 'c')
    {
         verificaColisao(objetosGraficos,objetosGraficos_len, 1);
    }
}
void processaMouse (int botao, int estado, int x, int y)
{
     if(estado == GLUT_DOWN)
     {
           if(botao == GLUT_LEFT_BUTTON)
           {
                printf("Clique em: %d %d\n", x, y);
           }
           else if(botao == GLUT_MIDDLE_BUTTON)
           {
               //middle button code
           }
           else if(botao == GLUT_RIGHT_BUTTON)
           {
               //right button code
           }
     }
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
    g = carregaGrafo(objetosGraficos_len); 
    if(!g){
        getc(stdin); //Pausa para ver o erro antes de sair
        return 1;
    } 
    vetForca fGravidade;
    fGravidade.angx = fGravidade.angz = PI / 2; //90
    fGravidade.angy = PI; //180
    fGravidade.aceleracao = GRAVIDADE;
    fGravidade.velocidade = -6;
    
    addForcas(objetosGraficos, objetosGraficos_len, fGravidade, "VM");
    
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	nRange = 300;
    glutInitWindowSize(800, 600);
	glutCreateWindow("Visualizador");
	glutDisplayFunc(Desenha);
	glutIdleFunc(Desenha);
    // Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);
	Inicializa();
    glutReshapeFunc(reshape);
    glutMouseFunc(processaMouse);
	glutMainLoop();
	
	free(objetosGraficos);
	desalocaGrafo(g);
	return 0;
}


