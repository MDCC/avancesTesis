#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>
/*Este programa es una version final del programa de cifrado con el criterio de tomar
como referencia el ultimo bit de referencia, lo que se dijo en la sala H. Este es muy cercano a la
version de VERONICA*/

/*Definiciones necesarias: MAPA RENYI.*/
#define RENYI_MAP(var, parametro, j) ((var)*(parametro)+((var)>>(j)))


/*Prototipos de funciones.*/
void imprimirArreglo1D(unsigned char *, unsigned int, unsigned int);
void imprimirArregloIndices(unsigned int *, unsigned int);

int main(){

	srand (time(NULL));

	/******************* Lectura de archivos y asignacion de memoria. ******************/
	FILE * archivobin;
	FILE * archivoCifrado;
        unsigned int tamanioArchivo; 
	if ((archivobin = fopen ("lena.jpg", "rb")) ==NULL){
	perror("No se puede abrir binario.dat");
	return -1;
	}
	fseek(archivobin,0,SEEK_END);
	tamanioArchivo = ftell(archivobin);
	/*El tamanioArchivo es solo por las pruebas, para ejemplos reales debo quitar que sea igual a 100.*/
	tamanioArchivo=100;
	rewind(archivobin);	
	unsigned char * datosArchivo = (unsigned char *)malloc(tamanioArchivo*sizeof(unsigned char));
	unsigned char * intercambioDatos = (unsigned char *)malloc(tamanioArchivo*sizeof(unsigned char));
	fread(datosArchivo,1,tamanioArchivo,archivobin);
	unsigned char * pAuxDatos = datosArchivo;
	/***********************************************************************************/

	/***************** Ahora inicializamos los mapas caóticos Renyi. *******************/
	unsigned int numeroMapas =4;
	unsigned int Xn[numeroMapas]; 
	unsigned int clave[numeroMapas]; 
	unsigned int parametros[numeroMapas];
	unsigned int H=0; 
	unsigned int j=9; /*No mas de 16.*/
	unsigned int epsilon;
	unsigned int gamma;
        unsigned int gammaComp;

	/*Inicializamos nuestros parametros.*/
	parametros[0]=131071;
	Xn[0]=653;
	parametros[1]=104729;
	Xn[1]=769;
	parametros[2]=524287;
	Xn[2]=227;
	parametros[3]=65537;
	Xn[3]=823;

	/*Primer ciclo en mapas caoticos para calcular H.*/
	unsigned int i;
	unsigned int k;
	unsigned int newH;
	for( i =0; i<numeroMapas; i++){
		Xn[i]= RENYI_MAP(Xn[i],parametros[i],j);
		H^=Xn[i];
	}
	H%=256; 
	epsilon = 5;  
        gamma= pow(2,epsilon)-1;
        gammaComp= (4294967295-gamma);
	newH = 0;
	for(k=0;k<numeroMapas; k++){            
		Xn[k]= (gammaComp^RENYI_MAP(Xn[k],parametros[k],j))+ (gamma^H); 
		newH^=Xn[k];      
	}
	H = newH;		
	H%=256; 
	/***********************************************************************************/


	/************ Declaracion de variables para cifrado parcial ************************/
	unsigned int tamRTP=50; 
	unsigned int numPaquetesRTP=tamanioArchivo/tamRTP; 
	unsigned int Lsegmentos = 10;  /*Segmentos a permutar, orita lo puse fijo.*/
	unsigned int segmentos[10];
	unsigned int avCodigo=8;
	unsigned int tamanioSegmento = tamRTP/Lsegmentos;
	unsigned int numBitsSegmento = tamanioSegmento*8; /*Numero de bytes del segmento por el numero de bits.*/
	unsigned int T; /*Esta T se usa para elegir el segmento de manera aleatoria.*/ 
	unsigned int irtp;
	unsigned int iTamSeg;
	unsigned int auxiliar;
	unsigned int iSeg;
	unsigned int posicion1;
	unsigned int posicion2;
	unsigned int bitRef;
	unsigned int aleatorio;
	unsigned int posicionInversion;
	unsigned int refRTP;
	unsigned int pos_byte;
	unsigned int p;
	unsigned int contadorMapa;
        int cambio;
	/***********************************************************************************/

        /******************** Estructuras para medir el tiempo de calculo ******************/
	struct timeval tv1,tv2;
	float tsec,tusec;
	
	if (gettimeofday(&tv1,0) == -1) {
		printf("ERROR time1\n");
		exit(1);
        } 
        printf("secs = %ld, usec = %ld\n",tv1.tv_sec,tv1.tv_usec);
	/***********************************************************************************/	

	/*********** Proceso de cifrado para cada uno de los paquetes RTP ******************/
	for(irtp=0; irtp < numPaquetesRTP; irtp++ ){

		/*========= Proceso de Permutacion ========================================*/
		/*Primero, iniciamos el arreglo referencia.*/	
		for(iSeg=0; iSeg < Lsegmentos; iSeg++)
			segmentos[iSeg] = iSeg;
	       	
		for(iSeg =Lsegmentos; iSeg >1; iSeg--){
			T = Xn[0]%(iSeg-1);
	
			/*Cambio de indices en el arreglo auxiliar.*/
		        auxiliar = segmentos[iSeg-1];
			segmentos[iSeg-1] = segmentos[T];
			segmentos[T] = auxiliar;
		         
		        /*Nos posicionamos en el segmento que queda en el final.*/
			pos_byte = segmentos[iSeg-1]*tamanioSegmento;

			/*========= Proceso de Inversion de bits ==========================*/
			refRTP=tamRTP*irtp;
			bitRef=0;	
		        contadorMapa=0;
			while((bitRef+avCodigo) <numBitsSegmento){
                                if(contadorMapa >(numeroMapas-1)){
					contadorMapa = 0;
					epsilon = (H % 8) + 1;
					gamma= pow(2,epsilon)-1;
                                        gammaComp= (4294967295-gamma);	
                                        for(k=0;k<numeroMapas; k++){  
						Xn[k]= (gammaComp^RENYI_MAP(Xn[k],parametros[k],j))+ (gamma^H);  
				                newH^=Xn[k];      
					}
					H = newH;		
					H%=256; 						
				}
 		        
				/*Obtenemos valor aleatorio.*/
				aleatorio=Xn[contadorMapa++];
		                p=(aleatorio %(avCodigo-2))+1;
				printf("\n el valor de p antiguo: %u",p);
				bitRef+=p;
		               
			        /*Si el numero aleatorio es impar...*/
				if(aleatorio&1){  	
					posicionInversion=(aleatorio%(avCodigo-p));
					bitRef+=posicionInversion;
					cambio = -posicionInversion;
				}
				/*Si el numero aleatorio es par...*/
				else{
					posicionInversion=(aleatorio % p);
					bitRef-=posicionInversion;
					cambio = posicionInversion;
				}

				datosArchivo[refRTP + pos_byte + (bitRef/8)]^=(1<<(avCodigo-(bitRef&7)-1));
                                /*Una vez que se ha hecho la inversion,
                                ahora es necesario recordar la posicion de referencia original.*/
                                bitRef+=cambio;
	
			}/*Fin del While para inversiones de bits.*/
		        /*======Fin del proceso de inversion===============================*/

		}/*Fin del for que recorre los segmentos del paquete RTP.*/
                
	
                /*Ahora, reordenamos el paquete RTP de acuerdo al arreglo de indices.*/ 
		for(iSeg=0; iSeg<Lsegmentos; iSeg++){
		        
		        posicion1=tamanioSegmento*segmentos[iSeg] + irtp*tamRTP;
		       	posicion2=tamanioSegmento*iSeg + irtp*tamRTP;

			for(iTamSeg=0; iTamSeg<tamanioSegmento; iTamSeg++){
		                /*Hacemos el intercambio.*/ 
		                intercambioDatos[posicion2 + iTamSeg]=datosArchivo[posicion1+iTamSeg];
			}
		}/*Fin del for para la permutacion de segmentos*/
     
	}/*Fin del ciclo de paquetes RTP.*/
	/***********************************************************************************/


        /******************** Estructuras para medir el tiempo de calculo ******************/
        if (gettimeofday(&tv2,0) == -1) {
		printf("ERROR time2\n");
		exit(1);
	}
	printf("secs = %ld, usec = %ld\n",tv2.tv_sec,tv2.tv_usec);
	
	//elapsed time
	if (tv1.tv_usec > tv2.tv_usec) {  
		tv2.tv_usec += 1000000;
		tv2.tv_sec--; 
	} 
	tsec = (tv2.tv_sec - tv1.tv_sec)*1000.;      /*Tiempo en milisegundos.*/
	tusec = (tv2.tv_usec - tv1.tv_usec)/1000.;
	
	printf("tsec = %f, tusec = %f, elapsed time = %f milliseconds\n",tsec,tusec,tsec+tusec);
	printf("Megabits/sec = %f \n",((numPaquetesRTP*tamRTP*8)/(1000.0*1000.0))/((tsec + tusec)/1000.));
	/***********************************************************************************/

	/*****************************Escritura de resultados*******************************/
        archivoCifrado =  fopen("cifrado.mov", "wb");
	fwrite(intercambioDatos, 1,tamanioArchivo,archivoCifrado);
	fclose(archivobin);
	fclose(archivoCifrado);
        free(datosArchivo);
	free(intercambioDatos);
        /***********************************************************************************/


	return 0;

}



void imprimirArregloIndices(unsigned int * segmentos, unsigned int tam){
        unsigned int i;
        printf("\n");
	for( i =0; i<tam; i++){
		printf("%u  ",segmentos[i]);
	}
        printf("\n");	
}


void  imprimirArreglo1D( unsigned char *A, unsigned int tamanio, unsigned int tamanioSegmento){

        printf("\n");
        unsigned int i;
        unsigned int tamanioS=0;
	for( i =0; i<tamanio; i++){
		printf("%u  ", A[i]);
                tamanioS++;
                if(tamanioS==tamanioSegmento){
                   printf("    ");
                   tamanioS=0; 
		}
	}
        printf("\n");	

}



