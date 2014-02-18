/* 
 * File:   main.cpp
 * Author: daniel
 *
 * Created on 2 de septiembre de 2013, 02:27 PM
 */

#include <cstdlib>
#include <fstream>
#include <iostream>


using namespace std;

/*
 *Ejemplo sencillo de un mapa logistico para el cifrado de datos.
 * Se van a producir valores con un generador logistico por medio de una 
 * expresion de recurrencia. 
 */

string graficarValores= "gnuplot -persistent -e \" plot 'salida2.dat' using 1:2 with lines title 'Mapa Logistico'\"; ";


int main(int argc, char** argv) {

        //hacemos un flujo de salida para mostrar los resultados.
    ofstream archivoSalida("salida.dat", ios::out);
    ofstream archivoSalida2("salida2.dat", ios::out);
    //declaramos un r. debe estar entre 1 y 4.
    
    
    //Cada elemento generado Xn debe estar entre (0-1).
    //Primero declaramos uno inicial.
    
    
    int contador=0;
    for(double k=0.1; k<=4.0; k=k+0.2){
    double xn = 0.1;
    double  r = k;

    archivoSalida<<"valor de r: "<<r<<"    xn inicial: "<<xn<<" "<<"\n";
    for(int i =0; i<20; i++){
        contador++;
        xn= r*xn*(1-xn);
        archivoSalida<<i<<"----->  iteracion: "<<i+1<<" valor de xn: "<<xn<<"\n";
        archivoSalida2<<contador<<"\t"<<xn<<"\n";
    }
  
    
    }
      archivoSalida.close();
      archivoSalida2.close();
   system(graficarValores.c_str());
   for(int i =0; i<20000; i++){
       cout<<"jaj ";
   }

   return 0;
}

