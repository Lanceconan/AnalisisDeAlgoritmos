/*
DATOS DES PROGRAMA
NOMBRE          : Vector.cpp correspondiente a parte del 30% de la prueba 1
FECHA ENTREGA   : Miercoles  30 de Abril 2014
LUGAR           : UTEM

Programa probado y testeado en un notebook HP con Windows 8 | 64 bit | 4GB de RAM

ADVERTENCIAS:

1.- Se definio un maximo de elementos por el vector inicial 10000, puede extenderse mucho mas, pero no tiene
sentido alguno, puesto que para mostrarse adecuadamente por pantalla se recomienda usar valores no superiores a 100 para
comprobar la efectividad del algoritmo.

2.- Para valores mayores, se sugiere cambiar las variables int por "long long" o en u defecto "unsigned long long"
y cambiar la constante N por el valor deseado+1.

3.- Se sugiere usar un tamaño de 10 en el largo del vector y llenarlo manualmente con los siguientes valores:

2 - 4 - 6 - 12 - 6 - 8 - 4 - 10 - 16 - 0

/*Librerias utilizadas*/
#include <stdio.h>
#include <time.h>
#include<stdlib.h>
#include<iostream>

/*Constantes*/
#define N 10000

/*Variables Globales*/
int Arreglo[N], Parte1 [N], Parte2[N], ColaDePendientes[N];
int PivoteParte1 = 0, PivoteParte2 = 0, PivoteDePendientes = 0, ValorMitad, CantidadEnCola = 0;
int SumaAcumuladaParte1, SumaAcumuladaParte2;
int MayorTemporal;
bool Salir;

/*Funcion que muestra los arreglos que suman igual*/
void MostrarPartesIguales()
{
    int i, j;
    printf("Vector 1: ");
    for (i = 0; i < PivoteParte1; i++)printf("| %d ", Parte1[i]);
    printf("|");
    printf("\n\n");

    printf("Vector 2: ");
    for (j = 0; j < PivoteParte2; j++) printf("| %d ", Parte2[j]);
    printf("|");
    printf("\n\n");
}


/*Funcion que prueba la paridad de la suma de los componentes del vector,
con tal de saber si es factible o no hacer la segmentacion del vector inicial*/
bool CondicionPar(int largo)
{
    int i, Suma = 0;
    for(i = 0; i < largo; i++) Suma = Suma + Arreglo[i];
    ValorMitad = Suma/2;
    if (Suma%2 == 0) return true;
    else return false;
}

/*Funcion que prueba la paridad de la suma de los componentes del vector,
con tal de saber si es factible o no hacer la segmentacion del vector inicial*/
bool CondicionNegPos(int largo)
{
    int i, Suma = 0;
    for(i = 0; i < largo; i++) Suma = Suma + Arreglo[i];
    if (Suma == 0) return true;
    else return false;
}


/*Funcion para llenar el Vector inicial manualmente [procesos tedioso]*/
void LlenarVectorManual(int largo)
{
    int i;
    for(i = 0; i < largo; i++)
    {
        printf("\n\t\tIngrese el [%d]er numero: ", i+1);
        scanf("%d", &Arreglo[i]);
    }

    printf("\n\t\tEl vector generado tienes los siguientes componentes:\n\n");
    for(i = 0; i < largo; i++) printf("| %d ", Arreglo[i]); printf("|");
}

