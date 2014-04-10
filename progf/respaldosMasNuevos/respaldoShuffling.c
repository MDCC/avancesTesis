#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>

void imprimirArreglo(unsigned char *, unsigned int);

int main(){


        //arreglo donde los primeros 4 son un RTP los segundos 4 son otro RTP.
    
	unsigned char textos[8]; 
        unsigned int tamanioArreglo = 8; 
	unsigned int tamRTP=4; //4 bites para un RTP
	unsigned int avCodigo=8;
	unsigned int tamanioArchivo = 64;        
        unsigned int numPaquetesRTP=2;
        unsigned int i;
	unsigned int irtp;
        unsigned int refRTP;
	unsigned int bitRef;
	unsigned int db;
	unsigned int de;
	unsigned int aleatorio;
	unsigned int posicionInversion;
 
        srand(time(NULL));

	for(i =0; i< 8; i++){
		textos[i]=i;
	}

	imprimirArreglo(textos, tamanioArreglo);

    


        for(irtp=0; irtp < numPaquetesRTP; irtp++ ){
		/*El tamanio del archivo es de */
                
                /*Tabajamos con el primer octeto de codigo.*/
                refRTP=tamRTP*irtp;
                aleatorio=rand()+1;
                bitRef=(aleatorio %(avCodigo-2))+1;
                db=bitRef;//Bits a la izquierda
                de= avCodigo -(bitRef+1);
	        printf("\n bitRef es %u  \n", bitRef);
		printf("\n El valor aleatorio es  %u  \n", aleatorio);

               /*Si el numero aleatorio es par...*/
                if((aleatorio%2)==0){  
			if(db!=0){
				posicionInversion=(aleatorio%db)+1;
				//posicionInversion  = bitRef - posicionInversion;
				//$$$$$$$Esta mal el posFInal en el indice del arreglo
				textos[0+irtp*tamRTP]= textos[0+irtp*tamRTP]^(1<<(avCodigo - (db-posicionInversion+1)));
                                
                              
                                printf("db Obtenido: %u  \n", db );
                                printf("Posicion Inversion en el db: %u  \n",posicionInversion );
                                printf("Numero de inversion que se va a aplicar : %u  \n",(1<<(avCodigo - (db-posicionInversion+1))) );
                                printf("Valor obtenido al final : %u  \n",textos[0+irtp*tamRTP] );
			}
                }
	        /*Si el numero aleatorio es impar...*/
                else{
		        if(de!=0){		
				posicionInversion=(aleatorio%de)+1;
			
		                textos[0+irtp*tamRTP]= textos[0+irtp*tamRTP]^(1<<(de - posicionInversion));
                                
                             
                                printf("de Obtenido: %u  \n", de );
                                printf("Posicion Inversion en el de: %u  \n",posicionInversion );
                                printf("Numero de inversion que se va a aplicar: %u  \n",1<<(de - posicionInversion));
                                printf("Valor obtenido al final : %u  \n",textos[0+irtp*tamRTP] );
			}
                }

        }


	imprimirArreglo(textos, 8);	
	return 0;

	
}

void  imprimirArreglo( unsigned char *A, unsigned int tamanio){
        printf("\n");
        unsigned int i;
	for( i =0; i<tamanio; i++){
		printf("%u  ", A[i]);    
	}
        printf("\n");	

}

