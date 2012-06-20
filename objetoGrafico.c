#include "include/objetoGrafico.h"

#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <gl/glu.h>			//Util library

//Funcoes ajudantes que imprimem o tipo e o id do objeto junto com uma mensagem de erro
void printErro(objetoGrafico* og, char* erro)  { printf("ERRO(id=%d, tipo=%c): %s\n", og->id, og->tipo, erro); }
void printAviso(objetoGrafico* og, char* erro) { printf("AVISO(id=%d, tipo=%c): %s\n", og->id, og->tipo, erro); }

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
    glPushMatrix(); //Salva a matriz
    aplicaCorTransformacoesPadrao(og);
     
    float* cor         = getCor(og);
    float *translacao = getTranslacao(og);
    float x = translacao[0], y = translacao[1], z = translacao[2];
    int iPivot=0;
    float base;
    glBegin(GL_POINTS);
    glVertex3f (x, y, z);
    glEnd();
    
    glPopMatrix(); //Deixa a matriz como ela estava antes
}

void desenhaLinhaOg(objetoGrafico* og, float *pontos[], int numPontos){
     int i;
     glBegin(GL_LINES);
         for(i=0;i<numPontos;i++){
             float* v = pontos[i];//verts[i];
             glVertex3f(v[0],v[1],v[2]);
         }
     glEnd();
}

void desenhaLinha(objetoGrafico* og){
     glPushMatrix(); //Salva a matriz    
     aplicaCorTransformacoesPadrao(og);

     int i;
     float* verts[2];
     for(i=0;i<2;i++){
        verts[i] = &getValoresExtra(og)[i*3];
     }
     desenhaLinhaOg(og, verts,2);
     glPopMatrix(); //Deixa a matriz como ela estava antes
}

void desenhaCirculo(objetoGrafico* og){
printAviso(og, "Espessura e tipografia ainda nao implementadas");
    glPushMatrix(); //Salva a matriz
    aplicaCorTransformacoesPadrao(og);
     
    float* cor         = getCor(og);
    float* corAlt      = &getValoresExtra(og)[0];
    float  raio        = getValoresExtra(og)[3];
    float  reparticoes = getValoresExtra(og)[4];
    float angle,x,y;
    int iPivot=0;
    float base;
   
    const float pi=3.1415f;
    float tamPart = 360/reparticoes;
     
    // Desenhando as base do cilindro
       // Base 1
    glBegin(GL_TRIANGLE_FAN);
    // Centro do FAN é a origem (0,0,0)
    glVertex2f(0.0f, 0.0f);
    //glVertex3f(0.0f, 0.0f, altura);
    
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
    	//glVertex3f(x, y,altura);
    }while(angle < (2.0f*pi));

    glEnd();
}

void desenhaEsfera(objetoGrafico* og){
    glPushMatrix(); //Salva a matriz
    aplicaCorTransformacoesPadrao(og);   
    float* cor         = getCor(og);
    float *translacao = getTranslacao(og);
    float  raio     = getValoresExtra(og)[0];
    float  reparticoes      = getValoresExtra(og)[1];
    float x = translacao[0], y = translacao[1], z = translacao[2];
    
    if(ehSolido(og)) glutSolidSphere(raio, reparticoes,reparticoes);
    else glutWireSphere(raio,reparticoes,reparticoes);
    glPopMatrix(); //Deixa a matriz como ela estava antes
}

