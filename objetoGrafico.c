#include "include/objetoGrafico.h"

#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <gl/glu.h>			//Util library

//Funcoes ajudantes que imprimem o tipo e o id do objeto junto com uma mensagem de erro
void printErro(objetoGrafico* og, char* erro)  { printf("ERRO(id=%d, tipo=%c): %s\n", og->id, og->tipo, erro); }
void printAviso(objetoGrafico* og, char* erro){ printf("AVISO(id=%d, tipo=%c): %s\n", og->id, og->tipo, erro); }

void DEBUG_printObj(objetoGrafico* og){ 
     printf("objetoGrafico<id=%d, tipo=%c, args={", og->id, og->tipo);
     int i;
     for(i=0;i<numParametros(og->tipo);i++){
         printf("%f, ",og->valores[i]);
     }
     printf("}>\n");
}

void aplicaCorTransformacoesPadrao(objetoGrafico* og){
     float* cor          = getCor(og);
     float* orient       = getOrientacao(og);
     float* trans        = getTranslacao(og);
     float  espessura    = getEspessura(og);
     GLushort tipografia = getTipografia(og);

     //Cor e transformacoes
     glColor3f(cor[0],cor[1],cor[2]);
     glTranslatef(trans[0],trans[1],trans[2]);
     glRotatef(orient[0],orient[1],orient[2],orient[3]);

     //Configuracoes de linha
     glLineStipple(1, tipografia);
     glLineWidth(espessura);
}

//Funcoes de desenho
void desenhaPonto(objetoGrafico* og){
    printf("ERRO: Tipo nao implementado(tipo=%c,id=%d)\n", og->tipo, og->id);
}

void desenhaLinha(objetoGrafico* og){
     glPushMatrix(); //Salva a matriz    
     aplicaCorTransformacoesPadrao(og);

     int i;
     float* verts[2];
     for(i=0;i<2;i++){
        verts[i] = &getValoresExtra(og)[i*3];
     }

     glBegin(GL_LINES);
         for(i=0;i<2;i++){
             float* v = verts[i];
             glVertex3f(v[0],v[1],v[2]);
         }
     glEnd();

     glPopMatrix(); //Deixa a matriz como ela estava antes
}

void desenhaCirculo(objetoGrafico* og){
    printf("ERRO: Tipo nao implementado(tipo=%c,id=%d)\n", og->tipo, og->id);
}

void desenhaEsfera(objetoGrafico* og){
    printf("ERRO: Tipo nao implementado(tipo=%c,id=%d)\n", og->tipo, og->id);
}

void desenhaRetangulo(objetoGrafico* og){
    printf("ERRO: Tipo nao implementado(tipo=%c,id=%d)\n", og->tipo, og->id);
}

void desenhaTriangulo(objetoGrafico* og){
     glPushMatrix(); //Salva a matriz
     aplicaCorTransformacoesPadrao(og);     

     int i;
     float* verts[3];
     for(i=0;i<3;i++){
        verts[i] = &getValoresExtra(og)[i*3];
     }

     GLenum modoDesenho;
     if(ehSolido(og)) modoDesenho = GL_TRIANGLES;
     else             modoDesenho = GL_LINE_LOOP;
     glBegin(modoDesenho);
         for(i=0;i<3;i++){
             float* v = verts[i];
             glVertex3f(v[0],v[1],v[2]);
         }
     glEnd();
     
     glPopMatrix(); //Deixa a matriz como ela estava antes
}

