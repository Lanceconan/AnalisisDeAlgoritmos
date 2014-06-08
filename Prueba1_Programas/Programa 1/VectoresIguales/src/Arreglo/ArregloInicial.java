/*
DATOS DES PROGRAMA
NOMBRE          : Vector.cpp correspondiente a parte del 30% de la prueba 1
FECHA ENTREGA   : Miercoles  30 de Abril 2014
LUGAR           : UTEM

Programa probado y testeado en un notebook HP con Windows 8 | 64 bit | 4GB de RAM| IDE NeatBeans 8.0

PROBLEMATICA:

Generar a partir de un vector generar dos vectores tales que estos sumen lo mismo

ADVERTENCIAS:

1.- Se definio un maximo de elementos por el vector inicial 10000, puede extenderse mucho mas, pero no tiene
sentido alguno, puesto que para mostrarse adecuadamente por pantalla se recomienda usar valores no superiores a 100 para
comprobar la efectividad del algoritmo.

2.- Se sugiere usar un tamaño de 10 en el largo del vector y llenarlo manualmente con los siguientes valores:

2 - 4 - 6 - 12 - 6 - 8 - 4 - 10 - 16 - 0
*/

package Arreglo;

import java.io.*;
import java.util.Random;

/**
 *
 * @author Alias
 */
