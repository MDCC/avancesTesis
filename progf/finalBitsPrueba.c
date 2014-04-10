#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>



/*Definiciones necesarias: MAPA RENYI.*/
#define RENYI_MAP(var, parametro, j) ((var)*(parametro)+((var)>>(j)))

/*Celcaramos los prototipos de funciones, recordemos que se va a trabajar con un erreglo de tipo
unsigned char.*/
void imprimirArreglo1D(unsigned char *, unsigned int, unsigned int);
//void flippingBits(unsigned char *,  unsigned int, unsigned int  );

void imprimirArregloIndices(unsigned int *, unsigned int);

int main(){


/******************* Lectura de archivos y asignacion de memoria. ******************/
unsigned int tamanioArchivo; 
FILE * archivobin;
if ((archivobin = fopen ("lena.jpg", "rb")) ==NULL){
perror("No se puede abrir binario.dat");
return -1;
}
fseek(archivobin,0,SEEK_END);
tamanioArchivo = ftell(archivobin);
tamanioArchivo=100;
rewind(archivobin);	
unsigned char * datosArchivo = (unsigned char *)malloc(tamanioArchivo*sizeof(unsigned char));
fread(datosArchivo,1,tamanioArchivo,archivobin); 
/***********************************************************************************/

/***************** Ahora inicializamos los mapas caóticos Renyi. *******************/
unsigned int numeroMapas =4;
unsigned int Xn[numeroMapas]; 
unsigned int clave[numeroMapas]; 
unsigned int parametros[numeroMapas];
unsigned int H=0; 
unsigned int j=9; /*No mas de 16.*/
//unsigned int iteraciones=0;
//unsigned int IT = 80000;
int epsilon;


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

                   

/*Primero, hacemos un ciclo inicial para calcular un nuevo valor para cada
uno de los mapas y calcular, por primera vez, el resultado de la operacion
XOR.*/
unsigned int i;
for( i =0; i<numeroMapas; i++){
	Xn[i]= RENYI_MAP(Xn[i],parametros[i],j);
	H^=Xn[i];
}
      
/*Tambien al primer H se le aplica el mod.*/
 H%=256; 
 
/*Elegimos un epsilon aleatorio entre 1 y 16 (para operaciones de 32 bits).
En este caso, elegimos uno que este entre 0 y 15.*/
epsilon = 1;   
unsigned int k;
unsigned long newH;
   //do {
        
        newH = 0;
        for(k=0;k<numeroMapas; k++){            
            Xn[k]= RENYI_MAP(Xn[k],parametros[k],j) + epsilon*H;  
            newH^=Xn[k];      
        }
        H = newH;
        //printf("\nla iteracion %d  para  %lu H es:  \n", contDeH,arregloH[contDeH] );
   
        /*BUscamos un H pequeño: la perturbación no debe ser 
        tan fuerte. Por tal motivo, se aplica una operación módulo.*/
        H%=256; 
        
        /*Ahora, elegimos un valor para epsilon.*/
        epsilon = (H & 1)?1:-1;
    
/***********************************************************************************/


/************ Declaracion de variables para cifrado parcial ************************/
unsigned int tamanioPaqueteRTP=50; /*Tamanio de paquete,  varia de 300 a 1400.*/
unsigned int numPaquetesRTP=tamanioArchivo/tamanioPaqueteRTP; 
unsigned int Lsegmentos = 10;  /*Segmentos a permutar, orita lo puse fijo.*/
unsigned int segmentos[10];
unsigned int tamanioSegmento = tamanioPaqueteRTP/Lsegmentos;
unsigned int M; /*Es el M que aparece en el paper.*/
unsigned int T; /*Esta T se usa para elegir el segmento de manera aleatoria.*/ 
unsigned int irtp;
unsigned int iTamSeg;
unsigned int auxiliar;
unsigned int iSeg;
unsigned int R;
unsigned int posicion1;
unsigned int posicion2;
unsigned int referencia;
unsigned int tamanioCodigo=8;
unsigned int bitRef;
unsigned int aleatorio;
unsigned int posicionInversion;
unsigned int db;
unsigned int de;
/***********************************************************************************/


/*********** Proceso de cifrado para cada uno de los paquetes RTP ******************/
for(irtp=0; irtp < numPaquetesRTP; irtp++ ){

        /*========= Proceso de Inversion de bits ==================================*/

        /*=========================================================================*/
       
        /*========= Proceso de Permutacion ========================================*/
	/*Primero, iniciamos el arreglo referencia.*/	
	for(i=0; i < Lsegmentos; i++)
		segmentos[i] = i;
        printf("\n El paquente numero  %u  \n \n",irtp);
       	
	srand (time(NULL));
	for(iSeg =Lsegmentos; iSeg >1; iSeg--){
	
                T= rand()%(iSeg-1); /*Generamos un valor aleatorio. */
	        
		//==========Pendiente de revision=============================
		printf("\n\n\n   T: %u    M: %u   \n",T, iSeg-1);
		imprimirArreglo1D(datosArchivo, tamanioArchivo, tamanioSegmento);
                auxiliar = segmentos[iSeg-1];
		segmentos[iSeg-1] = segmentos[T];
		segmentos[T] = auxiliar;
                //@#%#$%#$%#aqui vamos bien creo.... 
		//pos_byte = Blocks[i-1]*Bl_Size_byte;
                imprimirArregloIndices(segmentos, 10);
		//==========Pendiente de revision=============================

	        /*Ahora, hacemos el intercambio que sea necesario.*/
	        for(iTamSeg=0; iTamSeg<tamanioSegmento; iTamSeg++){
                        /*Primero, nos posicionamos en el elemento iTamSeg del bloque T...*/
		   	posicion1=(tamanioSegmento*(T)+iTamSeg) + (irtp*tamanioPaqueteRTP);
                       /*Ahora, nos posicionamos en el elemento iTamSeg del bloque final (iTamSeg)...*/
			posicion2=(tamanioSegmento*(iSeg-1)+iTamSeg) + (irtp*tamanioPaqueteRTP);
                        /*Hacemos el intercambio.*/ 
		        auxiliar = datosArchivo[posicion1];
		        datosArchivo[posicion1]=datosArchivo[posicion2];
		        datosArchivo[posicion2]= auxiliar;
	        }
		imprimirArreglo1D(datosArchivo, tamanioArchivo, tamanioSegmento);	
	}
        /*=========================================================================*/

        	
}

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


