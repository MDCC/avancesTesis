

#include <stdio.h>
#define MAPAS 3


void imprimirArregloIndices(unsigned char * segmentos, unsigned int tam);
/*Este ejemplo muestra un ejemplo simplificado de cómo acceder a un arreglo por medio
de un arreglo de índices posibles, además, se puede observar que al utilizar un contador con
un tipo de dato pequeño, se acota el acceso al arreglo de índices sin necesidad de acceder 
a lugares de memoria no permitidos.*/
int main(){

	unsigned char mapas[256];
	unsigned char i;

	unsigned int Xn[4];
        Xn[0]=34343234;
        Xn[1]=34343235;
        Xn[2]=34343236;
        Xn[3]=34343237;

	/*Inicializacion del arreglo de acuerdo a lo que se ocupa en este caso.*/
	/*Este i siempre va a oscilar entre 0  y 255. Es un ciclo infinito.*/
	for(i=0; i<1000; i++){
		mapas[i]= i&MAPAS;
		printf("%u --",i);
	}

	imprimirArregloIndices(mapas,  256);



   
	/*simulacion del ciclo extranio ese del while */
	for(i=0; i< 300; i++){
		printf("\n El valor del contador es %u. El valor en el arreglo es: %u ", i, Xn[mapas[i]] );
	}



	return 0;

}

void imprimirArregloIndices(unsigned char * segmentos, unsigned int tam){
        unsigned int i;
        printf("\n");
	for( i =0; i<tam; i++){
		printf("%u  ",segmentos[i]);
	}
        printf("\n");	
}
