//*****************************************************
//
// DuasViewports.cpp 
// Um programa OpenGL simples que abre uma janela GLUT
// e desenha uma casinha em duas viewports diferentes
// 
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>

float win, aspecto;
int largura, altura;

// Função que faz o desenho de uma casa composta de um quadrado e um triângulo
void DesenhaCasa()
{
	// Altera a cor do desenho para azul
	glColor3f(0.0f, 0.0f, 1.0f);     
	// Desenha a casa
	glBegin(GL_QUADS);
		glVertex2f(-15.0f,-15.0f);
		glVertex2f(-15.0f,  5.0f);       
		glVertex2f( 15.0f,  5.0f);       
		glVertex2f( 15.0f,-15.0f);
	glEnd();

	// Altera a cor do desenho para branco
	glColor3f(1.0f, 1.0f, 1.0f);  
	// Desenha a porta e a janela  
	glBegin(GL_QUADS);
		glVertex2f(-4.0f,-14.5f);
		glVertex2f(-4.0f,  0.0f);       
		glVertex2f( 4.0f,  0.0f);       
		glVertex2f( 4.0f,-14.5f);       
		glVertex2f( 7.0f,-5.0f);
		glVertex2f( 7.0f,-1.0f);       
		glVertex2f(13.0f,-1.0f);       
		glVertex2f(13.0f,-5.0f);             
	glEnd();
    
	// Altera a cor do desenho para azul
	glColor3f(0.0f, 0.0f, 1.0f);     
	// Desenha as "linhas" da janela  
	glBegin(GL_LINES);      
		glVertex2f( 7.0f,-3.0f);      
		glVertex2f(13.0f,-3.0f);       
		glVertex2f(10.0f,-1.0f);    
		glVertex2f(10.0f,-5.0f);             
	glEnd();    
    
	// Altera a cor do desenho para vermelho
	glColor3f(1.0f, 0.0f, 0.0f); 
	// Desenha o telhado
	glBegin(GL_TRIANGLES);
		glVertex2f(-15.0f, 5.0f);   
		glVertex2f(  0.0f,17.0f);    
		glVertex2f( 15.0f, 5.0f);       
	glEnd();
}

// Função que coloca uma linha ao redor da área da window
void FazMoldura()
{
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-win*aspecto,-win);   
		glVertex2f(-win*aspecto, win);    
		glVertex2f( win*aspecto, win); 
		glVertex2f( win*aspecto,-win);                    
	glEnd();
	glLineWidth(1);                           
}

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);
	// Define a Viewport 1 na metade esquerda da janela
	glViewport(0, 0, largura, altura);
	// Desenha a casa na Viewport 1                        
	DesenhaCasa();
	FazMoldura();
 	// Define a Viewport 2 na metade direita da janela
	glViewport(largura, 0, largura, altura);
	// Desenha a casa na Viewport 2               
	DesenhaCasa();
	FazMoldura();
  	// Executa os comandos OpenGL 
	glFlush();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if(h == 0) h = 1;
	// Atualiza as variáveis
	largura = w/2;
	altura = h;
	aspecto = (float) largura/altura;	
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Estabelece a janela de seleção (esquerda, direita, inferior, 
	// superior) mantendo a proporção com a janela de visualização
	gluOrtho2D (-win*aspecto, win*aspecto, -win, win);
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	win = 50.0f;
}

// Programa Principal 
int main(void)
{
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
 	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5); 
 	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Exemplo com duas viewports");
 	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);
 	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);
    // Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);
 	// Chama a função responsável por fazer as inicializações 
	Inicializa();
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();
 	return 0;
}

