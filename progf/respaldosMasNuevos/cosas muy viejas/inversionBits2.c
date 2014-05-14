#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>

void imprimirArreglo(unsigned char *, unsigned int);

/*En este ejemplo, se hace el cifrado por medio del esquema que se
platico en el aula de usos multiples: utiliza los bits de referencia
que se encuentran ANTES de hacer un recorrido de y db.*/

int main(){


        //arreglo donde los primeros 4 son un RTP los segundos 4 son otro RTP.
    
	unsigned char textos[8]; 
        unsigned int tamanioArreglo = 8; 
	unsigned int tamRTP=4; //4 bites para un RTP
	unsigned int numBitsSegmento = tamRTP*8; /*Numero de bytes del segmento por el numero de bits.*/
	unsigned int avCodigo=8;
	unsigned int tamanioArchivo = 64;        
        unsigned int numPaquetesRTP=2;
        unsigned int i;
	unsigned int irtp;
        unsigned int refRTP;
	unsigned int bitRef;
	unsigned int p;
	unsigned int aleatorio;
	unsigned int posicionInversion;
	int cambio;
 
        srand(time(NULL));

	for(i =0; i< 8; i++){
		textos[i]=i;
	}

	imprimirArreglo(textos, tamanioArreglo);

    


        for(irtp=0; irtp < numPaquetesRTP; irtp++ ){
		/*El tamanio del archivo es de */

		refRTP=tamRTP*irtp;
		bitRef=0;	
                unsigned int iteraciones =0;	
		while((bitRef+avCodigo) <numBitsSegmento){
                
		        /*Tabajamos con el primer octeto de codigo.*/
		        printf("\n bitRef: %u",bitRef);
		        aleatorio=rand()+1;
                        p=(aleatorio %(avCodigo-2))+1;
		        bitRef+=p;
                        printf("   p: %u   bitRefConP: %u",p,bitRef);
		
			
		       /*Si el numero aleatorio es impar...*/
		        if(aleatorio&1){  
				//Estos son los step y el pos_F.	
				posicionInversion=(aleatorio%(avCodigo-p));
				bitRef+=posicionInversion;
				cambio = -posicionInversion;
				printf("   posInversion: %u   bitRefConINversion: %u",posicionInversion,bitRef);
		        }
			/*Si el numero aleatorio es par...*/
		        else{
				//Estos son los step y el pos_F.
			        posicionInversion=(aleatorio % p);
				bitRef-=posicionInversion;
                                cambio = posicionInversion;
                                printf("   posInversion: %u   bitRefConINversion: %u",posicionInversion,bitRef);	
		        }

			textos[refRTP+(bitRef/8)]^=(1<<(avCodigo-(bitRef&7)-1));
                        printf("   posicionArreglo: %u   cosaestrania: %u",refRTP+(bitRef/8),(1<<(avCodigo-(bitRef&7)-1)));
                        
                        /*Una vez que se ha hecho la inversion, ahora es necesario recordar la posicion de referencia original.*/
                        bitRef+=cambio;


		}/*Fin del While.*/
        }/*Fin dei ciclo que reccorre los bloques.*/

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

