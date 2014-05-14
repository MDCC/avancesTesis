#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

/*Este programa es una version final del programa de cifrado con el criterio de tomar
como referencia el bit de referencia anterior (lo que se vio en la platica en sala H).*/

/*Definiciones necesarias: MAPA RENYI.*/
#define RENYI_MAP(var, parametro, j) ((var)*(parametro)+((var)>>(j)))
#define MAPAS 3

/*Prototipos de funciones.*/
void imprimirArreglo1D(unsigned char *, unsigned int, unsigned int);
void imprimirArregloIndices(unsigned int *, unsigned int);
void imprimirArreglofeo(unsigned char * segmentos, unsigned int tam);

int main(){


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
	/*El tamanioArchivo es solo por las pruebas, 
        para ejemplos reales debo quitar que sea igual a 100.*/
	tamanioArchivo=100;
	rewind(archivobin);	
	unsigned char * datosArchivo = (unsigned char *)malloc(tamanioArchivo*sizeof(unsigned char));
	unsigned char * datosAuxiliar = datosArchivo;
	unsigned char * intercambioDatos = (unsigned char *)malloc(tamanioArchivo*sizeof(unsigned char));
	fread(datosArchivo,1,tamanioArchivo,archivobin);
	/***********************************************************************************/

	/***************** Ahora inicializamos los mapas caóticos Renyi. *******************/
	unsigned int numeroMapas =4;
	unsigned int Xn[numeroMapas]; 
	unsigned int clave[numeroMapas]; 
	unsigned int parametros[numeroMapas];
	unsigned int H=0; 
	unsigned int j=9; /*No mas de 16.*/
	unsigned int epsilon;

	/*Inicializacion de un arreglo de posiciones en los mapas caoticos.*/
	unsigned char mapas[256];
	unsigned int i;
        for(i=0; i<256; i++){
		mapas[i]= i&MAPAS;
	}

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
	unsigned int newH;

        /*Inicializacion de mapas caoticos.*/
	Xn[0]= RENYI_MAP(Xn[0],parametros[0],j);
	H^=Xn[0];
	Xn[1]= RENYI_MAP(Xn[1],parametros[1],j);
	H^=Xn[1];
	Xn[2]= RENYI_MAP(Xn[2],parametros[2],j);
	H^=Xn[2];
	Xn[3]= RENYI_MAP(Xn[3],parametros[3],j);
	H^=Xn[3];
     
	H&=255; 
	epsilon = 5;  
	newH = 0;
        /*Hacemos nuevas asignaciones usando H.*/
        Xn[0]= RENYI_MAP(Xn[0],parametros[0],j) + (epsilon^H);
        newH^=(Xn[0]);
        Xn[1]= RENYI_MAP(Xn[1],parametros[1],j) + (epsilon^H);
        newH^=(Xn[1]);
        Xn[2]= RENYI_MAP(Xn[2],parametros[2],j) + (epsilon^H);
        newH^=(Xn[2]);
        Xn[3]= RENYI_MAP(Xn[3],parametros[3],j) + (epsilon^H);
        newH^=(Xn[3]);

	H = newH;		
	H&=255; 
	/***********************************************************************************/


	/************ Declaracion de variables para cifrado parcial ************************/
	unsigned int tamRTP=50; 
	unsigned int numPaquetesRTP=tamanioArchivo/tamRTP; 
	unsigned int Lsegmentos = 10;  /*Segmentos a permutar, orita lo puse fijo.*/
	unsigned int segmentos[10];

        /*Ejemplo de Valores de prueba permitidos para calcular BF.*/
	unsigned int avCodigo=8;
        double  f=.25;
	unsigned int MEPL=4;
	unsigned int BF =f*avCodigo*MEPL; /*Con estos datos de prueba, BF=12.*/
       
        /*Arreglo auxiliar para invertir bit de acuerdo a su posicion.*/
	unsigned char flip[8];
        flip[0]=128;  flip[1]=64;  flip[2]=32;  flip[3]=16;
        flip[4]=8;    flip[5]=4;   flip[6]=2;   flip[7]=1;

	unsigned int tamanioSegmento = tamRTP/Lsegmentos;
	unsigned int numBitsRTP = tamRTP*8; /* Num. de bytes del segmento * numero de bits. */
	unsigned int T;  
	unsigned int irtp;
	unsigned int iTamSeg;
	unsigned int auxiliar;
	unsigned int iSeg;
	unsigned int posicion1;
	unsigned int posicion2;
	unsigned int bitRef;
	unsigned int posicionInversion;
	unsigned int refRTP;
	unsigned int p;
	unsigned char contadorMapa=0;
	/***********************************************************************************/

        /******************** Estructuras para medir el tiempo de calculo ******************/
	struct timeval tv1,tv2;
	float tsec,tusec;
	
	if (gettimeofday(&tv1,0) == -1) {
		printf("ERROR time1\n");
		exit(1);
        } 
        printf("Segundos = %ld, Microsegundos = %ld\n",tv1.tv_sec,tv1.tv_usec);
	/***********************************************************************************/	

	/*********** Proceso de cifrado para cada uno de los paquetes RTP ******************/
	for(irtp=0; irtp < numPaquetesRTP; irtp++ ){

                /*========= Proceso de Inversion de bits ==========================*/
               
                refRTP=tamRTP*irtp;
	        bitRef=0;	
	        epsilon = (H & 15);
	
                while((bitRef+BF)<numBitsRTP){
                                                           
                        /*Actualizacion de mapas caoticos.*/		
			
                        newH=0;
			Xn[0]= RENYI_MAP(Xn[0],parametros[0],j)+ (epsilon^H);
			newH^=Xn[0]; 
                        Xn[1]= RENYI_MAP(Xn[1],parametros[1],j)+ (epsilon^H);
			newH^=Xn[1]; 
			Xn[2]= RENYI_MAP(Xn[2],parametros[2],j)+ (epsilon^H);
			newH^=Xn[2]; 
			Xn[3]= RENYI_MAP(Xn[3],parametros[3],j)+ (epsilon^H);
			newH^=Xn[3]; 
			H = newH;		
			H&=255; 						
		 
		        p=(Xn[mapas[contadorMapa++]]%(BF-2))+1;

			                      

			bitRef+=p;

			/*Si un numero aleatorio es impar...*/
			if(Xn[mapas[contadorMapa++]]&1){  				
                                posicionInversion = bitRef+(Xn[mapas[contadorMapa++]]%(BF-p)); 
			}
			/*Si el un numero aleatorio es par...*/
			else{
                                posicionInversion = bitRef-(Xn[mapas[contadorMapa++]] % p);
			}

		
                        datosAuxiliar[posicionInversion/8]^=flip[posicionInversion & 7];  
                     
  
                }/*Fin del ciclo while para inversion de bits en el segmento.*/

         

		/*========= Proceso de Permutacion ========================================*/
		/*Primero, iniciamos el arreglo referencia.*/	
		for(iSeg=0; iSeg < Lsegmentos; iSeg++)
			segmentos[iSeg] = iSeg;
	       	
		for(iSeg =Lsegmentos; iSeg >1; iSeg--){
			
			T = Xn[mapas[contadorMapa++]]%(iSeg-1);
			/*Cambio de indices en el arreglo auxiliar.*/
		        auxiliar = segmentos[iSeg-1];
			segmentos[iSeg-1] = segmentos[T];
			segmentos[T] = auxiliar;
		   
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
         
        


       
         /*Ahora, datosAuxiliar se mueve al siguiente paquete RTP.*/
         datosAuxiliar+= tamRTP;
           
	}/*Fin del ciclo de paquetes RTP.*/
	/***********************************************************************************/


        /******************** Estructuras para medir el tiempo de calculo ******************/
        if (gettimeofday(&tv2,0) == -1) {
		printf("ERROR time2\n");
		exit(1);
	}
	printf("Segundos = %ld, Microsegundos = %ld\n",tv2.tv_sec,tv2.tv_usec);
	
	/*Tiempo transcurrido.*/
	if (tv1.tv_usec > tv2.tv_usec) {  
		tv2.tv_usec += 1000000;
		tv2.tv_sec--; 
	} 
        

	tsec = (tv2.tv_sec - tv1.tv_sec)*1000.;      /*Tiempo en milisegundos.*/
	tusec = (tv2.tv_usec - tv1.tv_usec)/1000.;
	
	printf("MIlisegundos de tv_sec= %f, MIlisegundos de tv_usec = %f, TIempo total = %f Milisegundos \n",tsec,tusec,tsec+tusec);
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



void imprimirArreglofeo(unsigned char * segmentos, unsigned int tam){
        unsigned int i;
        printf("\n");
	for( i =0; i<tam; i++){
		printf("%u  ",segmentos[i]);
	}
        printf("\n");	
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


