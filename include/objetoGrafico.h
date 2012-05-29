#ifndef OBJETOGRAFICO_H
#define OBJETOGRAFICO_H

#define MAX_VALORES 100

typedef struct{
    int id;
    char tipo;
    float valores[MAX_VALORES]; // R;G;B;Espessura;Tipografia;Orientacao;p1x;p1y;p1z;p2x;p2y;p3z;
} objetoGrafico;

static int numParametros(char tipo){
    switch(tipo){
        case 'P': return 4; //Linha, Ponto, Circulo, Esfera, Triangulo, Retangulo, cone, tórus
        default: return -1;
    }
}


#endif
