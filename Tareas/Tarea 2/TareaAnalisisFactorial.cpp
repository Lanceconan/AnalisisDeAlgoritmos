/*
DATOS DES PROGRAMA
NOMBRE          : TareaAnalisisFactorial.cpp correspondiente a la segunda tarea de Cátedra
FECHA ENTREGA   : Domingo  6 de Abril 2014
UTEM

Programa probado y testeado en un notebook HP con Windows 8 | 64 bit | 4GB de RAM

Advertencia:
Se utiliza la funcion 'system' para limpiar pantallas temporalmente y la funcion getchar para hacer una pausa: Se sugiere
eliminar estas funciones cuando se utiliza sistema operativo Linux o similar pero la apariencia fisica se verá notablemente perjudicada.

*/

/*Librerias utilizadas*/
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/*Variables de tipo estaticas*/
#define MAXVECTOR 10000
#define MAX 100

//using namespace std;

/*Creacion de una estructura GranNumb, con un enterp del tipo puntero v y un entero n*/
struct GranNumb {
	int *v;
	int n;
};

/*SECCION DE FUNCIONES*/

GranNumb granprod(GranNumb fact_1, GranNumb fact_2) {
	int *v, n;
	n = (fact_1.n > fact_2.n) ? 2*fact_1.n : 2*fact_2.n;
	v = new int[n];
    /*Comparacion de valor de fact_1.n con fact_2.n, si el primero es mayor se multiplica por dos
    y se asigna a n, en caso contrario, se multiplica fact_2.n por dos y se añade a n.*/
	for(int i=0; i<n; i++) v[i] = 0;
    //pro es igual a la multiplicacion de lo que hay en la casilla v[i] por v[j], mas

	for(int i=0; i<fact_1.n; i++) {
		for(int j=0; j<fact_2.n; j++) {
			int prod = fact_1.v[i] * fact_2.v[j] + v[i+j]; //el valor de la casilla v [i+j*]
			int u = prod % 10; //finalmente el valor en la casilla v[i+j], es el resto de prod divido por 10
			int d = prod / 10; //y el valor de la casilla c[i+j+1] es la suma de su valor mas la division de prod por 10
			v[i+j] = u;
			v[i+j+1] += d;
		}
	}

	GranNumb gn;
	gn.n = 0;
	gn.v = v;

	for(int i=n-1; i>=0; i--) { //funion que recorre el vector v, y verifica que el valor de cada casilla sea distinto
		if(v[i] != 0) { // de 0, en caso de no serlo, al valor de gn.n se le añade i+1
			gn.n=i+1; // realizando una interrupcion del for.
			break;
		}
	}

	return gn;
}

GranNumb grandec(GranNumb gn) {
	int *v = new int [gn.n];
	for(int i=0; i<gn.n; i++) v[i] = gn.v[i];

	if(gn.n == 0) {
		return gn;
	} else {
		for(int i=0; i<gn.n; i++) {
			if(v[i] == 0) {
				v[i] = 9;
			} else {
				v[i]--;
				break;
			}
		}
	}

	GranNumb dec;
	dec.n = 0;
	dec.v = v;
	for(int i=gn.n-1; i>=0; i--) {
		if(v[i] != 0) {
			dec.n=i+1;
			break;
		}
	}
	return dec;
}

/* Funcion Factorial, en caso de que el n ingresado sea 0 devuelve 1, si no lo es, devuelve el factorial del numero*/
GranNumb granfact(GranNumb gn) {
	if( gn.n == 0) {
		GranNumb uno;
		uno.n = 1;
		uno.v = new int[1];
		uno.v[0] = 1;
		return uno;
	} else {
		return granprod(gn, granfact(grandec(gn)));
	}
}




