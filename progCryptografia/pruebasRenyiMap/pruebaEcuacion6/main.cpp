#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <QtGui/QApplication>
#include "mainwindow.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
using namespace cv;



string graficarValores= "gnuplot -persistent -e \" plot 'solucion.dat' using 1:2 title 'Histograma de la imagen'\"; ";



template <class T>
bool GuardaSolucion(const char *file, T *puntosX, T *puntosY, int n){
//Crea o abre el archivo
ofstream out(file);
if(!out.is_open()){
    cout<<"EL archivo no se pudo leer. "<<endl;
    return false;
}

for(int i =0; i<n; i++){
    //out<<"\n";
        out<<puntosX[i]<<"\t";
        out<<puntosY[i]<<endl;
}
    out.close();
    return true;
}
//===============================================================================




//--------------------------------------------------------------------------
void  ecuacion6(double beta, double n, int k){

    //Hacemos el arreglo para guardar los k valores.
    double *pseudoaleatorios = new double[k];
    cout<<"aqui nomas "<<endl;
    for(int i=0; i<k; i++){
        pseudoaleatorios[i]=int(floor(beta*i*1.0))%(int(pow(2.0,n)));
        cout<<"  "<<pseudoaleatorios[i];
    }
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

    double *xx= new double[k];

    for(int i =0; i<k; i++){
        xx[i]= i+1;
    }

    //==================================================================================
    //Ahora, guardamos los resultados en un archivo de nombre solucion.dat
    GuardaSolucion("solucion.dat",xx, pseudoaleatorios,k);
    //==================================================================================

    //==================================================================================
    //Imprimimos nuestros datos en la tabla.
    system(graficarValores.c_str());
    //==================================================================================






}
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''






int main(int argc, char *argv[])
{

    //Declaramos nuestras variables:
    double beta = 8.32125;
    int n = 5;




ecuacion6(beta, n, 100);

  //Finalmente, calculamos los histogramas de la imagen ecualizada.
  //calcular_histogramas(imagenEcualizada);
}
