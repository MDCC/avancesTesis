/* 
 * File:   main.cpp
 * Author: daniel
 *
 * Este programa crea una tabla de diferentes valores de k aplicados al 
 * mapa logistico, al acercarce k a 4 el modelo se comporta de una manera caotica
 * en otros valores de k, la poblacion de un sistema puede oscilar entre dos
 * valores o extinguirse.
 */

#include <cstdlib>
#include <fstream>
#include <iostream>


using namespace std;


//string graficarValores= "gnuplot -persistent -e \" plot 'salida2.dat' using 1:2 with lines title 'Mapa Logistico'\"; ";


int main(int argc, char** argv) {

    /*Declaramos el porcentaje de poblacion inicial que puede existir
     en un sistema, si p0=1, seria el valor máximo permitido.*/
    double p0= 0.5;
    double pn=0;
    double pnmasuno=0;
    int noks= 6;
    int n =20;
    
    /*Declaramos un arreglo que contendra los valores de k a analizar. */
    double k[6];
    k[0]=0.5;
    k[1]=1.5;
    k[2]=2;
    k[3]=3.2;
    k[4]=3.5;
    k[5]=3.9;
    
   
    
    /*Ahora, hacemos un ciclo para mostrar los datos encontrados.*/
    for(int kval =0; kval< noks; kval++){
        pn=p0;
        cout<<"\n El valor de k es: "<<k[kval]<<"\n";
        cout<<"Se calcularon n valores, donde n ="<<n<<"\n";
        for(int i =0; i< n; i++){
            pnmasuno= pn*k[kval]*(1-pn);
            pn = pnmasuno;
            cout<<"  "<<pnmasuno;
        }
        cout<<"\n\n\n";
    }
    

   return 0;
}

