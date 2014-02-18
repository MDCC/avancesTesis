/* 
 * File:   main.c
 * Author: daniel
 Renyi Map de 24 bits.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



/*Definimos una macro para generar datos con Renyi Map.
Como no se ocupan los 32 bits, no es necesaria la mascara.
 */ 
#define RENYI_MAP_24BITS(var, parametro, j, mask) ((var)*(parametro)+((var)>>(j)))&(mask)


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
    unsigned long x0=0x00000007;
    unsigned long valorABuscar;
    unsigned long  contador=0;
    unsigned long  TAMANIOCICLO = 16777216;   // pow(2,32)
    unsigned long k;
    //////////////////
    unsigned long j=22;
    unsigned long n=24;
    unsigned long i=22;
    unsigned long q=0;
    unsigned long mask= 0x0059A564;
    //////////////////    

/*Lamamos el Renyi Map por medio de
 una macro desde main.*/
int main(int argc, char** argv) {
    
    if( (archivoResultados = fopen("estadisticas.dat","wb"))==NULL){
        puts("--- ERROR EN LA OPERACION DE ABRIR estadisticas---");
        return 1;
    } 
    
    if( (archivoGraficar = fopen("graficar.dat","wb"))==NULL){
        puts("--- ERROR EN LA OPERACION DE ABRIR el de graficar---");
        return 1;
    } 
    

    

   
       
    
        //vamos a variar el q.    
        for(q=1; q <=9; q=q+2){
            
            var =x0;
            /*Antes de hacer los calculos, calculamos el parametro*/
            parametro = calcular_parametro(q, n, i);
            
            /*Con un for, elegimos el dato que se va a reastrear.*/
            for(k=0; k<valorGrande; k++){
                 var = RENYI_MAP_24BITS(var, parametro, j, mask);
            }

            /*Se guarda el valor.*/
            valorABuscar =var;
            var = RENYI_MAP_24BITS(var, parametro, j, mask);    
      

            /*Ahora, en un ciclo comparamos el valorABuscar obtenido el primer vez
            Y lo buscamos hasta encontrarlo otra vez.*/
            contador=1;

            while((valorABuscar != var) && (var!=0) && contador <TAMANIOCICLO){
                contador++;
                var =  RENYI_MAP_24BITS(var, parametro, j, mask); 
               //printf("iter: %llu \t Se encontró: %lu  \t Se buscó: %lu \n",contador,var,valorABuscar);  
            }
            
            
            /*Impresion de resultados.*/
            printf("iter: %lu \t Se encontró: %lu  \t Se buscó: %lu  \t  \n",contador,var,valorABuscar);
            fprintf(archivoResultados,
                   "iter: %lu \t Se encontró: %lu  \t Se buscó: %lu  \t   i=j:  %lu   n: %lu   q: %lu    Parametro: %lu \n",contador,var,valorABuscar,  j, n, q, parametro);
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