void desenhaRetangulo(objetoGrafico* og){
    //printf("ERRO: Tipo nao implementado(tipo=%c,id=%d)\n", og->tipo, og->id);
    printAviso(og, "Espessura e tipografia ainda nao implementadas");
    glPushMatrix(); //Salva a matriz
    aplicaCorTransformacoesPadrao(og);
    
    float* cor         = getCor(og);
    float lado         = getValoresExtra(og)[0];
    float altura       = getValoresExtra(og)[1];
    float espessura    = getEspessura(og);
    float tipografia   = getTipografia(og);
    
    float p1[3];
   float p2[3];
   float * pontos[] = {p1,p2};
    
    glColor3f(cor[0],cor[1],cor[2]);
	
    if(espessura)
    {     
       p1[0]=lado/2; p1[1]=-altura/2; p1[2]=0;//esquerda, baixo   
       p2[0]=-lado/2; p2[1]=-altura/2; p2[2]=0;//direita, baixo       
       desenhaLinhaOg(og, pontos, 2);  
       
       p1[0]=lado/2; p1[1]=altura/2; p1[2]=0;//esquerda, cima   
       p2[0]=-lado/2; p2[1]=altura/2; p2[2]=0;//direita, cima       
       desenhaLinhaOg(og, pontos, 2);  
       
       p1[0]=lado/2; p1[1]=-altura/2; p1[2]=0;//esquerda, baixo   
       p2[0]=lado/2; p2[1]=altura/2; p2[2]=0;//esquerda, cima       
       desenhaLinhaOg(og, pontos, 2);  
       
       p1[0]=-lado/2; p1[1]=-altura/2; p1[2]=0;//direita, baixo   
       p2[0]=-lado/2; p2[1]=altura/2; p2[2]=0;//direita, cima       
       desenhaLinhaOg(og, pontos, 2);  
    }
    else
    {   
        glBegin(GL_TRIANGLE_FAN);     
            // P1
            //glColor3f(1,0,0); // vermelho        
    
            glVertex3f(lado/2, -altura/2, 0); //esquerda, baixo
            glVertex3f(-lado/2, -altura/2, 0); //direita, baixo
            glVertex3f(-lado/2, altura/2, 0); //direita, cima
            
            glVertex3f(lado/2, -altura/2, 0); //esquerda, baixo
            glVertex3f(-lado/2, altura/2, 0); //direita, cima
            glVertex3f(lado/2, altura/2, 0); //esquerda, cima
        glEnd();     
    }
    glPopMatrix(); //Deixa a matriz como ela estava antes
}

void desenhaTrianguloOg(objetoGrafico* og, float* verts[]){
     GLenum modoDesenho;
     int i;
     if(ehSolido(og)) modoDesenho = GL_TRIANGLES;
     else             modoDesenho = GL_LINE_LOOP;
     glBegin(modoDesenho);
         for(i=0;i<3;i++){
             float* v = verts[i];
             glVertex3f(v[0],v[1],v[2]);
         }
     glEnd();   
}

