#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define RENYI_MAP(var, parametro, j) ((var)*(parametro)+((var)>>(j)))
#define ITtotales 80000 /*Iteraciones totales para NIST.*/


/*
 File:   main.c
 Author: daniel
En este programa, se ejecutan de manera simultánea dos mapas de tipo Renyi, estos no
son acoplados, las salidas de estos mapas se utilizan para una operacion XOR.
*/



unsigned long calcular_parametro(unsigned long q, unsigned int n, unsigned int i){    
    unsigned long potencia =1;
    unsigned int j;
    /*Calculo de la potencia (calculamos 2(a la)( n-i) ): */
    for(j =0; j<(n-i); j++){
        potencia*=2;
    }

    /*Ahora, lo que hacemos es la operacion q*2(a la )(n-i): */
    unsigned long parametro = q*(potencia);
    printf("  EL parametro es: %lu \n \n \n",parametro);
    return parametro;
}

int main(){
 
   
   /*Declaramos los arreglos que vamos a utilizar para guardar esto. EL tipo de dato será
   unsigned int, cuyo tamaño es de 34 bits (arquitectura de 64 bits).*/
   unsigned long Xtotal[ITtotales]; 
   FILE *  archivobin; 
   unsigned long Xn1 = 7;
   unsigned long Xn2 = 9;
   unsigned int n = 32;

   /*Valores de i, j y q para el mapa 1.*/
   unsigned int i1=7; 
   unsigned int j1=9; 
   unsigned long q1=13;
   /*Valores de i, j y q para el mapa 2.*/
   unsigned int i2=8; 
   unsigned int j2=13; 
   unsigned long q2=19;
 
   /*Calculo de los parametros para cada mapa: 1 y 2 respectivamente.*/
   unsigned long param1 =calcular_parametro(q1, n, i1);
   unsigned long param2 =calcular_parametro(q2, n, i2);
 
   unsigned int iteraciones=0;
   unsigned int IT = 80000;

  /* Apertura del fichero de destino, para escritura en binario.*/
   archivobin = fopen ("dosRenyisidifj1.dat", "wb");
   if (archivobin==NULL)
   {
   perror("No se puede abrir dosRenyisidifj1.dat");
   return -1;
   }
   
   printf("\n\n\n Operacion XOR en dos Renyis \n EL tamanio de unsigned long en maquina de 32 bits es:  %d", sizeof(long));



   while (iteraciones < IT) {

            Xn1= RENYI_MAP(Xn1,param1,j1);
            Xn2= RENYI_MAP(Xn2,param2,j2);
            Xtotal[iteraciones++] = Xn1^Xn2;
 
           //printf("\nla iteracion %u  para  %u H es:  \n",iteraciones-1, Xtotal[iteraciones-1] );

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
