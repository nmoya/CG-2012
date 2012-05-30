#ifndef OBJETOGRAFICO_H
#define OBJETOGRAFICO_H

#define MAX_VALORES 50

#define TPONTO     'P'
#define TLINHA     'L'
#define TCIRCULO   'C'
#define TESFERA    'E'
#define TRETANGULO 'R'
#define TTRIANGULO 'T'
#define TCUBO      'Q'
#define TCONE      'O'
#define TTORUS     'U'

typedef struct{
    int id;
    char tipo;
    float valores[MAX_VALORES]; // R;G;B;Espessura;Tipografia;Orientacao[3];Translacao[3];p1x;p1y;p1z;p2x;p2y;p3z;...
} objetoGrafico;                //Espessura == 0 -> solido

static float* getCor(objetoGrafico* og)         { return &og->valores[0]; }
static float  getEspessura(objetoGrafico* og)   { return  og->valores[3]; }
static float  getTipografia(objetoGrafico* og)  { return  og->valores[4]; }
static float* getOrientacao(objetoGrafico* og)  { return &og->valores[5]; }
static float* getTranslacao(objetoGrafico* og)  { return &og->valores[8]; } 
static float* getValoresExtra(objetoGrafico* og){ return &og->valores[11];}

void desenhaPonto(objetoGrafico* og);
void desenhaLinha(objetoGrafico* og);
void desenhaCirculo(objetoGrafico* og);
void desenhaEsfera(objetoGrafico* og);
void desenhaRetangulo(objetoGrafico* og);
void desenhaTriangulo(objetoGrafico* og);
void desenhaCubo(objetoGrafico* og);
void desenhaCone(objetoGrafico* og);
void desenhaTorus(objetoGrafico* og);

static int numParametros(char tipo){
    switch(tipo){ //XXX preencher numero de parametros correto
        case TPONTO:     return 3+1+3; //3cor + 1espessura + 1xyz?
		case TLINHA:     return -1; 
		case TCIRCULO:   return -1; 
		case TESFERA:    return -1; 
		case TRETANGULO: return -1;
		case TTRIANGULO: return 3+1+1+3+3+3*3; //3cor + 1epessura + 1tipografia + 3orientacao + 3translacao + 3xyz
		case TCUBO:      return -1; 
		case TCONE:      return -1; 
		case TTORUS:     return -1; 
        default: return -1;
    }
}

static void desenhaObjetoGrafico(objetoGrafico* og){
    switch(og->tipo){ //XXX preencher numero de parametros correto
        case TPONTO:     return desenhaPonto(og); 
		case TLINHA:     return desenhaLinha(og); 
		case TCIRCULO:   return desenhaCirculo(og); 
		case TESFERA:    return desenhaEsfera(og); 
		case TRETANGULO: return desenhaRetangulo(og); 
		case TTRIANGULO: return desenhaTriangulo(og);
		case TCUBO:      return desenhaCubo(og); 
		case TCONE:      return desenhaCone(og); 
		case TTORUS:     return desenhaTorus(og); 
    }
    printf("ERRO: Tipo nao implementado(tipo=%c,id=%d)\n", og->tipo, og->id);
}


#endif