void desenhaTriangulo(objetoGrafico* og){
     glPushMatrix(); //Salva a matriz
     aplicaCorTransformacoesPadrao(og);     

     int i;
     float* verts[3];
     for(i=0;i<3;i++){
        verts[i] = &getValoresExtra(og)[i*3];
     }
    
     desenhaTrianguloOg(og, verts);
    
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
    //glColor3f(cor[0],cor[1],cor[2]);
	     
   float p1[3];
   float p2[3];
   float * pontos[] = {p1,p2};
   
	
   if(espessura)
   {
                //Esquerda
       p1[0]=aresta/2; p1[1]=-aresta/2; p1[2]=aresta/2;//esquerda, baixo, fundo   
       p2[0]=aresta/2; p2[1]=-aresta/2; p2[2]=-aresta/2;//esquerda, baixo, frente       
       desenhaLinhaOg(og, pontos, 2);  
       
       p1[0]=aresta/2; p1[1]=-aresta/2; p1[2]=aresta/2;//esquerda, baixo, fundo   
       p2[0]=aresta/2; p2[1]=aresta/2; p2[2]=aresta/2;//esquerda, cima, fundo       
       desenhaLinhaOg(og, pontos, 2);
       
       p1[0]=aresta/2; p1[1]=-aresta/2; p1[2]=-aresta/2;//esquerda, baixo, frente   
       p2[0]=aresta/2; p2[1]=aresta/2; p2[2]=-aresta/2;//esquerda, cima, frente
       desenhaLinhaOg(og, pontos, 2);
       
       p1[0]=aresta/2; p1[1]=aresta/2; p1[2]=aresta/2;//esquerda, cima, fundo   
       p2[0]=aresta/2; p2[1]=aresta/2; p2[2]=-aresta/2;//esquerda, cima, frente
       desenhaLinhaOg(og, pontos, 2);
                          //Direita
       p1[0]=-aresta/2; p1[1]=-aresta/2; p1[2]=aresta/2;//direita, baixo, fundo   
       p2[0]=-aresta/2; p2[1]=-aresta/2; p2[2]=-aresta/2;//direita, baixo, frente       
       desenhaLinhaOg(og, pontos, 2);  
       
       p1[0]=-aresta/2; p1[1]=-aresta/2; p1[2]=aresta/2;//direita, baixo, fundo   
       p2[0]=-aresta/2; p2[1]=aresta/2; p2[2]=aresta/2;//direita, cima, fundo       
       desenhaLinhaOg(og, pontos, 2);
       
       p1[0]=-aresta/2; p1[1]=-aresta/2; p1[2]=-aresta/2;//direita, baixo, frente   
       p2[0]=-aresta/2; p2[1]=aresta/2; p2[2]=-aresta/2;//direita, cima, frente
       desenhaLinhaOg(og, pontos, 2);
       
       p1[0]=-aresta/2; p1[1]=aresta/2; p1[2]=aresta/2;//direita, cima, fundo   
       p2[0]=-aresta/2; p2[1]=aresta/2; p2[2]=-aresta/2;//direita, cima, frente
       desenhaLinhaOg(og, pontos, 2);
       
                          //Centro (frente)
       p1[0]=aresta/2; p1[1]=aresta/2; p1[2]=-aresta/2;//esquerda, cima, frente   
       p2[0]=-aresta/2; p2[1]=aresta/2; p2[2]=-aresta/2;//direita, cima, frente       
       desenhaLinhaOg(og, pontos, 2);  
       
       p1[0]=aresta/2; p1[1]=-aresta/2; p1[2]=-aresta/2;//esquerda, baixo, frente   
       p2[0]=-aresta/2; p2[1]=-aresta/2; p2[2]=-aresta/2;//direita, baixo, frente       
       desenhaLinhaOg(og, pontos, 2); 
                          //Centro (fundo)
       p1[0]=aresta/2; p1[1]=aresta/2; p1[2]=aresta/2;//esquerda, cima, fundo   
       p2[0]=-aresta/2; p2[1]=aresta/2; p2[2]=aresta/2;//direita, cima, fundo       
       desenhaLinhaOg(og, pontos, 2);  
       
       p1[0]=aresta/2; p1[1]=-aresta/2; p1[2]=aresta/2;//esquerda, baixo, fundo   
       p2[0]=-aresta/2; p2[1]=-aresta/2; p2[2]=aresta/2;//direita, baixo, fundo       
       desenhaLinhaOg(og, pontos, 2); 
       
       
       // diagonal
       
       /*p2[0]=aresta/2;
       p2[1]=-aresta/2;
       p2[2]=aresta/2;//esquerda, baixo, fundo       
       
       p1[0]=-aresta/2;
       p1[1]=aresta/2;
       p1[2]=-aresta/2;//direita, cima, frente
       
       desenhaLinhaOg(og, p1, p2);      */   
   }
   else
   {
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
   }
   
    

   glPopMatrix(); //Deixa a matriz como ela estava antes  
}
void desenhaCone(objetoGrafico* og){
    glPushMatrix(); //Salva a matriz
    aplicaCorTransformacoesPadrao(og);
     
    float* cor         = getCor(og);
    float* corAlt      = &getValoresExtra(og)[0];
    float  raio        = getValoresExtra(og)[3];
    float  alturaOrg   = getValoresExtra(og)[4];
    float  reparticoes = getValoresExtra(og)[5];
    float angle[2], x,y;
    int iPivot=0,i,k;
    float altura[2] = {0, alturaOrg};
    
    const float pi=3.1415f;
    
    float vert1[] = {0,0,0};
    float vert2[] = {0,0,0};
    float vert3[] = {0,0,0};
    float * verts[3] ={ vert1, vert2, vert3 };

    angle[0] = 0;
    do{
       angle[1] = min(angle[0]+(pi/reparticoes),(2.0f*pi));
   	   //Cor alternando
       if((iPivot++ %2) == 0) glColor3f(cor[0], cor[1], cor[2]);
       else                   glColor3f(corAlt[0],corAlt[1], corAlt[2]);
       
       for(k=0;k<2;k++){
           vert1[2]=altura[k];
           for(i=0;i<2;i++){
              verts[i+1][0] = raio*sin(angle[i]);
              verts[i+1][1] = raio*cos(angle[i]);
           }
           desenhaTrianguloOg(og,verts);
       }
       angle[0]=angle[1];
    }while(angle[0] < (2.0f*pi));

    glPopMatrix(); //Deixa a matriz como ela estava antes     
}

void desenhaTorus(objetoGrafico* og){
    glPushMatrix(); //Salva a matriz
    aplicaCorTransformacoesPadrao(og);   
    float* cor         = getCor(og);
    float *translacao = getTranslacao(og);
    float  raioInterno     = getValoresExtra(og)[0];
    float  raioExterno     = getValoresExtra(og)[1];
    float  reparticoes      = getValoresExtra(og)[2];
    float  aneis      = getValoresExtra(og)[3];
    float x = translacao[0], y = translacao[1], z = translacao[2];
    
    if(ehSolido(og)) glutSolidTorus(raioInterno, raioExterno, reparticoes,aneis);
    else glutWireTorus(raioInterno, raioExterno, reparticoes,aneis);
    glPopMatrix(); //Deixa a matriz como ela estava antes
}

