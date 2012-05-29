#ifndef PARSER_H
#define PARSER_H

#include "objetoGrafico.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static char* readUntil(FILE* arq, char c){
    int i=0;
    #define buffer_len 512
    static char buffer[buffer_len];
    for(i=0;i < buffer_len;i++){
        buffer[i] = fgetc(arq);
        if(i == 0 && buffer[i] == c){
            buffer[i]=' ';
        }
        if(buffer[i] == c || feof(arq)){
            buffer[i]=0;
            break;
        }
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
        readInt(&og->id);
        readChar(&og->tipo);
        if((nParametros = numParametros(og->tipo)) == -1) goto erro;
        for(k=0;k<nParametros;k++){
            readFloat(&og->valores[k]);
        }
    }
    
    return vetorObjetos;
erro:
    printf("Ocorreu um erro ao processar o arquivo (sintaxe invalida?)\n");
    *len=0;
    return 0;
}

#endif
