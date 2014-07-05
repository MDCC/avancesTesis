#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*Programa para descifrar.
Ahora vamos a hacer el programa de descifrado.*/

/*Definiciones necesarias: MAPA RENYI.*/
#define RENYI_MAP(var, parametro, j) ((var)*(parametro)+((var)>>(j)))
#define MAPAS 3
#define NUMSEGMENTOS 10
             
	    


/*Prototipos de funciones.*/
void imprimirArreglo1D(unsigned char *, unsigned int, unsigned int);
void imprimirArregloIndices(unsigned char *, unsigned int);
void imprimirArreglofeo(unsigned char * segmentos, unsigned int tam);

int main(){


	/******************* Lectura de archivos y asignacion de memoria. ******************/
	FILE * archivobin;
	FILE * archivoCifrado;
        unsigned int tamanioArchivo; 
	if ((archivobin = fopen ("cifrado.mov", "rb")) ==NULL){
	perror("No se puede abrir archivo para cifrar.");
	return -1;
	}
	fseek(archivobin,0,SEEK_END);
	tamanioArchivo = ftell(archivobin);
	tamanioArchivo = 100;
	rewind(archivobin);	
	unsigned char * datosArchivo = (unsigned char *)malloc(tamanioArchivo*sizeof(unsigned char));
	unsigned char * datosAuxiliar = datosArchivo;
	unsigned char * intercambioDatos = (unsigned char *)malloc(tamanioArchivo*sizeof(unsigned char));
	unsigned char * intercambioArreglo = intercambioDatos;
	fread(datosArchivo,1,tamanioArchivo,archivobin);
	/***********************************************************************************/

	/***************** Ahora inicializamos los mapas caóticos Renyi. *******************/
	unsigned int numeroMapas =4;
        unsigned int Xn[numeroMapas]; 

	unsigned int x1 = 43554;
	unsigned int parametro1 = 243;
	unsigned int parametro2= 234;
	unsigned int x2 = 34344;

	unsigned char * prtXn =(unsigned char *) Xn;   
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
	unsigned int tamRTP=50; 
	unsigned int numPaquetesRTP=tamanioArchivo/tamRTP; 
	unsigned char segmentos[10];

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
	unsigned int irtp;
	unsigned int auxiliar;
	unsigned char iSeg;
        unsigned char * p1;
	unsigned char * p2;
	unsigned int bitRef;
	unsigned int posicionInversion;
	unsigned char p;
	unsigned char count=0;
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




		/*========= Proceso de Permutacion ========================================*/
		/*Primero, iniciamos el arreglo referencia.*/	
                segmentos[0]=0;   segmentos[1]=1;   segmentos[2]=2;   segmentos[3]=3; 
                segmentos[4]=4;   segmentos[5]=5;   segmentos[6]=6;   segmentos[7]=7; 
                segmentos[8]=8;   segmentos[9]=9;  
	       	

       
                /*Hacemos intercambio en el arreglo segmentos.*/
		for(iSeg =NUMSEGMENTOS; --iSeg;){  

                        x1 = RENYI_MAP(x1,parametro1,j);
			x2 = RENYI_MAP(x2,parametro2,j);
                            
			T =  (x1 & x2) %(iSeg);


		        auxiliar = segmentos[iSeg];
			segmentos[iSeg] = segmentos[T];
			segmentos[T] = auxiliar;
   
		}/*Fin del for que recorre los segmentos del paquete RTP.*/
                

		/*En este momento, tenemos el arreglo segmentos que nos dice cómo están ordenados los
		segmentos del paquete RTP correspondiente, ahora, lo que sigue es volver a ponerlos en
		su posición original.
                Lo anterior me dice: El cero de datosAuxiliar, llevalo al siete, el 1segmento llevalo 
		al 6, el 2 llevalo al 5 el 3 llevalo al nueve.*/

                /*Lei mis datos y estan en datos auxiliar.*/
                p1= datosAuxiliar;
                for(iSeg=0; iSeg<NUMSEGMENTOS; iSeg++){
                        p2 =intercambioArreglo + tamanioSegmento*segmentos[iSeg];
			memcpy(p2,p1, tamanioSegmento);
		        p1+= tamanioSegmento; 
		}/*Fin del for para la permutacion de segmentos*/
		
		

                /*========= Proceso de Inversion de bits ==========================*/
	        bitRef=0;	
	        epsilon = (H & 15);
	
                while((bitRef+BF)<numBitsRTP){

			newH=0;
			Xn[0]= RENYI_MAP(Xn[0],parametros[0],j)+ (epsilon^H);
			newH^=Xn[0]; 
                        Xn[1]= RENYI_MAP(Xn[1],parametros[1],j)+ (epsilon^H);
			newH^=Xn[1]; 
			Xn[2]= RENYI_MAP(Xn[2],parametros[2],j)+ (epsilon^H);
			newH^=Xn[2]; 
			Xn[3]= RENYI_MAP(Xn[3],parametros[3],j)+ (epsilon^H);
			newH^=Xn[3]; 
			H = newH&255;


			for( count=0; (count < 16)&&((bitRef+BF) < numBitsRTP); ) { 
                           
		                p=( prtXn[count]  % (BF-2)  ) + 1;

				bitRef+=p;
                                count++;  
				/*Si un numero aleatorio es impar...*/
				if(p&1){  
		                	posicionInversion = bitRef+( prtXn[count]  % (BF-p));                                                       
				}
				/*Si el un numero aleatorio es par...*/
				else{
		                	posicionInversion = bitRef-( prtXn[count]  % p);			
				}

		                intercambioArreglo[posicionInversion>>3]^=flip[posicionInversion & 7];     
		                count++;  
			}
                }/*Fin del ciclo while para inversion de bits en el segmento.*/

	
	
        	/*Ahora, datosAuxiliar se mueve al siguiente paquete RTP.*/
        	datosAuxiliar+= tamRTP; 
		intercambioArreglo+=tamRTP;  
		      
	}/*Fin del ciclo de paquetes RTP.*/
	/***********************************************************************************/

	//imprimirArreglo1D( intercambioDatos, tamanioArchivo, tamanioSegmento);

 
        /******************** Estructuras para medir el tiempo de calculo ******************/
        if (gettimeofday(&tv2,0) == -1) {
		printf("ERROR time2\n");
		exit(1);
	}
	printf("Segundos = %ld, Microsegundos = %ld\n",tv2.tv_sec,tv2.tv_usec);

	
	/*Tiempo transcurrido.*/
	if (tv1.tv_usec > tv2.tv_usec) {  
		//printf(" ======= \n");
		tv2.tv_usec += 1000000;
		tv2.tv_sec--; 
	} 
        

	tsec = (tv2.tv_sec - tv1.tv_sec)*1000.;      /*Tiempo en milisegundos.*/
	tusec = (tv2.tv_usec - tv1.tv_usec)/1000.;
	
	printf("MIlisegundos de tv_sec= %f, MIlisegundos de tv_usec = %f, TIempo total = %f Milisegundos \n",tsec,tusec,tsec+tusec);
	printf("Megabits/sec = %f \n",((numPaquetesRTP*tamRTP*8)/(1000.0*1000.0))/((tsec + tusec)/1000.0));
	/***********************************************************************************/
   

    
	/*****************************Escritura de resultados*******************************/
        archivoCifrado =  fopen("otraVezElBueno.mov", "wb");
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