void desenhaCubo(objetoGrafico* og){
    //printf("ERRO: Tipo nao implementado(tipo=%c,id=%d)\n", og->tipo, og->id);
    printAviso(og, "Espessura e tipografia ainda nao implementadas");
    glPushMatrix(); //Salva a matriz
    aplicaCorTransformacoesPadrao(og);
    
    float* cor         = getCor(og);
    float aresta       = getValoresExtra(og)[0];
    float espessura    = getEspessura(og);
    float tipografia   = getTipografia(og);
       
    /* Fotmato do cubo:
           P6
        P1-P2-P3-P4
           P5
    */
    glColor3f(cor[0],cor[1],cor[2]);
	     
	     
   glBegin(GL_TRIANGLE_FAN);     
        // P1
        //glColor3f(1,0,0); // vermelho
        
        glVertex3f(aresta/2, -aresta/2, aresta/2); //esquerda, baixo, fundo
        glVertex3f(aresta/2, -aresta/2, -aresta/2); //esquerda, baixo, frente
        glVertex3f(-aresta/2, -aresta/2, -aresta/2); //direita, baixo, frente
        
        glVertex3f(aresta/2, -aresta/2, aresta/2); //esquerda, baixo, fundo
        glVertex3f(-aresta/2, -aresta/2, -aresta/2); //direita, baixo, frente
        glVertex3f(-aresta/2, -aresta/2, aresta/2); //direita, baixo, funco
   glEnd();     
   glBegin(GL_TRIANGLE_FAN);
		// P2
		//glColor3f(0,1,0); // verde
		
		glVertex3f(aresta/2, -aresta/2, aresta/2); //esquerda, baixo, fundo
		glVertex3f(-aresta/2, -aresta/2, aresta/2); //direita, baixo, funco
		glVertex3f(-aresta/2, aresta/2, aresta/2); //direita, cima, funco
				
		glVertex3f(aresta/2, aresta/2, aresta/2); //esquerda, cima, funco
		glVertex3f(aresta/2, -aresta/2, aresta/2); //esquerda, baixo, fundo
		glVertex3f(-aresta/2, aresta/2, aresta/2); //direita, cima, funco
	glEnd();    
    glBegin(GL_TRIANGLE_FAN);
		// P3
		//glColor3f(0,0,1); // azul
		
	    glVertex3f(-aresta/2, -aresta/2, aresta/2); //direita, baixo, fundo
	    glVertex3f(-aresta/2, -aresta/2, -aresta/2); //direita, baixo, frente
	    glVertex3f(-aresta/2, aresta/2, -aresta/2); //direita, cima, frente
	    
	    glVertex3f(-aresta/2, -aresta/2, aresta/2); //direita, baixo, fundo
	    glVertex3f(-aresta/2, aresta/2, -aresta/2); //direita, cima, frente
	    glVertex3f(-aresta/2, aresta/2, aresta/2); //direita, cima, fundo
    glEnd();
    glBegin(GL_TRIANGLE_FAN);     
        // P4
        //glColor3f(1,1,1); // branco
        
        glVertex3f(aresta/2, aresta/2, aresta/2); //esquerda, cima, fundo
        glVertex3f(aresta/2, aresta/2, -aresta/2); //esquerda, cima, frente
        glVertex3f(-aresta/2, aresta/2, -aresta/2); //direita, cima, frente
        
        glVertex3f(aresta/2, aresta/2, aresta/2); //esquerda, cima, fundo
        glVertex3f(-aresta/2, aresta/2, -aresta/2); //direita, cima, frente
        glVertex3f(-aresta/2, aresta/2, aresta/2); //direita, cima, funco
   glEnd(); 
   glBegin(GL_TRIANGLE_FAN);     
	    // P5
	    //glColor3f(1,1,0); // amarelo
	    
	    glVertex3f(aresta/2, -aresta/2, aresta/2); //esquerda, baixo, fundo
	    glVertex3f(aresta/2, -aresta/2, -aresta/2); //esquerda, baixo, frente
	    glVertex3f(aresta/2, aresta/2, -aresta/2); //esquerda, cima, frente
	    
	    glVertex3f(aresta/2, -aresta/2, aresta/2); //esquerda, baixo, fundo
	    glVertex3f(aresta/2, aresta/2, -aresta/2); //esquerda, cima, frente
	    glVertex3f(aresta/2, aresta/2, aresta/2); //esquerda, cima, fundo
   glEnd();    
   glBegin(GL_TRIANGLE_FAN);  
        // P6
        //glColor3f(0,1,1); // ciano
        
		glVertex3f(aresta/2, -aresta/2, -aresta/2); //esquerda, baixo, frente
		glVertex3f(-aresta/2, -aresta/2, -aresta/2); //direita, baixo, frente
		glVertex3f(-aresta/2, aresta/2, -aresta/2); //direita, cima, frente
				
		glVertex3f(aresta/2, aresta/2, -aresta/2); //esquerda, cima, frente
		glVertex3f(aresta/2, -aresta/2, -aresta/2); //esquerda, baixo, frente
		glVertex3f(-aresta/2, aresta/2, -aresta/2); //direita, cima, frente
   glEnd();  

   glPopMatrix(); //Deixa a matriz como ela estava antes  
}

