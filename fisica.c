#include "include/fisica.h"

#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <gl/glu.h>			//Util library
#include <math.h>
#include <string.h>

float getTempo ()
{
      return ((float)clock()/CLOCKS_PER_SEC); 
}

float getTempoPassado ()
{
      return getTempo() - TEMPO_INICIAL;
}

void addForcas(objetoGrafico og[], int lenOG, vetForca vForca, char tipoNRecebe[])
{
     int i = 0, k = 0;
     for(;i < lenOG; i++)
     {
            for(k = 0; k < strlen(tipoNRecebe); k++)
                if(og[i].tipo == tipoNRecebe[k]) goto addForcas_continua;
            
            if(og[i].objFisico.lenAngsForc == 0)
                og[i].objFisico.angsForc = (vetForca *) malloc (sizeof(vetForca));
            else
                og[i].objFisico.angsForc = (vetForca *) realloc (og[i].objFisico.angsForc, (og[i].objFisico.lenAngsForc + 1) *  sizeof(vetForca));
                                
            og[i].objFisico.angsForc[og[i].objFisico.lenAngsForc].angx = vForca.angx;
            og[i].objFisico.angsForc[og[i].objFisico.lenAngsForc].angy = vForca.angy;
            og[i].objFisico.angsForc[og[i].objFisico.lenAngsForc].angz = vForca.angz;
            og[i].objFisico.angsForc[og[i].objFisico.lenAngsForc].aceleracao = vForca.aceleracao;
            og[i].objFisico.angsForc[og[i].objFisico.lenAngsForc].massa = (og[i].bbox.h + og[i].bbox.l + og[i].bbox.p) / 60.0;
            og[i].objFisico.angsForc[og[i].objFisico.lenAngsForc].forca = og[i].objFisico.angsForc[og[i].objFisico.lenAngsForc].aceleracao * og[i].objFisico.angsForc[og[i].objFisico.lenAngsForc].massa;
            og[i].objFisico.angsForc[og[i].objFisico.lenAngsForc].velocidade = vForca.velocidade;
            
            og[i].objFisico.lenAngsForc ++;
            addForcas_continua: continue;
     }
}

void aplicaAceleracao(objetoGrafico *og)
{
    int k = 0;
    for(k = 0; k < og->objFisico.lenAngsForc; k++)
    {
        
        og->objFisico.angsForc[k].velocidade += 
            //F = m * a;
            //Vi+1 = Vi + a * t        --> MRUV
            //V = (S - S0) / (t - t0)  --> MRU
        
            og->objFisico.angsForc[k].aceleracao * getTempoPassado(); //MRUV
            //printf("tempo: %f, velocidade: %f\n", getTempoPassado(), og->objFisico.angsForc[k].velocidade);
            //como faz pra movimentos diferentes??
    }
}

void moveObjeto (objetoGrafico *og)
{
     float ax, ay, az;
     int i;
     for(i = 0; i < og->objFisico.lenAngsForc; i++)
     {
        ax = cos(og->objFisico.angsForc[i].angx) * og->objFisico.angsForc[i].velocidade;
        ay = cos(og->objFisico.angsForc[i].angy) * og->objFisico.angsForc[i].velocidade;
        az = cos(og->objFisico.angsForc[i].angz) * og->objFisico.angsForc[i].velocidade;
        
        og->valores[ITRANSLACAO] = og->valores[ITRANSLACAO] + ax;
        og->valores[ITRANSLACAO+1] = og->valores[ITRANSLACAO+1] + ay;
        og->valores[ITRANSLACAO+2] = og->valores[ITRANSLACAO+2] + az;
     }
     
     /*float ax, ay, az;
     ax = cos(og->angx) * og->forca;
     ay = cos(og->angy) * og->forca;
     az = cos(og->angz) * og->forca;
     og->valores[ITRANSLACAO] = og->valores[ITRANSLACAO] + ax;
     og->valores[ITRANSLACAO+1] = og->valores[ITRANSLACAO+1] + ay;
     og->valores[ITRANSLACAO+2] = og->valores[ITRANSLACAO+2] + az;*/
}

