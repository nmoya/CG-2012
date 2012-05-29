#ifndef OBJETOGRAFICO_H
#define OBJETOGRAFICO_H

#define MAX_VALORES 50

typedef struct{
    int id;
    char tipo;
    float valores[MAX_VALORES]; // R;G;B;Espessura;Tipografia;Orientacao;p1x;p1y;p1z;p2x;p2y;p3z;...
} objetoGrafico;

static int numParametros(char tipo){
    switch(tipo){ //XXX preencher numero de parametros correto
        case 'P': return 3; //Ponto
		case 'L': return -1; //Linha
		case 'C': return -1; //Circulo
		case 'E': return -1; //Esfera
		case 'T': return -1; //Triangulo
		case 'R': return -1; //Retangulo
		case 'c': return -1; //[c]one
		case 't': return -1; //[t]órus
        default: return -1;
    }
}


#endif