void imprimirArregloIndices(unsigned char * segmentos, unsigned int tam){
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































//------------------------------------------------------------------------------------

/*========= Proceso de Permutacion ========================================*/
		/*Primero, iniciamos el arreglo referencia.*/	
                //segmentos[0]=0;       segmentos[1]=1;   segmentos[2]=2;   segmentos[3]=3; 
                //segmentos[4]=4;       segmentos[5]=5;   segmentos[6]=6;   segmentos[7]=7; 
                //segmentos[8]=8;       segmentos[9]=9;   segmentos[10]=10; segmentos[11]=11; 
                //segmentos[12]=12;     segmentos[13]=13; segmentos[14]=14; segmentos[15]=15; 
                //segmentos[16]=16;     segmentos[17]=17; segmentos[18]=18; segmentos[19]=19; 
	       	
                /*limite se utiliza para ahorrar restas en el ciclo.*/
                //limite=NUMSEGMENTOS-1;
                /*El ciclo realiza lo que dice al paper: aplicar intercambio hasta el
                segundo elemento, el primero no tiene caso porque no 
		tiene con quien intercambiarse.*/
           //for(iSeg =limite-1;iSeg > 0; iSeg--) {
       
			//X = RENYI_MAP(H,parametroShuffling1,jShuffling1);
			//Y = RENYI_MAP(H,parametroShuffling2,jShuffling2);
                
                
			//T =  (prtX & prtY) % (iSeg);

		     //auxiliar = segmentos[iSeg];  // segmentos hacer unsigned char
			//segmentos[iSeg] = segmentos[T];
			//segmentos[T] = auxiliar;
            //}  
    
		//}/*Fin del for que recorre los segmentos del paquete RTP.*/

           // llenar pkt
           //for(count = 0;count < limite;count++) {
                /*Ahora se hace intercambio con el valor del ultimo elemento.*/
			//memcpy(datosPkt[count],datosAuxiliares[segmento[count]]);
                //datosAuxiliares[segmento[count]]) += tamRTP; 
		 //} 
      
  
	//}/*Fin del ciclo de paquetes RTP.*/
	/***********************************************************************************/
