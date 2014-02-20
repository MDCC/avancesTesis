#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define RENYI_MAP(var, parametro, j) ((var)*(parametro)+((var)>>(j)))
#define  MAX 4294967295 /*El valor de 2^32-1.*/
#define TAMANIOCICLO 4294967296 /*EL valor de 2^32.*/
#define ITtotales 80000 /*Iteraciones totales para NIST.*/


/*
 File:   main.c
 Author: daniel
En este programa, se ejecutan de manera simultánea dos mapas de tipo Renyi, estos no
son acoplados, las salidas de estos mapas se utilizan para una operacion XOR.
*/


int main(){
 
   
   /*Declaramos los arreglos que vamos a utilizar para guardar esto. EL tipo de dato será
   unsigned int, cuyo tamaño es de 34 bits (arquitectura de 64 bits).*/
   unsigned int Xtotal[ITtotales]; 
   unsigned int Xn1 = 653;
   unsigned int Xn2 = 769;
   unsigned int param1 = 131071;
   unsigned int param2 = 104729;
   FILE *  archivobin; 

   unsigned int j=9; /*No mas de 16.*/
   unsigned int iteraciones=0;
   unsigned int IT = 80000;

  /* Apertura del fichero de destino, para escritura en binario.*/
   archivobin = fopen ("dosRenyis.dat", "wb");
   if (archivobin==NULL)
   {
   perror("No se puede abrir binarioXORcomp.dat");
   return -1;
   }
   

   while (iteraciones < IT) {

            Xn1= RENYI_MAP(Xn1,param1,j);
            Xn2= RENYI_MAP(Xn2,param2,j);
            Xtotal[iteraciones++] = Xn1^Xn2;
 
           printf("\nla iteracion %u  para  %u H es:  \n",iteraciones-1, Xtotal[iteraciones-1] );

   } 
 

   /*Escribimos la informacion.*/
   fwrite(Xtotal,4,80000,archivobin); 


   if(!fclose(archivobin)){
      printf( "\nArchivo binario cerrado\n" );
   }
   else{
      printf( "\nError: Archivo binario no cerrado \n" );
      return 1;
   }  

  

return 0;
}
