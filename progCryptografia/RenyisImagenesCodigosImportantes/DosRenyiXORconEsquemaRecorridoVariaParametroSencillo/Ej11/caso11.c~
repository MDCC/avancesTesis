#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RENYI_MAP(var, parametro, j) ((var)*(parametro)+((var)>>(j)))
#define ITtotales 80000 /*Iteraciones totales para NIST.*/

/*
Operación XOR con intercambio entre dos mapas caótico.
En este caso, para los dos mapas: j = 8, comparten el mismo parametro b,
los valores iniciales difieren muy poco.
*/


int main(){
 
   
   unsigned long Xtotal[ITtotales]; 
   FILE *  archivobin; 
   unsigned long Xn1 = 7;
   unsigned long Xn2 = 9;

   /*Valor j y q para mapas.*/
   unsigned int j=8; 
 
 
   /*Parametros para cada mapa: 1 y 2 respectivamente.*/
   unsigned long param1 =5;
   unsigned long param2 =5;
 
   unsigned int iteraciones=0;
   unsigned int IT = 80000;

  /* Apertura del fichero de destino, para escritura en binario.*/
   archivobin = fopen ("caso11.dat", "wb");
   if (archivobin==NULL)
   {
   perror("No se puede abrir caso11.dat");
   return -1;
   }
   
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
            Xn1= RENYI_MAP(Xn1,param1,j);
            Xn2= RENYI_MAP(Xn2,param2,j);

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
             
            if((iteraciones-1)<5){
           printf("\nla iteracion %u  valor:  %lu \n",iteraciones-1,     Xtotal[iteraciones-1] );
           }

   } 
 

   /*Escribimos la informacion.*/
   fwrite(Xtotal,4,80000,archivobin); 

   if(!fclose(archivobin)){
      printf( "\nArchivo binario caso cerrado\n" );
   }
   else{
      printf( "\nError: Archivo binario  caso no cerrado \n" );
      return 1;
   }  

  

return 0;
}