public class ArregloInicial {
/*Constantes*/
private static final int N = 10000;

/*Variables Globales*/
private static int Arreglo[], Parte1 [], Parte2[], ColaDePendientes[];
private static int PivoteParte1 = 0, PivoteParte2 = 0, PivoteDePendientes = 0, ValorMitad, CantidadEnCola = 0;
private static int SumaAcumuladaParte1, SumaAcumuladaParte2;
private static int MayorTemporal, ContadorParaNoDivision = 0;

/*Funcion que muestra los arreglos que suman igual*/
static void MostrarPartesIguales()
{
    int i, j;
    System.out.println("Vector 1: ");
    for (i = 0; i < PivoteParte1; i++) System.out.print("|" + Parte1[i]);
    System.out.print("|");
    System.out.println("\n\n");

    System.out.println("Vector 2: ");
    for (j = 0; j < PivoteParte2; j++) System.out.print("|" + Parte2[j]);
    System.out.print("|");
    System.out.println("\n\n");
}

/*Funcion que prueba la paridad de la suma de los componentes del vector,
con tal de saber si es factible o no hacer la segmentacion del vector inicial*/
static boolean CondicionPar(int largo)
{
    int i, Suma = 0;
    for(i = 0; i < largo; i++) Suma = Suma + Arreglo[i];
        ValorMitad = Suma/2;
    if (Suma%2 == 0) 
        return true;
    else return false;
}

/*Funcion que prueba la paridad de la suma de los componentes del vector,
con tal de saber si es factible o no hacer la segmentacion del vector inicial*/
static boolean CondicionNegPos(int largo)
{
    int i, Suma = 0;
    for(i = 0; i < largo; i++) Suma = Suma + Arreglo[i];
    if (Suma == 0) return true;
    else return false;
}

/*Funcion para llenar el Vector inicial manualmente [procesos tedioso]*/
@SuppressWarnings("empty-statement")
static void LlenarVectorManual(int largo) throws IOException
{
    
    int i;
    for(i = 0; i < largo; i++)
    {
        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader (isr);
        System.out.print("\t\tIngrese numero: ");        
        String cadena = br.readLine();
            Arreglo[i] = Integer.parseInt (cadena);
    }

    System.out.print("\n\t\tEl vector generado tienes los siguientes componentes:\n\n");
    for(i = 0; i < largo; i++) System.out.print("| " + Arreglo[i]); System.out.print("|");
}

/*Funcion para ir buscando el siguiente menor de los mayores*/
static void BuscarSiguienteValorMayor()
{
    int i, PosicionTemporal = 0;
    /*Guarda el siguiente mayor temporal dentro del vector inicial*/
    for(i = 0; i < 10000; i++)
    {
        if(Arreglo[i] >= MayorTemporal)
        {
            MayorTemporal = Arreglo[i];
            PosicionTemporal = i;
        }
    }
        Arreglo[PosicionTemporal] = 0;
        SumaAcumuladaParte1 = SumaAcumuladaParte1 - MayorTemporal;
    /*Se condiciona el valor de la mitad de la suma del vector inicial
    1.- Para cuando la resta del mayor encontrado sobrepasa la mitad de la suma de los componentes 
        del vector inicial Se guarda en una Pila mediante vector
    2.- En caso de ser igual a 0 se termina de guardar la parte1 y se guarda la parte 2
        con los valores sobrantes del vector inicial, ademas de la Pila creada con los valores no utilizados
    3.- Se guarda el valor temporal en la parte1
        
    */
    if(SumaAcumuladaParte1 < 0)
    {
            SumaAcumuladaParte1 = SumaAcumuladaParte1 + MayorTemporal;
            ColaDePendientes[CantidadEnCola] = MayorTemporal;
            CantidadEnCola++;
            ContadorParaNoDivision++;
    }
    else if (SumaAcumuladaParte1 == 0)
    {
            Parte1[PivoteParte1] = MayorTemporal;
            //PivoteParte1++;
        for(i = 0; i < 10000; i++)
        {
            if( Arreglo[i] != 0)
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

/*Funcion para limpiar los vectores - No usada*/
static void LimpiarVectores() throws IOException
{
    int i;
    for(i = 0; i <= N; i++)
    {
        
        Arreglo[i] = 0;
        Parte1[i] = 0;
        Parte2[i] = 0;
        ColaDePendientes[i] = 0;
        
    }
}

/*Funcion para llenar el Vector automaticamente con la funcion rand*/
static void LlenarVector(int largo)
{
    int i, TemporalRnd;
    Random rand = new Random();
    int  n = rand.nextInt(50) + 1;
    
    for(i = 0; i < largo; i++) 
    {
        TemporalRnd = rand.nextInt(99) + 10;
        Arreglo[i] = TemporalRnd; 
    
    }
    System.out.print("\n\t\tEl vector generado tienes los siguientes componentes:\n\n");
    for(i = 0; i < largo; i++) System.out.print("|" + Arreglo[i]); System.out.print("|");
}

public static void main(String args[]) throws IOException
{
    int Largo, cero, OpcionEntrada, ReferenciaParaNoDivision;
    Parte1 = new int[N];
    Parte2 = new int[N];
    Arreglo = new int[N];
    ColaDePendientes = new int[N];  
    InputStreamReader dale = new InputStreamReader(System.in);
    BufferedReader hola;
    hola = new BufferedReader(dale);
    
    System.out.println("\t\t=================================================");
    System.out.println("\t\t   Segmentando un Vector en dos partes cuyos\n\t\t\t     componentes sumen lo mismo");
    System.out.println("\t\t=================================================\n\n\n");
    System.out.print("\t\tIngrese el tamanio del vector: ");
    Largo = Integer.parseInt (hola.readLine());
    /*Segmento donde se decide si llenar la matriz manualmente o por azar*/
    System.out.println("\n\t\t1 - poblar el vector Manualmente");
    System.out.println("\t\t2 - Poblar el vector automaticamente");
    opcion:
    System.out.print("\n\t\tIngrese Opcion y presione Enter: ");
    OpcionEntrada = Integer.parseInt (hola.readLine());
    //LlenarVector(Largo);
    if(OpcionEntrada == 1) LlenarVectorManual(Largo);
    else if (OpcionEntrada == 2) LlenarVector(Largo);
    

    /*En este segmento se condiciona la paridad de la suma de los componentes del vector inicial
    sabiendo de antemano si es posible o no segmentar el vector*/
    if (CondicionPar(Largo) == false || CondicionNegPos(Largo) == true)
    {
        System.out.println("\n\n\t\tNo se puede segmentar el vector inicial en dos partes iguales\n\n\t\tIntentelo nuevamente\n\n");
    }
    else
    {
        System.out.println("\n\n\t\tSe puede segmentar el vector inicial\n\t\tpor lo tanto podriamos encontrar dos vectores\n\t\tque sumen lo mismo.\n");
        System.out.print("\t\tEl valor por cada uno de los segmentos debe ser: " + ValorMitad);
        SumaAcumuladaParte1 = ValorMitad;
        SumaAcumuladaParte2 = ValorMitad;

        for (cero = 0; cero < Largo; cero++)
        {
            if( Arreglo[cero] == 0)
            {
                    Parte2[PivoteParte2] = 0;
                    PivoteParte2++;
            }

        }
        /*Segmento principal del programa, el cuarl repetira la busqueda del mayor hasta que la mitad del
        vector inicial, o sea, la sumatoria de las partes del vector 1 sea igual a la mitad del vector inicial
        en caso de no poder segmetarse, retornara un mensaje de no poder segmentar el vector inicial*/
        do
        {
            MayorTemporal = Arreglo[0];
            BuscarSiguienteValorMayor();
            ReferenciaParaNoDivision = PivoteParte1 + ContadorParaNoDivision;
        /*Se termina este bucle cuando se encuentra la solucion o cuando no se encuentra*/    
        }
        while(0!= SumaAcumuladaParte1 && PivoteParte1 < ReferenciaParaNoDivision);

            if (SumaAcumuladaParte1 == 0)
            {
                System.out.println("\n\t\tLos vectores segmentados son: \n\n");
                MostrarPartesIguales();
            }
            else System.out.println("\n\n\t\tNo se pueden segmentar finalmente los vectores en dos partes iguales\n\n\t\tIntentelo Nuevamente\n\n");

    }
}
}