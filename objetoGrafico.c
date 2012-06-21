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
     GLfloat corMat[]    = {cor[0],cor[1],cor[2],1.f};
     GLfloat emission[]  = {0,0,0,0};
     
     //Cor, material e transformacoes
     glColor3f(cor[0],cor[1],cor[2]);
     glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corMat);
     //glMaterialfv(GL_FRONT, GL_EMISSION, emission);
     glTranslatef(trans[0],trans[1],trans[2]);
     glRotatef(orient[0],orient[1],orient[2],orient[3]);

     //Configuracoes de linha
     glLineStipple(1, tipografia);
     glLineWidth(espessura);
}

//Funcoes de desenho
void desenhaPonto(objetoGrafico* og){
    glPushMatrix(); //Salva a matriz
    //aplicaCorTransformacoesPadrao(og);
     
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
             float* v;
             if(i > 1){
                  v=pontos[i-1];//verts[i];
                  glVertex3f(v[0],v[1],v[2]);
             }
             v=pontos[i];
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
    // Centro do FAN � a origem (0,0,0)
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
    //glEnable(GL_LIGHTING);
    aplicaCorTransformacoesPadrao(og);   
    float* cor         = getCor(og);
    float *translacao = getTranslacao(og);
    float  raio     = getValoresExtra(og)[0];
    float  reparticoes      = getValoresExtra(og)[1];
    float x = translacao[0], y = translacao[1], z = translacao[2];
    
    if(ehSolido(og)) glutSolidSphere(raio, reparticoes,reparticoes);
    else glutWireSphere(raio,reparticoes,reparticoes);
    //glDisable(GL_LIGHTING);
    glPopMatrix(); //Deixa a matriz como ela estava antes
}


void desenhaTrianguloOg(objetoGrafico* og, float* verts[]){
     GLenum modoDesenho;
     int i,k;
     if(ehSolido(og)) modoDesenho = GL_TRIANGLES;
     else             modoDesenho = GL_LINE_LOOP;
     float u[3],v[3],norm[3],magnitude;
     #define vcopy(v1,v2) memcpy(v1,v2,sizeof(float)*3)
     #define  vdif(v1,v2) for(k=0;k<3;k++) v1[k]=v2[k]-v1[k]
     #define magn(v)      sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2])
     
     //Calculo da normal
     vcopy(u,verts[1]); vdif(u,verts[0]);
     vcopy(v,verts[2]); vdif(v,verts[0]);
     norm[0] = u[1]*v[2] - u[2]*v[1];
     norm[1] = u[2]*v[0] - u[0]*v[2];
     norm[2] = u[0]*v[1] - u[1]*v[0];
     magnitude = magn(norm);
     for(k=0;k<3;k++) norm[k]/=magnitude;


     glBegin(modoDesenho);
         glNormal3d(norm[0],norm[1],norm[2]);
         for(i=0;i<3;i++){
             float* v = verts[2-i];
             glVertex3f(v[0],v[1],v[2]);
         }
     glEnd();   
}

