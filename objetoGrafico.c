#include "include/objetoGrafico.h"

#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <gl/glu.h>			//Util library

//Funcoes ajudantes que imprimem o tipo e o id do objeto junto com uma mensagem de erro
void printErro(objetoGrafico* og, char* erro)  { printf("ERRO(id=%d, tipo=%c): %s\n", og->id, og->tipo, erro); }
void printAviso(objetoGrafico* og, char* erro){ printf("AVISO(id=%d, tipo=%c): %s\n", og->id, og->tipo, erro); }


//Funcoes de desenho
void desenhaPonto(objetoGrafico* og){
    printf("ERRO: Tipo nao implementado(tipo=%c,id=%d)\n", og->tipo, og->id);
}

void desenhaLinha(objetoGrafico* og){
    printf("ERRO: Tipo nao implementado(tipo=%c,id=%d)\n", og->tipo, og->id);
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
     printAviso(og, "Desconsiderando translacao, orientacao, preenchimento e tipografia (nao implementado)"); //XXX aprender a usar a pilha de matrizes
     float* cor = getCor(og);
     float* verts[3];
     int i;
     for(i=0;i<3;i++){
        verts[i] = &getValoresExtra(og)[i*3];
     }
     glBegin(GL_TRIANGLES);
         glColor3f(cor[0],cor[1],cor[2]);
         for(i=0;i<3;i++){
             float* v = verts[i];
             glVertex3f(v[0],v[1],v[2]);
         }
     glEnd();
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
