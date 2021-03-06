#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define RENYI_MAP(var, parametro, j) ((var)*(parametro)+((var)>>(j)))

#define  MAX 4294967295 /*El valor de 2^32-1.*/
#define TAMANIOCICLO 4294967296 /*EL valor de 2^32.*/
#define noMapas 4 /*NUmero de mapas a utilizar.*/
#define ITtotales 80000 /*Iteraciones totales para NIST.*/
#define tamanioH 20000 /*Tamanio del arreglo de H.*/


/*
 File:   main.c
 Author: daniel
 El siguiente programa es un ejemplo de cuatro mapas caoticos RENYI acoplados.
 Se utiliza la suma para lograr el acoplado.
 Para declarar nuestras variables, utilizamos los siguientes componentes:
 -Un arreglo que guarda el valor de los parametros para cada mapa.
 -Un arreglo que guarda el valor de los valores calculados para cada mapa.
*/


int main(){
 
   
   /*Declaramos los arreglos que vamos a utilizar para guardar esto.*/
   unsigned int Xn[noMapas];
   unsigned int Xtotal[ITtotales]; 
   unsigned int parametros[noMapas];
   unsigned int i;
   unsigned int iest;
   unsigned int arregloH[tamanioH];
   int epsilon;
   FILE *  archivobin; 
   FILE *  archivoH;
	double maxFloatNumber = pow(2.,32)-1;
   
   unsigned int H=0; 
   unsigned int j=9; /*No mas de 16.*/
   unsigned int iteraciones=0;
   unsigned int IT = 80000;
   int frecEnteros[100];


  /* Apertura del fichero de destino, para escritura en binario.*/
   archivobin = fopen ("binarioSUMAmod.dat", "wb");
   if (archivobin==NULL)
   {
   perror("No se puede abrir binarioSUMAmod.dat");
   return -1;
   }
   
   /* Apertura del archivo H para su escritura en binario.*/
   archivoH = fopen ("HdeSuma.dat", "wb");
   if (archivoH==NULL)
   {
   perror("No se puede abrir HdeSuma.dat");
   return -1;
   }
   

	/*Archivos para guardar los datos enteros.*/       
	FILE * archivoGraficarEnteros;
        if( (archivoGraficarEnteros = fopen("graficarEnt.dat","wb"))==NULL){
		perror("--- ERROR EN LA OPERACION DE ABRIR el de graficar Ent---");
		return 1;
        } 


   
   /*Inicializamos nuestros parametros, en este punto se aplica el uso
   de una llave, en este ejemplo todavia no elegimos una. Tambi��n,
   los parametros son fijos en este ejemplo.*/
   parametros[0]=131071;
   Xn[0]=653;
   parametros[1]=104729;
   Xn[1]=769;
   parametros[2]=524287;
   Xn[2]=227;
   parametros[3]=65537;
   Xn[3]=823;        
   int contDeH=0;
   
   /*Primero, hacemos un ciclo inicial para calcular un nuevo valor para cada
   uno de los mapas y calcular, por primera vez, el resultado de la operacion
   XOR.*/
   for( i =0; i<noMapas; i++){
       Xn[i]= RENYI_MAP(Xn[i],parametros[i],j);
       H+=Xn[i];
   }
    
   arregloH[contDeH]=H; 
   contDeH++;
   
   /*Tambien al primer H se le aplica el mod.*/
   H%=256; 
   
   /*Elegimos un epsilon aleatorio entre 1 y 16 (para operaciones de 32 bits).
   En este caso, elegimos uno que este entre 0 y 15.*/
   epsilon = 1;   
    
   unsigned int k;
   unsigned long newH;
   
   do {
        
        newH = 0;
        for(k=0;k<noMapas; k++){            
            Xn[k]= RENYI_MAP(Xn[k],parametros[k],j) + epsilon*H;
            Xtotal[iteraciones] = Xn[k];
		/*===========Conteo de Frecuencias========================*/
		for(iest =0; iest<100; iest++){
			if (Xtotal[iteraciones]>=((iest/100.0)*maxFloatNumber) && Xtotal[iteraciones]<((iest+1)/100.0*maxFloatNumber)){
				frecEnteros[iest]+=1;
			} 
		} 
		/*========================================================*/ 
	    iteraciones++;     
            newH+=(Xn[k]);      
        }
        H = newH;
        arregloH[contDeH]=H;
        printf("\nla iteracion %d  para  %u H es:  \n", contDeH,arregloH[contDeH] );
        contDeH++;
        /*BUscamos un H pequeño: la perturbación no debe ser 
        tan fuerte. Por tal motivo, se aplica una operación módulo.*/
        H%=256;
        
        /*Ahora, elegimos un valor para epsilon.*/
        epsilon = (H & 1)?1:-1;

   } while (iteraciones < IT);


	/*============Guardamos los datos enteros en el archivo indicado==========*/
	for(iest =0; iest<100; iest++){
		fprintf(archivoGraficarEnteros,"%f \t %d \n",(iest+1)/100.0*maxFloatNumber, frecEnteros[iest]);
	}
	/*========================================================================*/
  
   /*Escribimos la informacion.*/
   fwrite(Xtotal,4,80000,archivobin); 
   fwrite(arregloH,4,20000,archivoH); 

   if(!fclose(archivobin)){
      printf( "\nArchivo binario de Mapas cerrado\n" );
   }
   else{
      printf( "\nError: Archivo binario de Mapas no cerrado \n" );
      return 1;
   }
   
   if(!fclose(archivoH)){
      printf( "\nArchivo binario DE H cerrado\n" );
   }
   else{
      printf( "\nError: Archivo binario DE H no cerrado \n" );
      return 1;
   }

	if(!fclose(archivoGraficarEnteros)){
		printf( "\nArchivo de datos enteros cerrado\n" );
	}
	else{
		printf( "\nError: Archivo de datos enteros no cerrado \n" );
		return 1;
	} 

   
return 0;
}
