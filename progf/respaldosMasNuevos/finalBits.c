#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>


/*Celcaramos los prototipos de funciones, recordemos que se va a trabajar con un erreglo de tipo
unsigned char.*/
void intercambiarArreglo( unsigned char * , unsigned int , unsigned int , unsigned int , unsigned int );
void imprimirArreglo1D(unsigned char *, unsigned int);
void shuffling(unsigned char * , unsigned int , unsigned int , unsigned int , unsigned int );
void flippingBits(unsigned char *,  unsigned int, unsigned int  );



int main(){



/*Primero, abrimos los archivos que vamos a utilizar para esta cosa
rara. Tambien abrimos el archivo que queremos leer. La informacion
se guarda en un arreglo previamente definido. int tiene un tamanio de
4 bytes. SUpongamos que queremos 300 bytes, que es un tamanio aceptable para
los paquetes rtp. Entonces necesitamos 300 bytes*/
unsigned int tamanioArreglo = 20;
unsigned char Xtotal[tamanioArreglo]; 
FILE * archivobin;
   archivobin = fopen ("binarioXOR.dat", "wb");
   if (archivobin==NULL)
   {
   perror("No se puede abrir binario.dat");
   return -1;
   }


/*Escribimos la informacion: indicamos el arreglo, el numero de bytes que
conforman al tipo de dato utilizado, el numero de elementos a guardar, y
el archivo de donde lo vamos a leer.*/
 fread(Xtotal,1,tamanioArreglo,archivobin); 




/*Supongamos que T = 3, M=5.*/

unsigned int T = 3;
unsigned int M = 5;
unsigned int L = 5;


/*Llamamos al metodo que vamos a utilizar.*/
shuffling(Xtotal, T, M, L, tamanioArreglo);


unsigned int k = 4;
unsigned int Av= 8;

printf("\n Ahora, vamos a intertir bits, k =4 \n");
imprimirArreglo1D(Xtotal,tamanioArreglo);
flippingBits(Xtotal, Av, k);
imprimirArreglo1D(Xtotal,tamanioArreglo);


return 0;

/*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;*/

}



void shuffling(unsigned char * A , unsigned int T, unsigned int M, unsigned int L, unsigned int tamanio){
/*unsigned int M=L;*/
unsigned int i;
unsigned int R;
/*unsigned int T;*/
srand (time(NULL));
for(i =1; i<L; i++){
	//Generate random number R
	R= rand();
	T= R%M+1;
        printf("\n R: %u    T: %u    M: %u   \n", R, T, M);
	imprimirArreglo1D(A, tamanio);
	intercambiarArreglo(A, T, M, L, tamanio);
	imprimirArreglo1D(A, tamanio);
        M=M-1;
}

}

void intercambiarArreglo( unsigned char * A , unsigned int T, unsigned int M, unsigned int L, unsigned int tamanio){
	/*Recordemos que los indices van de 0 a 19 (en este caso.)
	  Ademas, en este caso, tamanioBOloque es igual a 4.*/
	unsigned int tamanioBloque = tamanio/L;

	/*Ahora, hacemos el intercambio que sea necesario.*/
	unsigned int i;
	unsigned int auxiliar;
	for(i=0; i<tamanioBloque; i++){
		auxiliar = A[tamanioBloque*(T-1)+i];
		A[tamanioBloque*(T-1)+i]=A[tamanioBloque*(M-1)+i];
		A[tamanioBloque*(M-1)+i]= auxiliar;
	}
}




void flippingBits(unsigned char * A, unsigned int Av, unsigned int k){
	/*Elegimos la posicion, que depende de tamanio promedio de codigos. Obtenemos un numero entre 0 y 7.*/
        unsigned int aleatorio = rand();
         
        /*Posicion de referencia en el bloque de bits.*/
        unsigned int Pos = aleatorio%Av + 1;
	unsigned int flipbitPos;
        unsigned int db= Pos-1;
	unsigned int de= Av - Pos; 
        unsigned int posFinal;


       
        if((aleatorio%2)==0){
                /*Por ejemplo, podemos obtener un valor entre 1  y 4.*/
		flipbitPos = ( aleatorio  % db)+1;
                posFinal = Pos-flipbitPos;
//$$$$$$$$$$$$Esta mal el posFInal en el indice del arreglo
                A[posFinal-1]= A[posFinal-1]^(1<<posFinal);
        }
        else{
                /*Por ejemplo, podemos obtener un valor entre 1  y 3.*/
		flipbitPos = ( aleatorio  % de)+1;
                posFinal = Pos+flipbitPos;
//$$$$$$$$$$$$Esta mal el posFInal en el indice del arreglo
                A[posFinal-1]= A[posFinal-1]^(1<<posFinal);
        }

	


}

void  imprimirArreglo1D( unsigned char *A, unsigned int tamanio){

        printf("\n");
        unsigned int i;
	for( i =0; i<tamanio; i++){
		printf("%u  ", A[i]);
	}
        printf("\n");	

}



