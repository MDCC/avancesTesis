/* 
 * File:   main.c
 * Author: daniel
 *
 * Created on 9 de febrero de 2014, 12:36 AM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    
    /*Declaramos el arreglo que tiene el mensaje original.*/
    char plaintext[16]= {'0','1','2','3','4','5','6','7','8','9','A','B', 'C','D','E','F'};
    printf(" %d", sizeof(plaintext));

    return (EXIT_SUCCESS);
}

