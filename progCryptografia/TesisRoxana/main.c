/* 
 * File:   main.c
 * Author: daniel
 *
 * Created on 19 de enero de 2014, 12:23 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <sys/time.h>
//#include "Archivos.h"
/*
 * 
 */

#define ITERA 3000 
#define ITERA1 10000
#define TAMTA 1000
#define NUMVG 100
#define CAMUL 20
int NUMAP;

//Ahora, definimos los prototipos de funciones que vamos a necesitar.
double mapaLogis(double lambda, double xn);

//Genera las ITERA iteraciones de los NUMAP mapas
int mapasLogis(const double *lambdas, const double *Xn0, double *Xn );

//Establece los parametros iniciales de los mapas.
int iniciales(double *lambdas, double *Xn0, const unsigned int *clave );

//Establece valores iniciales de retroalimentacion.
int iniRetroAli(unsigned int *tCifrado);

//Lee la clave de un archivo y obtiene el numero de mapas.
int obtenClave(unsigned int **clave);

//Cifrado de los datos.
int cifrador(const unsigned int *clave);



int main(int argc, char** argv) {
    
    unsigned int *clave = NULL, semilla =0; //Se almacena la clave para el 
                                            //Sistema.
    
    int i;
    struct timeval tv1, tv2;
    
    if(gettimeofday(&tv1,0)==1)
        perror("Lectura de Tiempo \n");
    
    obtenClave(&clave);

    return (EXIT_SUCCESS);
}


int obtenClave(unsigned int **clave){

    FILE *abre = NULL; //Apuntador al archivo.
    unsigned int tam; //Almacena tamanio del archivo abierto.
    
    //Nombre del archivo y modo en que se abrira.
    char nombre[TAM_NOM_A]="", modo[5]="";

}