#include <stdio.h>
#include <time.h>

void intercambiarArreglo( unsigned int * , unsigned int , unsigned int , unsigned int , unsigned int );
void imprimirArreglo1D(unsigned int *, unsigned int);
void shuffling();

/*Este programa hace el schuffling del arreglo del codigo, aqui las longitudes son predefinidas. Al igual
que los datos. 
Ya funciona el método de Schuffling, pero todavía debemos de revisar qué pasa cuandto R = M, en este
programa, cuando T=M, deja el arreglo tal como está, entonces sería bueno poner una condición que cuando
T=M, no se haga nada. Otra opción también sería impedir que T=M. Otra cosa importante a notar es que
T nunca debe ser cero, porque se accederá a memoria de manera indebida, porque se está ejecutando una 
orden de la siguiente manera: "Intercambia el segmento 0 con el 5", cuando solo hay segmentos del 1 al 5.
Tambien se manda llamar la funcion srand() para obtener numeros aleatorios, que es lo que se ocupa 
en el algoritmo.*/

main(){

/*Supongamos que T = 3, M=5.*/
unsigned int tamanio = 20;
unsigned int T = 3;
unsigned int M = 5;
unsigned int L = 5;
unsigned int  A[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

/*Llamamos al metodo que vamos a utilizar.*/
shuffling(A, T, M, L, tamanio);

}


void shuffling(unsigned int * A , unsigned int T, unsigned int M, unsigned int L, unsigned int tamanio){
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

void intercambiarArreglo( unsigned int * A , unsigned int T, unsigned int M, unsigned int L, unsigned int tamanio){

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

void  imprimirArreglo1D( unsigned int *A, unsigned int tamanio){

        printf("\n");
        unsigned int i;
	for( i =0; i<tamanio; i++){
		printf("%u  ", A[i]);
	}
        printf("\n");	

}