/*Funcion para ir buscando el siguiente menor de los mayores*/
void BuscarSiguienteValorMayor(void)
{
    int i, PosicionTemporal = 0;
    for(i = 0; i < N; i++)
    {
        if(Arreglo[i] >= MayorTemporal)
        {
            MayorTemporal = Arreglo[i];
            PosicionTemporal = i;
        }
    }
    Arreglo[PosicionTemporal] = 0;
    SumaAcumuladaParte1= SumaAcumuladaParte1 - MayorTemporal;

    if(SumaAcumuladaParte1 < 0)
    {
        SumaAcumuladaParte1 = SumaAcumuladaParte1 + MayorTemporal;
        ColaDePendientes[CantidadEnCola] = MayorTemporal;
        CantidadEnCola++;
    }
    else if (SumaAcumuladaParte1 == 0)
    {
        Parte1[PivoteParte1] = MayorTemporal;
        PivoteParte1++;
        for(i = 0; i < N; i++)
        {
            if(Arreglo[i] != 0)
            {
            Parte2[PivoteParte2] = Arreglo[i];
            Arreglo[i] = 0;
            PivoteParte2++;
            }
        }
        for(i = 0; i < CantidadEnCola; i++)
        {
            Parte2[PivoteParte2] = ColaDePendientes[i];
            PivoteParte2++;
            SumaAcumuladaParte2 = SumaAcumuladaParte2 - Arreglo[i];
        }
    }
    else
    {
    Parte1[PivoteParte1] = MayorTemporal;
    PivoteParte1++;
    }

}

/*Funcion para comprobar si los componentes del vector inicial esta vacio, como condicion
de termino del programa */
bool EstaVacioVectorInicial(void)
{
    int i;
    bool condicion = true;
    for(i = 0; i <= N; i++)
    {
        if(Arreglo[i] != 0) condicion = false;
    }
    return condicion;
}

/*Funcion para llenar el Vector automaticamente con la funcion rand*/
void LlenarVector(int largo)
{
    int i;
    for(i = 0; i < largo; i++) Arreglo[i] = rand() % (100-10);
    printf("\n\t\tEl vector generado tienes los siguientes componentes:\n\n");
    for(i = 0; i < largo; i++) printf("| %d ", Arreglo[i]); printf("|");
}
int main()
{
    int Largo, cero;
    char c;
    printf("\n\n\t\t=================================================\n");
    printf("\t\t   Segmentando un Vector en dos partes cuyos\n\t\t\t     componentes sumen lo mismo\n");
    printf("\t\t=================================================\n\n\n");
    printf("\t\tIngrese el tamanio del vector: ");
    scanf("%d", &Largo);
    /*Segmento donde se decide si llenar la matriz manualmente o por azar*/
    printf("\n\t\t1 - poblar el vector Manualmente\n");
    printf("\t\t2 - Poblar el vector automaticamente\n");
    opcion:
    printf("\n\n\t\tIngrese Opcion y presione Enter: ");
    fflush(stdin); c = getchar();
    if(c == '1') LlenarVectorManual(Largo);
    else if (c == '2') LlenarVector(Largo);
    else
    {
        printf("\n\n\t\tNo disponible la opcion digitada");
        goto opcion;
    }

    /*En este segmento se condiciona la paridad de la suma de los componentes del vector inicial
    sabiendo de antemano si es posible o no segmentar el vector*/
    if (CondicionPar(Largo) == false || CondicionNegPos(Largo) == true)
    {
        printf("\n\n\t\tNo se puede segmentar el vector inicial en dos partes iguales\n\n\t\tIntentelo nuevamente\n\n");
        return 0;
    }
    else
    {
        printf("\n\n\t\tSe puede segmentar el vector inicial\n\t\tpor lo tanto podriamos encontrar dos vectores\n\t\tque sumen lo mismo.\n\n");
        printf("\n\t\tEl valor por cada uno de los segmentos debe ser: %d\n\n", ValorMitad);
        SumaAcumuladaParte1 = ValorMitad;
        SumaAcumuladaParte2 = ValorMitad;

        for (cero = 0; cero < Largo; cero++)
        {
            if(Arreglo[cero] == 0)
            {
                Parte2[PivoteParte2] = 0;
                PivoteParte2++;
            }

        }
        do
        {
            MayorTemporal = Arreglo[0];
            BuscarSiguienteValorMayor();
            Salir = EstaVacioVectorInicial();
        }
        while(SumaAcumuladaParte1 != 0);

            if (SumaAcumuladaParte1 == 0 || SumaAcumuladaParte2 == 0)
            {
                printf("Los vectores segmentados son: \n\n");
                MostrarPartesIguales();
            }
            else printf("\n\n\t\tNo se pueden segmentar finalmente los vectores en dos partes iguales\n\n\t\tIntentelo Nuevamente\n\n");

    }

    return 0;
}
