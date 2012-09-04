#include "include/grafo.h"

#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <gl/glu.h>			//Util library
#include <math.h>

grafo* carregaGrafo(int nElementos)
{
     int i;
     int j;
     grafo *g;
     g = (grafo*) malloc (sizeof(grafo));
     g->nElementos = nElementos;
     g->deslocamento = (float***) malloc(nElementos*sizeof(float**));
     g->posicionamento = (int***) malloc(nElementos*sizeof(int**));
     g->distancia = (float**) malloc(nElementos*sizeof(float*));
     for(i = 0; i < nElementos ; i++)
     {
             g->deslocamento[i] = (float**) malloc(nElementos*sizeof(float*));
             g->posicionamento[i] = (int**) malloc(nElementos*sizeof(int*));
             g->distancia[i] = (float*) malloc(nElementos*sizeof(float));
             for(j = 0 ; j < nElementos; j++)
             {
                   g->deslocamento[i][j] = (float*) malloc (3 *sizeof(float));
                   g->posicionamento[i][j] = (int*) malloc(3*sizeof(int));
             }
     }
     g->incx = 0;
     g->incz = 0;
     g->incy = 0;
     return g;
}
void atualizaGrafo (objetoGrafico* vetObjetos, grafo* g)
{
     int i, j;
     for (i =0 ; i< g->nElementos ; i++)
     {
         for (j = 0 ; j < g->nElementos ; j++)
         {
             g->deslocamento[i][j][0] = vetObjetos[i].bbox.centro[0] - vetObjetos[j].bbox.centro[0];
             g->deslocamento[i][j][1] = vetObjetos[i].bbox.centro[1] - vetObjetos[j].bbox.centro[1];
             g->deslocamento[i][j][2] = vetObjetos[i].bbox.centro[2] - vetObjetos[j].bbox.centro[2];
         }
     }
}
void analizaGrafo (grafo* g)
{
     int i, j;
     float *vet1;
     for (i =0 ; i< g->nElementos ; i++)
     {
         for (j = 0 ; j < g->nElementos ; j++)
         {
             vet1 = g->deslocamento[i][j];
             
             if (vet1[0] > 0)             //O objeto I esta a direta do objeto J
             {
                g->posicionamento[i][j][0] = DIR;
             }
             else                         //Esquerda
             {
                g->posicionamento[i][j][0] = ESQ;                                          
             }
             if (vet1[1] > 0)             //O objeto I esta acima do objeto J
             {
                g->posicionamento[i][j][1] = CIM;
             }
             else                         //Baixo
             {
                g->posicionamento[i][j][1] = BAI;
             }
             if (vet1[2] > 0)             //O objeto I esta a frente do objeto J
             {
                g->posicionamento[i][j][2] = FRE;
             }
             else                         //Atrás
             {
                g->posicionamento[i][j][2] = TRA;                                          
             }
         }
     }
}
void desalocaGrafo(grafo *g)
{
     int i, j;
     for ( i = 0; i < g->nElementos ; i++)
     {
         for (j = 0; j < 3; j++)
         {
             free(g->deslocamento[i][j]);
             free(g->posicionamento[i][j]);
         }
         free(g->deslocamento[i]);
         free(g->posicionamento[i]);
         free(g->distancia[i]);
      }
      free(g->deslocamento);
      free(g->posicionamento);
      free(g->distancia);
      free(g);
}

void imprimeGrafo(grafo *g)
{
     analizaGrafo (g);
     int i, j;
     printf("\nnElementos : %d\n",g->nElementos);
     printf("\t\t\tDeslocamento em X\n");
     printf("\t");
     for( j = 0 ; j < g->nElementos; j++)
     {
              printf("%d  ",j);
     }
     printf("\n");
     for ( i  = 0; i < g->nElementos ; i ++)
     {
         printf("%d\t",i);
         for( j = 0 ; j < g->nElementos; j++)
         {
              if (i == j)
                 printf("X  ");
              else
              printf("%.d  ",g->posicionamento[i][j][0]);
         }
         printf("\n");
     }
     
     printf("\t\t\tDeslocamento em Y\n");
     printf("\t");
     for( j = 0 ; j < g->nElementos; j++)
     {
              printf("%d  ",j);
     }
     printf("\n");
     for ( i  = 0; i < g->nElementos ; i ++)
     {
         printf("%d\t",i);
         for( j = 0 ; j < g->nElementos; j++)
         {
              if (i == j)
                 printf("X  ");
              else
              printf("%.d  ",g->posicionamento[i][j][1]);
         }
         printf("\n");
     }
     printf("\t\t\tDeslocamento em Z\n");
     printf("\t");
     for( j = 0 ; j < g->nElementos; j++)
     {
              printf("%d  ",j);
     }
     printf("\n");
     for ( i  = 0; i < g->nElementos ; i ++)
     {
         printf("%d\t",i);
         for( j = 0 ; j < g->nElementos; j++)
         {
              if (i == j)
                 printf("X  ");
              else
                  printf("%.d  ",g->posicionamento[i][j][2]);
         }
         printf("\n");
     }
}