/*Funcion para pasar un caracter de los valores de entrada a entero*/
int PasarEntero(char c)
{
    return c - 48;
}
/*Funcion para sumar parcial digito a digito entre la multiplicacion parcial y acumulada dejandolo en un solo digito*/
int SumarDigitos(int aa, int bb, int ccarry)
{
    int SSumarAux = aa + bb + ccarry;
    if (SSumarAux > 9)return ((int)SSumarAux%10);
    else return SSumarAux;
}
/*Funcion obetener el acarreo de la suma de la multiplicacion parcial y acumulada dejandolo en un solo digito*/
int AcarreoSuma(int aa, int bb, int ccarry)
{
    int SSumarAux = aa + bb + ccarry;
    //printf("\nSuma para acarreo [%d] + [%d] + [%d] = %d\n", aa, bb, ccarry, SSumarAux);
    if (SSumarAux > 9) return ((int)SSumarAux/10);
    else return 0;
}
/*Funcion para calcular la multiplicacion parcial de dos digitos entregando solo la unidad del resultado*/
int MultiplicarDigitos(int a, int b, int carry)
{
    int MultAux = (a * b) + carry;
    if (MultAux > 9)return ((int)MultAux%10);
    else return MultAux;
}

int Acarreo(int a, int b, int carry, int limite)
{
    int MultAux = (a * b) + carry;
    if (MultAux > 9 || limite == 0) return ((int)MultAux/10);
    else return 0;
}

/*FIN DE SECCION DE FUNCIONES*/

