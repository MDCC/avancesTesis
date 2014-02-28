#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RENYI_MAP(var, parametro, j) ((var)*(parametro)+((var)>>(j)))
#define ITtotales 5 /*Iteraciones totales para NIST.*/

/*
 File:   main.c
 Author: daniel
En este programa, hacemoxs un esquema cruzado para la generacion de numeros
aleatorios.
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
 
   
  /*En este primer ejemplo, se hace la prueba para i = j en cada uno de 
   los dos mapas.*/
   unsigned long Xtotal[ITtotales]; 

   unsigned long Xn1 = 13;
   unsigned long Xn2 = 19;
   unsigned int n = 32;

   /*Valores de i, j y q para el mapa 1.*/
   unsigned int i1=9; 
   unsigned int j1=9; 
   unsigned long q1=13;
   /*Valores de i, j y q para el mapa 2.*/
   unsigned int i2=13; 
   unsigned int j2=13; 
   unsigned long q2=19;
 
   /*Calculo de los parametros para cada mapa: 1 y 2 respectivamente.*/
   unsigned long param1 =calcular_parametro(q1, n, i1);
   unsigned long param2 =calcular_parametro(q2, n, i2);
 
   unsigned int iteraciones=0;
   unsigned int IT = 5;



      printf("\n\n\n ======== Pruebas NIST XOR con intercaMBIO I =J =========\n\n\n");

   printf("\n\n\n Operacion XOR en dos Renyis \n EL tamanio de unsigned long en maquina de 32 bits es:  %d", sizeof(long));


  /*Sea a el valor de 2^16 -1 (el maximo valor en 16 bits de 32.)*/
   unsigned long a = 65535;
   /*Declaramos valores temporales.*/
   unsigned long temp;
   unsigned long temp1;
   unsigned long temp2;
   unsigned long Xn3;

   while (iteraciones < IT) {

           /*Primero, creamos los valores por medio del mapa renyi.*/
            Xn1= RENYI_MAP(Xn1,param1,j1);
            Xn2= RENYI_MAP(Xn2,param2,j2);

            /*obtenemos la parte derecha del valor de Xn2.*/
            temp1 = Xn2 & a;
            /*Obtenemos la parte izquierda del valor de Xn1.*/
            temp2 = Xn1 >> 16;
            /*Hacemos la combinacion.*/
            temp = temp1^temp2;

            /*Obtenemos la parte izquierda del valor de x2.*/
            temp1 = Xn2 >> 16;
            /*Obtenemos la parte derecha del valor de x1.*/
            temp2 = Xn1 & a;
            
            /*Ahora, formamos el nuevo valor para x3.*/
            Xn3=(temp1^temp2)<<16;
            Xn3|=temp;


            Xtotal[iteraciones++] = Xn3;
 
     
           printf("\n valor 1: %lu       valor 2: %lu       valor 3: %lu   nana %lu  \n", Xn1, Xn2, Xn3, Xtotal[iteraciones-1]   );


   } 
 

  

return 0;
}
