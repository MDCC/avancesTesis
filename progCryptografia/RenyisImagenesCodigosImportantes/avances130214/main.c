#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define RENYI_MAP(var, parametro, j) ((var)*(parametro)+((var)>>(j)))

#define  MAX 4294967295 /*El valor de 2^32-1.*/
#define TAMANIOCICLO 4294967296 /*EL valor de 2^32.*/
#define noMapas 4 /*NUmero de mapas a utilizar.*/
#define ITtotales 80000 /*Iteraciones totales para NIST.*/



/*
 File:   main.c
 Author: daniel
 El siguiente programa es un ejemplo de cuatro mapas caoticos RENYI acoplados.
 Para declarar nuestras variables, utilizamos los siguientes componentes:
 -Un arreglo que guarda el valor de los parametros para cada mapa.
 -Un arreglo que guarda el valor de los valores calculados para cada mapa.
*/


int main(){
 
   
   /*Declaramos los arreglos que vamos a utilizar para guardar esto.*/
   unsigned long Xn[noMapas];
   unsigned long Xtotal[ITtotales]; 
   unsigned long parametros[noMapas];
   unsigned int i;
   unsigned int epsilon;
   unsigned long gamma;
   unsigned long gammaComp;

   unsigned long H=0; 
   unsigned int j=9; /*No mas de 16.*/
   unsigned long iteraciones=0;
   unsigned long IT = 80000;

   /*Inicializamos nuestros parametros, en este punto se aplica el uso
    *de una llave, en este ejemplo todavia no elegimos una. Tambi��n,
    *los parametros son fijos en este ejemplo.*/
   parametros[0]=131071;
   Xn[0]=653;
   parametros[1]=104729;
   Xn[1]=769;
   parametros[2]=524287;
   Xn[2]=227;
   parametros[3]=65537;
   Xn[3]=823;
                   
   /*Primero, hacemos un ciclo inicial para calcular un nuevo valor para cada
   uno de los mapas y calcular, por primera vez, el resultado de la operacion
   XOR.*/
   for( i =0; i<noMapas; i++){
       Xn[i]= RENYI_MAP(Xn[i],parametros[i],j);
       H^=Xn[i];
   }
   
 
    /*Elegimos un epsilon aleatorio entre 1 y 16 (para operaciones de 32 bits).
      En este caso, elegimos uno que este entre 0 y 15.*/
   epsilon = 5;   
  
   gamma= pow(2,epsilon);
   gamma-=1;
   gammaComp= MAX-gamma;
    
   unsigned int k;
   unsigned long newH;

   do {
        
        newH = 0;
        for(k=0;k<noMapas; k++){            
            Xn[k]= gammaComp^RENYI_MAP(Xn[k],parametros[k],j)+ gamma^H;
            Xtotal[iteraciones++] = Xn[k];
            printf("%lu\n",Xtotal[iteraciones-1]);   
            newH^=Xn[k];      
        }
        H = newH;
        /*Ahora, elegimos un valor para epsilon entre 1 y 8 bits.*/
        epsilon = (H % 8) + 1; 
 

   } while (iteraciones < IT);
   
   
/*IMPRIMIR DATOS y procesar con NIST*/

return 0;
}