void desenhaCone(objetoGrafico* og){
    printAviso(og, "Espessura e tipografia ainda nao implementadas");

    glPushMatrix(); //Salva a matriz
    aplicaCorTransformacoesPadrao(og);
     
    float* cor         = getCor(og);
    float* corAlt      = &getValoresExtra(og)[0];
    float  raio        = getValoresExtra(og)[3];
    float  altura      = getValoresExtra(og)[4];
    float  reparticoes = getValoresExtra(og)[5];
    float angle,x,y;
    int iPivot=0;
    
    const float pi=3.1415f;
    
    /* Abaixo tirado do exemplo "GlutTEST - 07 - CONE", corrigido um bug em que,
     se o numero de reparticoes fosse muito pequeno, ocasionaria na falta de 
     uma repartição */
    
    // Desenhando a base do cone
    glBegin(GL_TRIANGLE_FAN);
    // Centro do FAN é a origem (0,0,0)
    glVertex2f(0.0f, 0.0f);
    
    angle = -(pi/reparticoes);
    do{
        angle = min(angle+(pi/reparticoes),(2.0f*pi));
    	// Calculate x and y position of the next vertex
    	x = raio*sin(angle);
    	y = raio*cos(angle);
    	// Alternate color between red and green
    	if((iPivot %2) == 0) glColor3f(cor[0], cor[1], cor[2]);
    	else                 glColor3f(corAlt[0],corAlt[1], corAlt[2]);
    	// Increment pivot to change color next time
    	iPivot++;
    	// Specify the next vertex for the triangle fan
    	glVertex2f(x, y);
    }while(angle < (2.0f*pi));
    
    glEnd();
    
    // Desenhando a lateral do cone
    glBegin(GL_TRIANGLE_FAN);
    // Pinnacle of cone is shared vertex for fan, moved up Z axis
    // to produce a cone instead of a circle
    glVertex3f(0.0f, 0.0f, altura);
    // Loop around in a circle and specify even points along the circle
    // as the vertices of the triangle fan
    angle = -(pi/reparticoes);
    do{
        angle = min(angle+(pi/reparticoes),(2.0f*pi));
    	// Calculate x and y position of the next vertex
    	x = raio*sin(angle);
    	y = raio*cos(angle);
        // Alternate color between red and green
    	if((iPivot %2) == 0) glColor3f(cor[0], cor[1], cor[2]);
    	else                 glColor3f(corAlt[0],corAlt[1], corAlt[2]);
    	// Increment pivot to change color next time
    	iPivot++;
    	// Specify the next vertex for the triangle fan
    	glVertex2f(x, y);
    }while(angle < (2.0f*pi));
    glEnd();

    glPopMatrix(); //Deixa a matriz como ela estava antes     
}

void desenhaTorus(objetoGrafico* og){
    printf("ERRO: Tipo nao implementado(tipo=%c,id=%d)\n", og->tipo, og->id);
}
