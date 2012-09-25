#ifndef PARSER_H
#define PARSER_H

#include "grafo.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void calculaBBox(objetoGrafico *og){
     float h, l, p;
     float cx, cy, cz;
     cx = og->valores[ITRANSLACAO];
     cy = og->valores[ITRANSLACAO+1];
     cz = og->valores[ITRANSLACAO+2];     
     switch(og->tipo){
            case TESFERA:
                 l = og->valores[NARGSCOMUNS]*2 + OFFSET;
                 h = l;
                 p = h;
                 break; 
    		case TCUBO:    
                 l = og->valores[NARGSCOMUNS] + OFFSET ;
                 h = l;
                 p = h;
                 break;
    		case TTORUS:
                 l = (og->valores[NARGSCOMUNS]+og->valores[NARGSCOMUNS+1])*1.8 + OFFSET;
                 h =(og->valores[NARGSCOMUNS]+og->valores[NARGSCOMUNS+1])*1.8 + OFFSET;
                 p = h;
                 break;
    		case TCONE:    
                 l = og->valores[NARGSCOMUNS+1*NCOR] * 2;
                 h = l;
                 p = og->valores[NARGSCOMUNS+1*NCOR+1];
                 cz = cz + (p / 2);
                 break;
      		case TKOMPOSTO:
                 break;
            case TCHAO:
                 l = og->valores[IRESTO];
                 h = 1;
                 p = og->valores[IRESTO+1];      
                 break;
                 
                 
            case TPONTO:     
    		case TLINHA:      
    		case TCIRCULO:    
    		case TQUADRADO:  
    		case TTRIANGULO:
            case TILUMINACAO:
                 //printf("Aviso: Nao sao criadas Bouding Box para objetos 2d (tipo=%c,id=%d)\n", og->tipo, og->id);
                 og->bbox.centro[0] = cx;
                 og->bbox.centro[1] = cy;
                 og->bbox.centro[2] = cz;
                 og->bbox.l = 0;
                 og->bbox.h = 0;
                 og->bbox.p = 0;  
                 return;
    		case TCILINDRO:    
            case TANIMACAO:
                 og->bbox.centro[0] = 0;
                 og->bbox.centro[1] = 0;
                 og->bbox.centro[2] = 0;    
                 printf("ERRO: Tipo nao implementado(tipo=%c,id=%d)\n", og->tipo, og->id);            
                 return;
     }
     //printf("l:%f h:%f p:%f\n",l,h,p);
     og->bbox.l = l;
     og->bbox.h = h;
     og->bbox.p = p;        
    //Centro
    og->bbox.centro[0] = cx;
    og->bbox.centro[1] = cy;
    og->bbox.centro[2] = cz;
    
            //Pontos da frente da BB
                 
    //P1
    og->bbox.pontos[0]   = cx - l/2.0 +OFFSET;
    og->bbox.pontos[1] = cy + h/2.0 +OFFSET;
    og->bbox.pontos[2] = cz - p/2.0 +OFFSET;
    
    //P2
    og->bbox.pontos[ 1*3  ] = cx + l/2.0    +OFFSET;
    og->bbox.pontos[ 1*3+1] = cy + h/2.0  +OFFSET;
    og->bbox.pontos[ 1*3+2] = cz - p/2    +OFFSET;
    
    //P3
    og->bbox.pontos[ 2*3  ] = cx - l/2.0    +OFFSET;
    og->bbox.pontos[ 2*3+1] = cy - h/2.0    +OFFSET;
    og->bbox.pontos[ 2*3+2] = cz - p/2      +OFFSET;
    
    //P4
    og->bbox.pontos[ 3*3  ] = cx + l/2.0      +OFFSET;
    og->bbox.pontos[ 3*3+1] = cy - h/2.0      +OFFSET;
    og->bbox.pontos[ 3*3+2] = cz - p/2        +OFFSET;
    
    //P5
    og->bbox.pontos[ 4*3  ] = cx - l/2.0      +OFFSET;
    og->bbox.pontos[ 4*3+1] = cy + h/2.0      +OFFSET;
    og->bbox.pontos[ 4*3+2] = cz + p/2        +OFFSET;

    //P6
    og->bbox.pontos[ 5*3  ] = cx + l/2.0      +OFFSET;
    og->bbox.pontos[ 5*3+1] = cy + h/2.0      +OFFSET;
    og->bbox.pontos[ 5*3+2] = cz + p/2        +OFFSET;

    //P7
    og->bbox.pontos[ 6*3  ] = cx - l/2.0      +OFFSET;
    og->bbox.pontos[ 6*3+1] = cy - h/2.0      +OFFSET;
    og->bbox.pontos[ 6*3+2] = cz + p/2        +OFFSET;

    //P8
    og->bbox.pontos[ 7*3  ] = cx + l/2.0      +OFFSET;
    og->bbox.pontos[ 7*3+1] = cy - h/2.0      +OFFSET;
    og->bbox.pontos[ 7*3+2] = cz + p/2        +OFFSET;
}

static char* readUntil(FILE* arq, char c){
    int i=0;
    #define buffer_len 512
    static char buffer[buffer_len];
    for(i=0;i < buffer_len;){
        buffer[i] = fgetc(arq);
        if(i == 0 && buffer[i] == c){ //ignora se o primeiro caracter for o caracter de parada
            continue;
        }
        if(buffer[i] == '#'){ //Comentario
            while((buffer[i] = fgetc(arq)) != '\n');
        }
        if(buffer[i] == c || feof(arq)){
            buffer[i]=0;
            break;
        }
        i++;
    }
    //printf("buffer = '%s'\n", buffer);
    return buffer;
}

static objetoGrafico* carregaObjetosGraficos(FILE* arq, int* len){
    assert(arq);
    objetoGrafico* vetorObjetos;
    if(sscanf(readUntil(arq,'\n'), "%d",len) != 1) goto erro; //pega quantidade de objetos
    if(!(vetorObjetos = malloc(sizeof(objetoGrafico)*(*len)))) goto erro; //aloca
    int i,k,nParametros;
    objetoGrafico* og;
    
    #define readInt(intPtr) if(sscanf(readUntil(arq,';'), "%d", (intPtr)) !=1) goto erro
    #define readFloat(floPtr) if(sscanf(readUntil(arq,';'), "%f", (floPtr)) !=1) goto erro
    #define readChar(chrPtr) do{ *(chrPtr)=fgetc(arq); } while(*(chrPtr) == ';' || *(chrPtr) == ' ' || *(chrPtr) == '\n' )

    for(i=0;i<*len;i++){
        og = &vetorObjetos[i];
        og->quadroAtual=0;
        og->invisivel=0;
        readInt(&og->id);
        readChar(&og->tipo);
        if((nParametros = numParametros(og->tipo)) == -1) goto erro;
        for(k=0;k<nParametros;k++){
            readFloat(&og->valores[k]);
        }
        og->bbox.visivel = VISIBILIDADE;
        og->bbox.offset = OFFSET;
        og->noChao = 0;
        og->objFisico.lenAngsForc = 0;
        og->objFisico.angsForc = NULL;
        calculaBBox(og);
    }
    
    return vetorObjetos;
erro:
    printf("Ocorreu um erro ao processar o arquivo (sintaxe invalida?)\n");
    *len=0;
    return 0;
}

#endif
