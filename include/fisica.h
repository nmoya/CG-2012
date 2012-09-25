#ifndef FISICA_H
#define FISICA_H

#include "objetoGrafico.h"
#include <time.h>

#define GRAVIDADE 0.05
#define PI        3.1415926535897932384626433832795028841971693993751058

#define TEMPO_INICIAL 0

void addForcas(objetoGrafico og[], int lenOG, vetForca vForca, char tipoNRecebe[]);
void aplicaAceleracao(objetoGrafico *og);
void moveObjeto (objetoGrafico *og);
float getTempo();
float getTempoPassado();


#endif

