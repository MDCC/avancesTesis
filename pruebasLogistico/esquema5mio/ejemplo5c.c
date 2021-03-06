/*OPeracion XOR de manera aleatoria, pero ahora a mi modo.*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LogisticMap(par,var)  ((par)*(var)*(1.0 - (var)))
#define numMaps 8


int main() {

        /*Arreglo para guardar las frecuencias.*/
	int estadisticos[100];
	int frecEnteros[100];

	unsigned int posfrec;
	unsigned int iest;
        for(posfrec=0; posfrec<100; posfrec++){
            estadisticos[posfrec]=0;
            frecEnteros[posfrec]=0;
        }


	/*Apertura del fichero de destino, para escritura en binario.*/
	FILE * archivobin;
	archivobin = fopen ("bin.dat", "wb");
	if (archivobin==NULL){
		perror("No se puede abrir bin.dat");
		return 1;
	}
	/*Archivos para guardar los datos a graficar.*/       
	FILE * archivoGraficar;
        if( (archivoGraficar = fopen("graficar.dat","wb"))==NULL){
		perror("--- ERROR EN LA OPERACION DE ABRIR el de graficar---");
		return 1;
        } 
	/*Archivos para guardar los datos enteros.*/       
	FILE * archivoGraficarEnteros;
        if( (archivoGraficarEnteros = fopen("graficarEnt.dat","wb"))==NULL){
		perror("--- ERROR EN LA OPERACION DE ABRIR el de graficar Ent---");
		return 1;
        } 

	unsigned int TotalDatos = 300000;
	float X[TotalDatos];
	double maxFloatNumber = pow(2.,32)-1;
	unsigned int    i;
	unsigned int    Y[TotalDatos];
	unsigned int    Y2[TotalDatos];
	  //3.986       //3.9867   //3.9867363  //3.999725732;
	float Par = 3.999135731;
	float Xn =  0.0003751; 
	i = 0;

	while(i < TotalDatos) {  
		Xn = LogisticMap(Par,Xn);
		X[i]= Xn;
		/*===========Conteo de Frecuencias========================*/
		for(iest =0; iest<100; iest++){
			if (X[i]>=(iest/100.0)&&X[i]<(iest+1)/100.0){
				estadisticos[iest]+=1;
			} 
		} 
		/*========================================================*/
		Y[i] = X[i]*maxFloatNumber;
		i++;	
	} 


	

	/*============Guardamos los datos en el archivo indicado==================*/
	for(iest =0; iest<100; iest++){
		fprintf(archivoGraficar,"%f \t %d \n",(iest+1)/100.0, estadisticos[iest]);
	}
	/*========================================================================*/

	  

	for(i = 0; i < (TotalDatos-1); i++) {
		Y2[i]= Y[i];
		Y[i] ^= Y[i+1];
		//printf("\n   Y: %u",  Y[i]);
	}

        Y2[TotalDatos-1]=Y[TotalDatos-1];

	for(i = (TotalDatos-1); i >0 ; i--) {
		Y[i] ^= Y2[i-1];
		printf("\n   Y: %u",  Y[i]);
	}




	for(i = 0; i < TotalDatos; i++) {
		/*===================Conteo de Frecuencias========================*/
		for(iest =0; iest<100; iest++){
			if (Y[i]>=((iest/100.0)*maxFloatNumber) && Y[i]<((iest+1)/100.0*maxFloatNumber)){
				frecEnteros[iest]+=1;
			} 
		} 
		/*================================================================*/
	}



	/*============Guardamos los datos enteros en el archivo indicado==========*/
	for(iest =0; iest<100; iest++){
		fprintf(archivoGraficarEnteros,"%f \t %d \n",(iest+1)/100.0*maxFloatNumber, frecEnteros[iest]);
	}
	/*========================================================================*/


	/*==============Escribir datos en archivo==================================*/
	fwrite(Y,sizeof(unsigned int),TotalDatos,archivobin); 


	/*============================Cerramos los archivos========================*/
	if(!fclose(archivoGraficar)){
		printf( "\nArchivo para graficar cerrado\n" );
	}
	else{
		printf( "\nError: Archivo para graficar no cerrado \n" );
		return 1;
	} 
	if(!fclose(archivobin)){
		printf( "\nArchivo de datos en formato binario cerrado\n" );
	}
	else{
		printf( "\nError: Archivo de datos en formato binario no cerrado \n" );
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
