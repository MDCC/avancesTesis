/* 
 * File:   main.cpp
 * Author: daniel
 *
 * Created on 31 de enero de 2014, 05:20 AM
 */

#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

/*Declaramos propotipos de funciones*/
void imprimirMatriz(double * arreglo, int tamanio){

    for(int i =0; i<tamanio; i++){
        cout<<" "<<arreglo[i];
    }
}
/*
 * 
 */
int main(int argc, char** argv) {
     
    
    double xgorro[256];
    int k=5;
    for(int i =0; i<256; i++){
        xgorro[i]=i/256.0;
    }
    
    
    //Imprimimos los valores entre 0 y 1 xgorro.
    imprimirMatriz(xgorro, 256);

    double Gamma[256];

      for(int i =0; i<256; i++){
        Gamma[i]=xgorro[i]*256;
    }
    
    cout<<endl<<"------ Ahora, imprimimos Gamma ------"<<endl;
    imprimirMatriz(Gamma, 256);
    
    
    cout<<endl<<"------ Ahora, imprimimos la forma basica de renyi map ------"<<endl;
    int b=5;
    double figorro[256];
      for(int i =0; i<256; i++){
        figorro[i]=int(floor((b*Gamma[i]))) % 256;
    }
    imprimirMatriz(figorro, 256);
    
    /*Supongamos que se tiene una parte entera y otra fraccionaria al valor 
     de beta, obtenemos lo siguiente.*/
    int beta=8;
    double gamma = .32125;
    double fkfraccionaria[256];
     for(int i =0; i<256; i++){
        fkfraccionaria[i]=int((beta*Gamma[i]+ int(floor(gamma*Gamma[i])))) % 256;
    }
    
    cout<<endl<<"------Imprimimos esta cosa rara de fraccion------"<<endl;    
    imprimirMatriz(fkfraccionaria, 256);
    
    
    
    return 0;
}


