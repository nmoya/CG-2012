#ifndef OBJETOGRAFICO_H
#define OBJETOGRAFICO_H

#define MAX_VALORES 50

#define NPONTO 3

#define TPONTO      'P'
#define TLINHA      'L'
#define TCIRCULO    'C'
#define TESFERA     'E'
#define TQUADRADO   'Q'
#define TTRIANGULO  'T'
#define TCUBO       'U'
#define TCONE       'O'
#define TTORUS      'S'
#define TCILINDRO   'I'
#define TKOMPOSTO   'K'
#define TILUMINACAO 'M'

// Numero de argumentos padrao
#define NCOR        3
#define NESPESSURA  1
#define NTIPOGRAFIA 1
#define NORIENTACAO 4
#define NTRANSLACAO 3
#define NARGSCOMUNS (NCOR+NESPESSURA+NTIPOGRAFIA+NORIENTACAO+NTRANSLACAO)

#define NILUMINACAO (4*2+4) //corAmbiente+corLuz+posicao

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
void desenhaCilindro(objetoGrafico* og);
void desenhaKomposto(objetoGrafico* og);
void configuraIluminacao(objetoGrafico* og);

static int numParametros(char tipo){
    switch(tipo){ //XXX preencher numero de parametros correto
        case TPONTO:     return NCOR+1*NPONTO; //3cor + 1espessura + 1xyz?
		case TLINHA:     return NARGSCOMUNS+2*NPONTO;    // OKA
		case TCIRCULO:   return NARGSCOMUNS+1*NCOR+1+1;  //+ corAlternativa + raio + reparticoes INCOMPLETO
		case TESFERA:    return NARGSCOMUNS+1+1;  //raio + reparticoes // OKA
		case TQUADRADO:  return NARGSCOMUNS+1+1; //corAlternativa + largura + altura 
		case TTRIANGULO: return NARGSCOMUNS+3*NPONTO; //3cor + 1epessura + 1tipografia + 3orientacao + 3translacao + 3xyz // OKA
		case TCUBO:      return NARGSCOMUNS+1; //INCOMPLETO
		case TCONE:      return NARGSCOMUNS+1*NCOR+1+1+1;  //+ corAlternativa + raio + altura + reparticoes // INCOMPLETO
		case TTORUS:     return NARGSCOMUNS+1+1+1+1;  //raioInterno + raioExterno + reparticoes + aneis // OKA
		case TCILINDRO:  return NARGSCOMUNS+1*NCOR+1+1+1;  //+ corAlternativa + raio + altura + reparticoes INCOMPLETO
		case TKOMPOSTO:  return NARGSCOMUNS+1+1 +  /* Esfera do pirulito =)*/  
                         1*NCOR+1+1+1; // Cilindro do pirulito =)
        case TILUMINACAO:return NILUMINACAO;
        default: return -1;
    }
}

static void desenhaObjetoGrafico(objetoGrafico* og){
    switch(og->tipo){
        case TPONTO:     return desenhaPonto(og); 
		case TLINHA:     return desenhaLinha(og); 
		case TCIRCULO:   return desenhaCirculo(og); 
		case TESFERA:    return desenhaEsfera(og); 
		case TQUADRADO:  return desenhaRetangulo(og); 
		case TTRIANGULO: return desenhaTriangulo(og);
		case TCUBO:      return desenhaCubo(og); 
		case TCONE:      return desenhaCone(og); 
		case TTORUS:     return desenhaTorus(og); 
		case TCILINDRO:  return desenhaCilindro(og);
		case TKOMPOSTO:  return desenhaKomposto(og);
		case TILUMINACAO:return configuraIluminacao(og);
    }
    printf("ERRO: Tipo nao implementado(tipo=%c,id=%d)\n", og->tipo, og->id);
}


#endif
