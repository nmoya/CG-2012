#ifndef OBJETOGRAFICO_H
#define OBJETOGRAFICO_H

#define MAX_VALORES 50

#define NPONTO 3

#define TPONTO     'P'
#define TLINHA     'L'
#define TCIRCULO   'C'
#define TESFERA    'E'
#define TRETANGULO 'R'
#define TTRIANGULO 'T'
#define TCUBO      'Q'
#define TCONE      'O'
#define TTORUS     'U'

// Numero de argumentos padrao
#define NCOR        3
#define NESPESSURA  1
#define NTIPOGRAFIA 1
#define NORIENTACAO 4
#define NTRANSLACAO 3
#define NARGSCOMUNS (NCOR+NESPESSURA+NTIPOGRAFIA+NORIENTACAO+NTRANSLACAO)

// Indice dos argumentos
#define ICOR 0
#define IESPESSURA  (ICOR+NCOR)
#define ITIPOGRAFIA (IESPESSURA+NESPESSURA)
#define IORIENTACAO (ITIPOGRAFIA+NTIPOGRAFIA)
#define ITRANSLACAO (IORIENTACAO+NORIENTACAO)
#define IRESTO      (ITRANSLACAO+NTRANSLACAO)

typedef struct{
    int id;
    char tipo;
    float valores[MAX_VALORES]; // R;G;B;Espessura;Tipografia;Orientacao[4];Translacao[3];p1x;p1y;p1z;p2x;p2y;p3z;...
} objetoGrafico;                //Espessura == 0 -> solido

static float* getCor(objetoGrafico* og)         { return &og->valores[ICOR]; }
static float  getEspessura(objetoGrafico* og)   { return  og->valores[IESPESSURA]; }
static float  getTipografia(objetoGrafico* og)  { return  og->valores[ITIPOGRAFIA]; }
static float* getOrientacao(objetoGrafico* og)  { return &og->valores[IORIENTACAO]; }
static float* getTranslacao(objetoGrafico* og)  { return &og->valores[ITRANSLACAO]; } 
static float* getValoresExtra(objetoGrafico* og){ return &og->valores[IRESTO];}

static float  ehSolido(objetoGrafico* og)       { return  og->valores[IESPESSURA] == 0; }

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
        case TPONTO:     return NCOR+NESPESSURA+1*NPONTO; //3cor + 1espessura + 1xyz?
		case TLINHA:     return NARGSCOMUNS+2*NPONTO; 
		case TCIRCULO:   return -1; 
		case TESFERA:    return -1; 
		case TRETANGULO: return -1;
		case TTRIANGULO: return NARGSCOMUNS+3*NPONTO; //3cor + 1epessura + 1tipografia + 3orientacao + 3translacao + 3xyz
		case TCUBO:      return NARGSCOMUNS+1;  //3cor + 1epessura + 1tipografia + 3orientacao + 3translacao + aresta
		case TCONE:      return NARGSCOMUNS+1*NCOR+1+1+1;  //+ corAlternativa + raio + altura + reparticoes
		case TTORUS:     return -1; 
        default: return -1;
    }
}

static void desenhaObjetoGrafico(objetoGrafico* og){
    switch(og->tipo){
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
