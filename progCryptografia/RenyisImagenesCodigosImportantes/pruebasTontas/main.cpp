/*
 * File:   main.c
 * Author: daniel
 *
 * Created on 19 de octubre de 2013, 01:48 AM
 * Este programa mide el tamanio de ciclos del Mapa Caotico
 * Renyi Map para enteros.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



/*Definimos una macro para generar datos con Renyi Map.
Como se ocupan los 32 bits, es necesaria la mascara.
 */
#define RENYI_MAP(var, parametro, j) ((var)*(parametro)+((var)>>(j)))


/*El siguiente metodo calcula el parametro  a multiplicar:
q*(2 a la (n-i))*/
unsigned long calcular_parametro(unsigned long q, unsigned int n, unsigned int i){

    unsigned long potencia =1;
    unsigned int j;
    for(j =0; j<(n-i); j++){
        potencia*=2;
    }
    unsigned long parametro = q*(potencia);
    return parametro;
}



    FILE * archivoResultados;
    FILE * archivoGraficar;

    unsigned long parametro;
    unsigned long valorGrande=5000000;
    unsigned long var;
    unsigned long p;
    unsigned long x0=0x00000001;
    unsigned long valorABuscar;
    unsigned long long contador=0;
    unsigned long long TAMANIOCICLO = 4294967296;   // pow(2,32)
    unsigned long k;
    unsigned long i=15;
    unsigned long j=15;


int main(int argc, char** argv) {


    /*Abrimos archivos para impresion de resultados.*/
    if( (archivoResultados = fopen("estadisticas.dat","wb"))==NULL){
        puts("--- ERROR EN LA OPERACION DE ABRIR estadisticas---");
        return 1;
    }

    if( (archivoGraficar = fopen("graficar.dat","wb"))==NULL){
        puts("--- ERROR EN LA OPERACION DE ABRIR el de graficar---");
        return 1;
    }



        for(parametro=1; parametro <=100; parametro++){

            var =x0;
            /*Con un for, elegimos el dato que se va a reastrear.*/
            for(k=0; k<valorGrande; k++){
                 var = RENYI_MAP(var, parametro, j);
            }

            /*Se guarda el valor.*/
            valorABuscar =var;
            var = RENYI_MAP(var, parametro, j);


            /*Ahora, en un ciclo comparamos el valorABuscar obtenido el primer vez
            Y lo buscamos hasta encontrarlo otra vez, el contador se inicializa a uno porque
            ya se calculó un nuevo valor para var.*/
            contador=1;

            while((valorABuscar != var) && (var!=0) && contador <TAMANIOCICLO){
                contador++;
                var = RENYI_MAP(var, parametro, j);
               //printf("iter: %llu \t Se encontró: %lu  \t Se buscó: %lu \n",contador,var,valorABuscar);
            }


            /*Impresion de resultados: Si se encuentra el valor buscado, el valor buscado y el encontrado
            coinciden, si no coinciden se llega al tamanio del ciclo y se sale del while.*/
            printf("iter: %llu \t Se encontró: %lu  \t Se buscó: %lu  \t  \n",contador,var,valorABuscar);
            fprintf(archivoResultados,"iter: %llu \t Se encontró: %lu  \t Se buscó: %lu  \t   j:  %lu  Parametro usado: %lu \n",contador,var,valorABuscar,  j, parametro);
            fprintf(archivoGraficar,"%lu \t %llu \n",parametro, contador);

        }// ciclo parametros


    /*Verificamos que se hayan cerrado los archivos.*/
     if(!fclose(archivoResultados)){
      printf( "\nArchivo de de resultados  cerrado\n" );
       }
     else
     {
      printf( "\nError: Archivo  no cerrado \n" );
      return 1;
     }
      if(!fclose(archivoGraficar)){
      printf( "\nArchivo para graficar cerrado\n" );
       }
     else
     {
      printf( "\nError: Archivo  no cerrado \n" );
      return 1;
     }


    return 0;
}



