#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

/*Este programa es una version final del programa de cifrado con el criterio de tomar
como referencia el bit de referencia anterior (lo que se vio en la platica en sala H).
Version3
Esta version tiene las siguientes caracteristicas.
-El metodo de cifrado es el mio: operaciones separadas, no se optimiza el proceso de intercambio de datos.
-La generacion de mapas caoticos es aquella donde se utilizan TODOS los octetos.*/

/*Definiciones necesarias: MAPA RENYI.*/
#define RENYI_MAP(var, parametro, j) ((var)*(parametro)+((var)>>(j)))
#define MAPAS 3
#define NUMSEGMENTOS 20

/*Prototipos de funciones.*/
void imprimirArreglo1D(unsigned char *, unsigned int, unsigned int);
void imprimirArregloIndices(unsigned int *, unsigned int);
void imprimirArreglofeo(unsigned char * segmentos, unsigned int tam);

int main(){


	/******************* Lectura de archivos y asignacion de memoria. ******************/
	FILE * archivobin;
	FILE * archivoCifrado;
        unsigned int tamanioArchivo; 
	if ((archivobin = fopen ("test.mov", "rb")) ==NULL){
	perror("No se puede abrir binario.dat");
	return -1;
	}
	fseek(archivobin,0,SEEK_END);
	tamanioArchivo = ftell(archivobin);
	rewind(archivobin);	
	unsigned char * datosArchivo = (unsigned char *)malloc(tamanioArchivo*sizeof(unsigned char));
	unsigned char * datosAuxiliar = datosArchivo;
	unsigned char * intercambioDatos = (unsigned char *)malloc(tamanioArchivo*sizeof(unsigned char));
	fread(datosArchivo,1,tamanioArchivo,archivobin);
	/***********************************************************************************/

	/***************** Ahora inicializamos los mapas caóticos Renyi. *******************/
	unsigned int numeroMapas =4;
        unsigned int Xn[numeroMapas]; 
	unsigned char * prtXn = Xn;  
	unsigned int parametros[numeroMapas];
	unsigned int H=0; 
	unsigned int j=9; /*No mas de 16.*/
	unsigned int epsilon;

	unsigned int i;
        for(i=0; i<tamanioArchivo; i++){
		intercambioDatos[i] = datosArchivo[i];
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
	unsigned int newH=0;

        /*Inicializacion de mapas caoticos.*/
	Xn[0]= RENYI_MAP(Xn[0],parametros[0],j);
	newH^=Xn[0];
	Xn[1]= RENYI_MAP(Xn[1],parametros[1],j);
	newH^=Xn[1];
	Xn[2]= RENYI_MAP(Xn[2],parametros[2],j);
	newH^=Xn[2];
	Xn[3]= RENYI_MAP(Xn[3],parametros[3],j);
	newH^=Xn[3];
	H=newH&255; 
	epsilon = 5;  
	
        /*Hacemos nuevas asignaciones usando H.*/
        Xn[0]= RENYI_MAP(Xn[0],parametros[0],j) + (epsilon^H);
        newH^=(Xn[0]);
        Xn[1]= RENYI_MAP(Xn[1],parametros[1],j) + (epsilon^H);
        newH^=(Xn[1]);
        Xn[2]= RENYI_MAP(Xn[2],parametros[2],j) + (epsilon^H);
        newH^=(Xn[2]);
        Xn[3]= RENYI_MAP(Xn[3],parametros[3],j) + (epsilon^H);
        newH^=(Xn[3]);
	H = newH&255;		
	/***********************************************************************************/


	/************ Declaracion de variables para cifrado parcial ************************/
	unsigned int tamRTP=400; 
	unsigned int numPaquetesRTP=tamanioArchivo/tamRTP; 
	//unsigned int Lsegmentos = 20;  /*Segmentos a permutar, orita lo puse fijo.*/
	unsigned int segmentos[20];

        /*Ejemplo de Valores de prueba permitidos para calcular BF.*/
	unsigned int avCodigo=8;
        double  f=.25;
	unsigned int MEPL=4;
	unsigned int BF =f*avCodigo*MEPL; /*Con estos datos de prueba, BF=12.*/
       
        /*Arreglo auxiliar para invertir bit de acuerdo a su posicion.*/
	unsigned char flip[8];
        flip[0]=128;  flip[1]=64;  flip[2]=32;  flip[3]=16;
        flip[4]=8;    flip[5]=4;   flip[6]=2;   flip[7]=1;

	unsigned int tamanioSegmento = tamRTP/NUMSEGMENTOS;
	unsigned int numBitsRTP = tamRTP*8; /*Num. de bytes del segmento * numero de bits.*/
	unsigned int T;  
	register unsigned int irtp;
	register unsigned int iTamSeg;
	unsigned int auxiliar;
	register unsigned int iSeg;
	register unsigned int posicion1;
	register unsigned int posicion2;
	unsigned int bitRef;
	unsigned int posicionInversion;
	unsigned int refRTP;
	unsigned int p;
	unsigned int count=0;
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
	for(irtp=0; irtp < numPaquetesRTP; irtp++){

                /*========= Proceso de Inversion de bits ==========================*/
                refRTP=tamRTP*irtp;
	        bitRef=0;	
	        epsilon = (H & 15);
	
                while((bitRef+BF)<numBitsRTP){
                        
                        if(count > 15){
                        	count=0;
				newH=0;
				Xn[0]= RENYI_MAP(Xn[0],parametros[0],j)+ (epsilon*H);
				newH^=Xn[0]; 
                        	Xn[1]= RENYI_MAP(Xn[1],parametros[1],j)+ (epsilon*H);
				newH^=Xn[1]; 
				Xn[2]= RENYI_MAP(Xn[2],parametros[2],j)+ (epsilon*H);
				newH^=Xn[2]; 
				Xn[3]= RENYI_MAP(Xn[3],parametros[3],j)+ (epsilon*H);
				newH^=Xn[3]; 
				H = newH&255;		
                        }
                                                           
                      
						
	                p=( *(prtXn+count)  % (BF-2)  ) + 1;
			count++;  
			bitRef+=p;


			/*Si un numero aleatorio es impar...*/
			if(p&1){  
                           posicionInversion = bitRef+( *(prtXn+count)  % (BF-p)); 
			}
			/*Si el un numero aleatorio es par...*/
			else{
                           posicionInversion = bitRef-( *(prtXn+count)  % p);
			}
                        
                 
                        datosAuxiliar[posicionInversion>>3]^=flip[posicionInversion & 7];  
                        count++;                      
                }/*Fin del ciclo while para inversion de bits en el segmento.*/

		
                      
		/*========= Proceso de Permutacion ========================================*/
		/*Primero, iniciamos el arreglo referencia.*/	
                segmentos[0]=0;   segmentos[1]=1;   segmentos[2]=2;   segmentos[3]=3; 
                segmentos[4]=4;   segmentos[5]=5;   segmentos[6]=6;   segmentos[7]=7; 
                segmentos[8]=8;   segmentos[9]=9;   segmentos[10]=10; segmentos[11]=11; 
                segmentos[12]=12; segmentos[13]=13; segmentos[14]=14; segmentos[15]=15; 
                segmentos[16]=16; segmentos[17]=17; segmentos[18]=18; segmentos[19]=19; 
	       	
		for(iSeg =NUMSEGMENTOS; iSeg >1; iSeg--){
        
                          if(count > 15){
                        	count=0;
				newH=0;
				Xn[0]= RENYI_MAP(Xn[0],parametros[0],j)+ (epsilon*H);
				newH^=Xn[0]; 
                        	Xn[1]= RENYI_MAP(Xn[1],parametros[1],j)+ (epsilon*H);
				newH^=Xn[1]; 
				Xn[2]= RENYI_MAP(Xn[2],parametros[2],j)+ (epsilon*H);
				newH^=Xn[2]; 
				Xn[3]= RENYI_MAP(Xn[3],parametros[3],j)+ (epsilon*H);
				newH^=Xn[3]; 
				H = newH&255;		
                        }
                            

			T = *(prtXn+count)  % (iSeg-1);
			count++;
                   
			/*Cambio de indices en el arreglo auxiliar.*/
		        auxiliar = segmentos[iSeg-1];
			segmentos[iSeg-1] = segmentos[T];
			segmentos[T] = auxiliar;
                        
		}/*Fin del for que recorre los segmentos del paquete RTP.*/
                
       
                /*Ahora, reordenamos el paquete RTP de acuerdo al arreglo de indices.*/ 
		for(iSeg=0; iSeg<NUMSEGMENTOS; iSeg++){
		   
		        posicion1=tamanioSegmento*segmentos[iSeg];
		       	posicion2=tamanioSegmento*iSeg + refRTP;
			for(iTamSeg=0; iTamSeg<tamanioSegmento; iTamSeg++){
		                /*Hacemos el intercambio.*/ 
		                intercambioDatos[posicion2 + iTamSeg]=datosAuxiliar[posicion1+iTamSeg];
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


