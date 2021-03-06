/* 
 * Este programa grafica los valores obtenidos de los mapas logisticos acoplados
 * en un una gráfica de tipo histograma, se espera que la distribución de los 
 * datos cumpla con una distribución uniforme.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Definimos una macro para generar datos con Renyi Map.
Como no se ocupan los 32 bits, no es necesaria la mascara.
 */ 




    FILE * archivoResultados;
    FILE * archivoGraficar;
    

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
    
        int i;
        long k;
        int estadisticos[100];
        for(i=0; i<100; i++){
            estadisticos[i]=0;
        }
         double var=1000;
         double b=8.32125;
         
       for(k=0; k<1000000; k++){
           
              var =b*var- floor(b*var);
              
              for(i =0; i<100; i=i+1){
                  
                  if (var>=(i/100.0)&&var<(i+1)/100.0){
                      
                      
                      estadisticos[i]+=1;
                  } 
              } 
    
          
        }// ciclo parametros 
         
         
         for(i =0; i<100; i++){
            fprintf(archivoGraficar,"%f \t %d \n",(i+1)/100.0, estadisticos[i]);
         }
    
         
       
        
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