void desenhaCilindro(objetoGrafico* og){
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
    float base;
    objetoGrafico quad;
    
    const float pi=3.1415f;
    float tamPart = 360/reparticoes;
     
    // Desenhando as base do cilindro
       // Base 1
    glBegin(GL_TRIANGLE_FAN);
    // Centro do FAN é a origem (0,0,0)
    glVertex2f(0.0f, 0.0f);
    //glVertex3f(0.0f, 0.0f, altura);
    
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
    	//glVertex3f(x, y,altura);
    }while(angle < (2.0f*pi));

    glEnd();
       //Base 2

    glBegin(GL_TRIANGLE_FAN);
    // Centro do FAN é a origem (0,0,0)
    //glVertex2f(0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f+altura, 0.0f);
        
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
    	//glVertex2f(x, y);
    	glVertex3f(x, y+altura, 0.0 );
    }while(angle < (2.0f*pi));
    glEnd();
    
    // Faz as laterais do cilindro    
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
    	/*glShadeModel(GL_FLAT);
        glBegin(GL_QUADS);
                glVertex2f(-x, y);
                glVertex2f( x, y);
                glVertex2f( x,-y);
                glVertex2f(-x,-y);
        glEnd();*/   
    }while(angle < (2.0f*pi));

    glPopMatrix(); //Deixa a matriz como ela estava antes 
}
void desenhaKomposto(objetoGrafico *og){
    
    float *cor = getCor(og);
    float espessura = getEspessura(og);
    float tipografia = getTipografia(og);
    float *orientacao = getOrientacao(og);
    float *translacao = getTranslacao(og);
    float x = translacao[0], y = translacao[1], z = translacao[2];
    
    float raioE = getValoresExtra(og)[0];
    float reparticoesE = getValoresExtra(og)[1];
    
    float  corAlt[3];
           corAlt[0]    = getValoresExtra(og)[2];
           corAlt[1]    = getValoresExtra(og)[3];
           corAlt[1]    = getValoresExtra(og)[4];
    float  raioC        = getValoresExtra(og)[5];
    float  alturaC      = getValoresExtra(og)[6];
    float  reparticoesC = getValoresExtra(og)[7];
    
    objetoGrafico esfera, cilindro;
    
    //Monta esfera
    esfera.id = -1;
    esfera.tipo = TESFERA;
    esfera.valores[ICOR]            = cor[0];
    esfera.valores[ICOR+1]          = cor[1];
    esfera.valores[ICOR+2]          = cor[2];
    
    esfera.valores[IESPESSURA]      = espessura;
    esfera.valores[ITIPOGRAFIA]     = tipografia;
    
    esfera.valores[IORIENTACAO]     = orientacao[0];
    esfera.valores[IORIENTACAO+1]     = orientacao[1];
    esfera.valores[IORIENTACAO+2]     = orientacao[2];
    esfera.valores[IORIENTACAO+3]     = orientacao[3];
    
    esfera.valores[ITRANSLACAO]       = x;
    esfera.valores[ITRANSLACAO+1]     = y;
    esfera.valores[ITRANSLACAO+2]     = z;
    
    esfera.valores[IRESTO]            = raioE;
    esfera.valores[IRESTO+1]          = reparticoesE;
    
    desenhaEsfera(&esfera);
    
    //Monta Cilindro
    cilindro.id = -1;
    cilindro.tipo = TCILINDRO;
    cilindro.valores[ICOR]            = cor[0];
    cilindro.valores[ICOR+1]          = cor[1];
    cilindro.valores[ICOR+2]          = cor[2];
    
    cilindro.valores[IESPESSURA]      = espessura;
    cilindro.valores[ITIPOGRAFIA]     = tipografia;
    
    cilindro.valores[IORIENTACAO]     = orientacao[0];
    cilindro.valores[IORIENTACAO+1]     = orientacao[1];
    cilindro.valores[IORIENTACAO+2]     = orientacao[2];
    cilindro.valores[IORIENTACAO+3]     = orientacao[3];
    
    cilindro.valores[ITRANSLACAO]       = x;
    cilindro.valores[ITRANSLACAO+1]     = y;
    cilindro.valores[ITRANSLACAO+2]     = z;
    
    cilindro.valores[IRESTO]            = corAlt[0];
    cilindro.valores[IRESTO+1]          = corAlt[1];
    cilindro.valores[IRESTO+2]          = corAlt[2];

    cilindro.valores[IRESTO+3]          = raioC;
    cilindro.valores[IRESTO+4]          = alturaC;
    cilindro.valores[IRESTO+5]          = reparticoesC;
    
    desenhaCilindro(&cilindro);
    
}