void desenhaTrianguloOgInvNorm(objetoGrafico* og, float* vOrg[]){
     float* verts[3] = {vOrg[0],vOrg[2],vOrg[1]};
     desenhaTrianguloOg(og,verts);
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

void desenhaRetanguloOg(objetoGrafico* og, float* verts[]){ 
     int i,k;
     float vertsInterno[4][3];
     float * ponto[] ={ vertsInterno[0], vertsInterno[1], vertsInterno[2], vertsInterno[3], vertsInterno[0] };
     for(i=0;i<4;i++){
         for(k=0;k<3;k++){
             ponto[i][k] = verts[i][k];
         }
     }
     if(ehSolido(og))
     {
         desenhaTrianguloOg(og, ponto);
         desenhaTrianguloOg(og, &(ponto[1]));
     }
     else{
          ponto[3]=vertsInterno[2];
          ponto[2]=vertsInterno[3];
          desenhaLinhaOg(og,ponto,5);
          
     }
}

void desenhaRetangulo(objetoGrafico* og){
    //printf("ERRO: Tipo nao implementado(tipo=%c,id=%d)\n", og->tipo, og->id);
    printAviso(og, "Espessura e tipografia ainda nao implementadas");
    glPushMatrix(); //Salva a matriz
    aplicaCorTransformacoesPadrao(og);
    float lado         = getValoresExtra(og)[0];
    float altura       = getValoresExtra(og)[1];
    float vertsInterno[4][3] ={
          {-lado/2,-altura/2,0},
          {lado/2,-altura/2,0},
          {-lado/2,altura/2,0},
          {lado/2,altura/2,0}
    };
    float * ponto[] ={ vertsInterno[0], vertsInterno[1], vertsInterno[2], vertsInterno[3] };
    desenhaRetanguloOg(og,ponto);
    glPopMatrix(); //Deixa a matriz como ela estava antes
}

void desenhaCubo(objetoGrafico* og){
    glPushMatrix(); //Salva a matriz
    aplicaCorTransformacoesPadrao(og);
    int i;
    float aresta       = getValoresExtra(og)[0];
    
   float vertsInterno[4][3] = {
         {aresta/2,-aresta/2,aresta/2},
         {aresta/2,-aresta/2,-aresta/2},
         {aresta/2,aresta/2,aresta/2},
         {aresta/2,aresta/2,-aresta/2}
   };
   float * ponto[] ={ vertsInterno[0], vertsInterno[1], vertsInterno[2], vertsInterno[3] };
   
   desenhaRetanguloOg(og,ponto);

   for(i=0;i<4;i++) vertsInterno[i][0]*=-1;
   desenhaRetanguloOg(og,ponto);
   
   for(i=0;i<2;i++){
        vertsInterno[i][0]*=-1;
        vertsInterno[i][1]*=-1;
   }
   desenhaRetanguloOg(og,ponto);
   
   for(i=0;i<4;i++) vertsInterno[i][1]*=-1;
   desenhaRetanguloOg(og,ponto);
   
   for(i=0;i<4;i+=2){
        vertsInterno[i][1]*=-1;
        vertsInterno[i][2]*=-1;
   }
   desenhaRetanguloOg(og,ponto);
   
   for(i=0;i<4;i++) vertsInterno[i][2]*=-1;
   desenhaRetanguloOg(og,ponto);

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
    GLfloat corMat[]    = {cor[0],cor[1],cor[2],1.f};
    GLfloat corAltMat[]    = {corAlt[0],corAlt[1],corAlt[2],1.f};
    float angle[2], x,y;
    int iPivot=0,i,k;
    float altura[2] = {alturaOrg,0};
    
    const float pi=3.1415f;
    
    float vert1[] = {0,0,0};
    float vert2[] = {0,0,0};
    float vert3[] = {0,0,0};
    float * verts[3] ={ vert1, vert2, vert3 };
    #define setVerts(v0,v1,v2) verts[0]=v0; verts[1]=v1; verts[2]=v2

    angle[0] = 0;
    do{
       angle[1] = min(angle[0]+(pi/reparticoes),(2.0f*pi));
   	   //Cor alternando
       if((iPivot++ %2) == 0) {
            glColor3f(cor[0], cor[1], cor[2]);
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corMat);
       }
       else{
            glColor3f(corAlt[0],corAlt[1], corAlt[2]);
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corAltMat);
       }
       
       for(k=0;k<2;k++){
           vert1[2]=altura[k];
           for(i=0;i<2;i++){
              verts[i+1][0] = raio*sin(angle[i]);
              verts[i+1][1] = raio*cos(angle[i]);
           }
           if(altura[k] == 0) desenhaTrianguloOgInvNorm(og,verts);
           else               desenhaTrianguloOg(og,verts);
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
    // Centro do FAN � a origem (0,0,0)
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
    // Centro do FAN � a origem (0,0,0)
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
