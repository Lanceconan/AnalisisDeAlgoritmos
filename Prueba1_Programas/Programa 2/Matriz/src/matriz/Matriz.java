/*
DATOS DES PROGRAMA
NOMBRE          : Matriz.java correspondiente a parte del 30% de la prueba 1
FECHA ENTREGA   : Miercoles  30 de Abril 2014
LUGAR           : UTEM

Programa probado y testeado en un notebook HP con Windows 8 | 64 bit | 4GB de RAM | IDE NeatBeans 8.0

PROBLEMATICA:

Dada una secuencia de matrices, encontrar la manera más eficiente para multiplicar 
estas matrices juntos. El problema no es en realidad para realizar las multiplicaciones, 
sino que se limita a decidir en qué orden para realizar las multiplicaciones.
*/

/*Paquete correspondiente a la clase*/
package matriz;

/*Librerias utilizadas en la clase Matriz.java*/
import java.util.Scanner;

/*Clase principal*/
public class Matriz {
    /*Metodo que define a la clase Matriz, como clase principal*/
    public static void main (String[] args) {
        // Variables estaticas
        int numMatrices;
        Scanner scan = new Scanner(System.in);
         
         
        // Menu de entrada del programa
        System.out.println ();
        System.out.println ("\t\t===========================================================");
        System.out.println (" \t\tPrograma para resolver Multiplicacion de Cadena de Matrices");
        System.out.println ("\t\t===========================================================");
        System.out.println ();

         
        System.out.print   ("\t\tIngrese cantidad de Matrices a multiplicar: ");
        numMatrices = scan.nextInt();
         
         
        // Declaracion de Variables Dinamicas (el tamaño cambia segun los valores ingresados)
        char[] matrices = new char[numMatrices]; 
         
        for (int i = 0; i < numMatrices; ++i)
            matrices[i] = (char)(i + 65);
         
        String[][] output = new String[numMatrices][numMatrices];
        double[][] matrix = new double[numMatrices][numMatrices];
         
        for (int i = 0; i < numMatrices; ++i)
            output[i][i] = Character.toString(matrices[i]);
         
        for (int i = 0; i < numMatrices; ++i)
            matrix[i][i] = 0;
         
        int[] dimension = new int[numMatrices + 1];
         
        System.out.print("\t\tIngrese el tamaño de las filas de la Matriz 1: ");
        dimension[0] = scan.nextInt();
         
        for (int i = 1; i < dimension.length; ++i) {
            System.out.print ("\t\tIngrese el tamaño de las columnas de la Matriz " + i + ": ");
            dimension[i] = scan.nextInt();
        }
         
        /*Segmento del codigo que se encarga de hacer la operatoria compleja con tal de encontrar 
        la operatoria sucesiva de matrices, con tal de encontrar la menor cantidad operatorias para conseguir la 
        multiplicacion de N matrices 
        
        Complejidad de tiempo: O (n ^ 3) 
        Espacio auxiliar: O (n ^ 2)
        
        */       
        System.out.println ();
        System.out.println ();
        for (int b = 1; b < numMatrices; ++b) {
            for (int i = 0; i < numMatrices - b; ++i) {
                int j = i + b;
                matrix[i][j] = Double.POSITIVE_INFINITY;
                for (int k = i; k < j; ++k) {
                    if (matrix[i][j] > matrix[i][k] + matrix[k + 1][j] + 
                        dimension[i] * dimension[k + 1] * dimension[j + 1])
                        output[i][j] = "(" + output[i][k] + output[k + 1][j] + ")";
                    matrix[i][j] = Math.min(matrix[i][j], matrix[i][k] + matrix[k + 1][j] + 
                    dimension[i] * dimension[k + 1] * dimension[j + 1]);
                }
            }
        }
         
         
        // Mostrar Resultados
        System.out.println("\tInterpretando AxB como AxB, tal como la notacion matematica, tenemos que:");
        System.out.println ("\n\tUsando Parentesis se tiene la siguiente multiplicacion " + output[0][numMatrices - 1] + 
                            " la cual realizara " + (int)matrix[0][numMatrices - 1] + " calculos.");
        System.out.println ("\t----------------------------------------------------------------------------------------------");
   
    }
}
