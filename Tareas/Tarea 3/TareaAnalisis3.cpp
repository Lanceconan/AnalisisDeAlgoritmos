/*
DATOS DES PROGRAMA

NOMBRE          : TareaAnalisis3.cpp correspondiente a la tercera tarea de Cátedra
FECHA ENTREGA   : Domingo  6 de Abril 2014
UTEM

Programa probado y testeado en un notebook HP con Windows 8 | 64 bit | 4GB de RAM

Advertencia:
Se utiliza la funcion 'system' para limpiar pantallas temporalmente y la funcion getchar para hacer una pausa: Se sugiere
eliminar estas funciones cuando se utiliza sistema operativo Linux o similar pero la apariencia fisica se verá notablemente perjudicada.

*/

/*Librerias utilizadas*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXFILACOLUMNA 40000
#define MAXVECTOR 100

/*Variables Globales*/
int ElementoActual = 1; /*Pivote usado para intercambiar la cabecera del vector con el elemento correspondiente*/
int PivoteSuperior, PivoteInferior; /*Pivote usado para tener una referencia de donde se realiza el intercambio parcial*/
int N, K;
unsigned long long CalculoCombinatoria = 0;
int Vector[MAXVECTOR]; /* Vector que guarda el vector de entrada*/
int VectorTemporal [MAXVECTOR]; /*Vector que guarda la combinatoria parcial*/

/*Funcion recursiva que indica la combinacion actual y suma el resultado total de combinaciones */
void Combinatoria(int numero, int indice, int longitud){
  int i, Tempo = 0, Temporal, AuxNumero;
  if (longitud == K)
  {
    CalculoCombinatoria++;
    AuxNumero = numero;
    //printf("\t\t\t\t%d \n", numero);
    printf("\n\t\t");
    while(AuxNumero > 0)
    {
        VectorTemporal[Tempo] = AuxNumero%10;
        AuxNumero = (int)AuxNumero/10;
        Tempo++;
    }
    Temporal = Tempo-1;
    while(Temporal >= 0)
    {
        printf(" %d ", Vector[VectorTemporal[Temporal]-1]);
        Temporal--;
    }

  }

  else
  {
    for (i = indice; i <= N; i++) Combinatoria(numero*10+i,i+1,longitud+1);
  }
}

/*Funcion para generar numeros aleatorios*/
void generar_Elementos(int componentes)
{
    int RecorreVector;
    for(RecorreVector = 0; RecorreVector < componentes; RecorreVector++) Vector[RecorreVector] = 0;
    srand (time(NULL));
    for(RecorreVector = 0; RecorreVector < componentes; RecorreVector++) Vector [RecorreVector] =  rand() % 10;
}

/*Funcion principal*/
int main (void)
{
    int i, C, PivoteVector,SumaGrande;
    char NN[3], KK[3];
    Principio:

    system("cls");
    printf("\n\n\t\t==================================================\n");
    printf("\t\t  Ingrese Valores Validos N > K con K menor a 10\n");
    printf("\t\t==================================================\n\n\n");

     printf("\t\tIngrese la cantidad de N: "); scanf("%s", &NN);
     printf("\n\t\tIngrese la cantidad de N: "); scanf("%s", &KK);
     N = atoi(NN);
     K = atoi(KK);
     if (N < K || K == 0 || N == 0 || K > 10)
     {
        printf("\n\n\t\tOpcion no Valida\n\t\tEnter para ingresar nuevamente");
        fflush(stdin);getchar();
        goto Principio;
     }
     clock_t start = clock();
     generar_Elementos(N);
     printf("\n\tEl vector generado es:\n\t");
     for(PivoteVector = 0;PivoteVector < N; PivoteVector++) printf("%d ",Vector[PivoteVector]);
     fflush(stdin);getchar();
     printf("\n\n\t\tLas combinaciones ordenadas son: \n\n");
     for (C=1; C<N;C++) Combinatoria(C,C+1,1);
     printf("\n\n\t\tLa cantidad de combinaciones de %d sobre %d son: %lu\n", N, K, CalculoCombinatoria);
    /*Aqui termina el esqueleto del algoritmo para mostrar los valores combinatorios*/

/*Tiempo de ejecucion del programa*/
printf("\n\n\n\t\tTiempo transcurrido de Computo es: %.5f", ((double)clock() - start) / CLOCKS_PER_SEC);

printf("\n\n\t\t=================================================\n");
printf("\t\t             Usted ha salido del programa\n\t\t                    Grupo ALIAS\n");
printf("\t\t=================================================\n");
fflush(stdin);getchar();
return 0;
}
