/*Este programa utiliza la operacion XOR secuencial. Los datos generados 
se guardan en archivos para poder
graficarse en el lenguaje R.*/
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



	unsigned int N = 10000;
	unsigned int TotalDatos = N*numMaps, TotalDatos2 = TotalDatos/2;
	float X[TotalDatos], Par[numMaps], Var[numMaps],  eps = 0.001,  EPS =1-eps,  H, tempH;
	double maxFloatNumber = pow(2.,32)-1;
	unsigned int    i, k;
	unsigned int    Y[TotalDatos];
	  

	Par[0] = 3.9999; Par[1] = 3.9999; Par[2] = 3.9999;  Par[3] = 3.9999;
	Var[0] =  0.34561; Var[1] =  0.98687; Var[2] =  0.54735; Var[3] =  0.04576;
	Par[4] = 3.9999; Par[5] = 3.9999; Par[6] = 3.9999;  Par[7] = 3.9999;
	Var[4] =  0.94584; Var[5] =  0.78594; Var[6] =  0.62384; Var[7] =  0.86560;

	for(H = 0, i=0;i < numMaps;i++) {   
		X[i] = LogisticMap(Par[i],Var[i]);
		/*===========Conteo de Frecuencias========================*/
		for(iest =0; iest<100; iest++){
			if (X[i]>=(iest/100.0)&&X[i]<(iest+1)/100.0){
				estadisticos[iest]+=1;
			} 
		} 
		/*========================================================*/
		H+= X[i];
	}
	H/= numMaps;


	i = numMaps;
	while(i < TotalDatos) {  
		for(tempH = 0, k=0;k < numMaps;k++) {
			X[i] = EPS*LogisticMap(Par[k],X[i-numMaps]) + eps*H;
			/*===========Conteo de Frecuencias========================*/
			for(iest =0; iest<100; iest++){
				if (X[i]>=(iest/100.0)&&X[i]<(iest+1)/100.0){
					estadisticos[iest]+=1;
				} 
			} 
			/*========================================================*/
			tempH += X[i];
			i++;
		} 
		H = tempH/numMaps;
	} 


	/*============Guardamos los datos en el archivo indicado==================*/
	for(iest =0; iest<100; iest++){
		fprintf(archivoGraficar,"%f \t %d \n",(iest+1)/100.0, estadisticos[iest]);
	}
	/*========================================================================*/

	  
	for(i = 0; i < TotalDatos; i++) {
		Y[i] = X[i]*maxFloatNumber;
	}
	
	for(i = 0; i < TotalDatos; i+=2) {
		Y[i] ^= Y[i+1];
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
	fwrite(Y,sizeof(unsigned int),TotalDatos2,archivobin);
	printf("\nEL numero de datos es: %u",TotalDatos2); 


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
