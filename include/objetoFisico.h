#ifndef OBJETOFISICO_H
#define OBJETOFISICO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
        float angx, angy, angz; /*** http://www.eletrica.ufpr.br/ufpr2/professor/49/TE224/Aula%202%20Vetores.pdf ***/
        float velocidade; /*** http://pt.wikipedia.org/wiki/Equa%C3%A7%C3%A3o_de_Torricelli ***/ //Velocidade em funcao da aceleracao
        float forca;
        float massa;
        float aceleracao;
} vetForca;

typedef struct
{
  vetForca * angsForc;
  int lenAngsForc;
} objetoFisico;

#endif
