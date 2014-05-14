

#include <stdio.h>
#define MAPAS 3


void imprimirArregloIndices(unsigned char * segmentos, unsigned int tam);
/*Este programa muestra el corrimiento del valor 1 a la izxquierda con el operador 
de desplazamiento <<. También se muestra un ejemplo de aplicar una máscara de bits AND a distintos valores*/
int main(){



	unsigned int i;
	printf("\n Corrimiento del valor 1.");
	for(i=0; i<20; i++){
		printf("\n %u  valor a la derecha de <<: %u", 1<<i, i);
	}




        unsigned int posiciones[10]={1,7,11,307,378,384,391,393,397,399};
	printf("\n Mascaras de bits a valores de un arreglo .");
	for(i=0; i<10; i++){
		printf("\n Valor: %u	Resultado de máscada &7 %u", posiciones[i],posiciones[i]&7 );
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
