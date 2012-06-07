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
    printf("ERRO: Tipo nao implementado(tipo=%c,id=%d)\n", og->tipo, og->id);
}

void desenhaCone(objetoGrafico* og){
    printf("ERRO: Tipo nao implementado(tipo=%c,id=%d)\n", og->tipo, og->id);
}

void desenhaTorus(objetoGrafico* og){
    printf("ERRO: Tipo nao implementado(tipo=%c,id=%d)\n", og->tipo, og->id);
}