/*FUNCION PRINCIPAL*/
int main (void)
{
    char NumA [1000], NumB [1000], s [MAX];
    int jj, ll, m, Suma, RefLargoNumC = 0, CarA = 0, CarB = 0, LargoA = 0, LargoB = 0, LargoC = 0, i = 0, j = 0, Aca = 0, AcaSuma = 0, PivoteC;
    int AcarreoAux = 0, opcion, NumF, NumFactor [10], PivoteB = 0, AuxNumC [MAXVECTOR], NumC [MAXVECTOR];
    long MultParcial;
    clock_t start, stop;
    GranNumb gn;
    GranNumb fact;

    /*Identificacion de Variables NO Nemotecnicas:

    NumA            : primer numero ingresado por teclado
    NumB            : Segundo numero ingresado por teclado
    NumC            : Array donde se almacena el resultado final de la multiplicacion grande
    AuxNumC         : Valor donde se guarda la multiplicacion parcial entre el NumA y CarB segun la posicion i
    CarA            : Numero parcial de la Cadena NumA indicada por la posicion i
    CarB            : Numero parcial de la Cadena NumB indicada por la posicion j
    i               : Pivote y limite superior en recorrido de cadena NumA ingresada por teclado
    j               : Pivote y limite superior en recorrido de cadena NumB ingresada por teclado
    m               : Multiplicacion parcial los dgitos enteros CarA y CarB mas su correspondiente acarreo
    RefLargoNumC    : Variable Auxuliar para recorrer el NumC
    PivoteC         : Recorrido del Array AuxNumC
    start           : variable que lleva el conteo en segundos para un proceso
    Aca-AcaSuma     : Variables auxiliares utilizadas para guardar acarreo de las multilicacion o suma parcial.
    */

    for(i = 0; i < MAXVECTOR; i++)
    {
        NumC[i] = 0;
        AuxNumC [i]= 0;
    }
    do
    {
    system("cls");
    printf("\n\n\t\t=================================================\n");
    printf("\t\t             Ingrese una opcion Valida\n");
    printf("\t\t=================================================\n\n\n");

    printf("\t\t1 - Factorial de un Numero Grande\n");
    printf("\t\t2 - Multiplicacion de dos Numeros grandes\n");
    printf("\t\t3 - Salir");
    printf("\n\n\t\tIngrese Opcion y presione Enter: ");
    fflush(stdin);char c = getchar();
    opcion = PasarEntero(c);
    switch(opcion)
    {

    /*EN CASO DE QUERER OBTENER UN FACTORIAL DE UN NUMERO BASTANTE GRANDE POR EJEMPLO 3000 SE UTILIZARA ESTA SECCION DE CODIGO

    EXPLICACION:

    */
    case 1:
    start = 0;
    start = clock();         /*Se inicia el conteo de tiempo de ejecucion del programa*/
	printf("\n\n\tIngresar Nro: ");
	scanf("%s", s);
	gn.n = strlen(s);
	gn.v = new int[gn.n];
	for(ll=0; ll<gn.n; ll++) gn.v[ll] = (int)s[gn.n-1-ll] - 48; //convierte caracter en cifra

    fact = granfact(gn);
    printf("\n\n\t");
	for(ll=fact.n-1; ll>=0; ll--)
    {
		printf("%d", fact.v[ll]);
	}
	stop = clock();
	printf("\n\nTiempo transcurrido de Computo fue: %.10f\n\nPresione un tecla para continuar\n\n", ((double)stop - start) / CLOCKS_PER_SEC);
    printf("\n\n");
    fflush(stdin);getchar();
    break;

    case 2:
      /*EN CASO DE QUERER MULTIPLICAR DOS NUMEROS GRANDES EL PROGRAMA EJECUTARA ESTAS INSTRUCCIONES DE A CONTINUACION

    EXPLICACION: La multiplicacion se realiza tal cual se hace con un lapiz y papel. Para ejemplificar:
    NumA = 12 | NumB = 12

    12 x 2 = 24 y se almacena en AuxNumC = 24 para luego sumarlo con NumC = 000
    luego
    12 x 1 = 12 y se almacena en AuxNumC = 12 multiplicandolo por la potencia de 10 correspondiente a su posicion en num C para luego sumarlo con NumC = 024

    finalmente:

      024
    + 120
    -----
      144
    */
    for(i = 0; i < MAXVECTOR; i++)
    {
        NumC[i] = 0;
        AuxNumC [i]= 0;
    }
    printf("\n\n\tIngrese el 1er Numero: ");
    scanf("%s", NumA);
    printf("\n\tIngrese el 2do Numero: ");
    scanf("%s", NumB);
    start = clock();        /*Se inicia el conteo de tiempo de ejecucion del programa*/
    LargoA = strlen(NumA);
    LargoB = strlen(NumB);
    j = LargoB - 1;
    while(j >= 0)
    {
    /*En este While se van seleccionando los caracteres de la cadena NumB en orden de valor unidad|decena|centena|así sucesivamente
    y se va multiplicando digito a digito con los caracteres de la cadena NumA ingresada por teclado
    */
    CarB = PasarEntero(NumB[j]);
    i = LargoA - 1;
    PivoteC = RefLargoNumC;
    RefLargoNumC++;
    Aca = 0;
    while(i >= 0)
    {
    /*En este While se van seleccionando los caracteres de la cadena NumA en orden de valor unidad|decena|centena|así sucesivamente
    y se va multiplicando digito a digito por el caracter sacado de la cadena NumB
    */
       CarA = PasarEntero(NumA[i]);
       AuxNumC[PivoteC] = MultiplicarDigitos(CarA,CarB, Aca);
       Aca = Acarreo(CarA,CarB, Aca,i);
       m = (CarA*CarB) + Aca;
       i--;
       PivoteC++;
    }
    if(m > 10) AuxNumC[PivoteC] = Aca;

    /**/
    AcaSuma = 0;
    for(i = 0; i <  MAXVECTOR; i++)
    {
        int temporalC = NumC[i];
        NumC[i] = SumarDigitos(temporalC, AuxNumC[i], AcaSuma);
        AcaSuma = AcarreoSuma(temporalC, AuxNumC[i], AcaSuma);
    }
    /**/

    j--;
    for(i = 0; i < MAXVECTOR; i++) AuxNumC[i] = 0;
    }
    printf("\n\nEl numero Total es:\n\n");
    jj = MAXVECTOR - 100;
    while(NumC[jj] == 0)
    {
        jj--;
    }

    while(jj >= 0)
    {
        printf("%d",NumC[jj]);
        jj--;
    }
    printf("\n\nTiempo transcurrido de Computo fue: %.10f\n\nPresione un tecla para continuar\n\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    printf("\n\n");
    fflush(stdin);getchar();
    break;

    case 3:
    /*Opcion para salir del programa*/
    system("cls");
    printf("\n\n\t\t=================================================\n");
    printf("\t\t             Usted ha salido del programa\n\t\t                    Grupo ALIAS\n");
    printf("\t\t=================================================\n");
    break;

    default:
    /*Opcion para cuando no se ingresa una opcion valida en el menu*/
    system("cls");
    printf("\n\n\t\t=================================================\n");
    printf("\t\t       Opcion no valida, ingrese nuevamente\n");
    printf("\t\t=================================================\n");
    fflush(stdin); getchar();
    break;
    }
    }while (opcion != 3);
    return 0;
}

/*FIN DE PROGRAMA Y DE FUNCION PRINCIPAL*/
