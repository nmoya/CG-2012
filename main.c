#include "include/objetoGrafico.h"
#include "include/parser.h"

int main(){
    objetoGrafico* objetosGraficos;
    int objetosGraficos_len;
    FILE* arqEntrada = fopen("arquivoEntrada.txt","r");
    objetosGraficos = carregaObjetosGraficos(arqEntrada, &objetosGraficos_len);
    
    int i,k;
    printf("ID;tipo;*valores\n");
    for(i=0;i<objetosGraficos_len;i++){
        objetoGrafico* og;
        og = &objetosGraficos[i];
        printf("%d;%c;", og->id, og->tipo);
        for(k=0;k<numParametros(og->tipo);k++){ 
            printf("%f;", og->valores[k]);
        }
        printf("\n");
    }
    getc(stdin);
    return 0;
    
}
