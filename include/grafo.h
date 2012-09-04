#include <stdio.h>
#include <stdlib.h>
#include "include/objetoGrafico.h"

#define DIR 1
#define ESQ 2
#define FRE 3
#define TRA 4
#define CIM 5
#define BAI 6

typedef struct
{
        int nElementos;
        float ***deslocamento;
        int ***posicionamento;
        float **distancia;
        float incx, incy, incz;
} grafo;


grafo* carregaGrafo(int nElementos);
void calculaAngulos(grafo* g, objetoGrafico* og1, objetoGrafico* og2);
void imprimeGrafo(grafo *g);
void desalocaGrafo(grafo *g);
void atualizaGrafo (objetoGrafico* vetObjetos, grafo* g);
