/* 
 * File:   main.cpp
 * Author: daniel
 *
 * Created on 1 de septiembre de 2013, 07:52 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    cout<<endl<<"----------------------------------------"<<endl;
    cout<<"Programa para leer un archivo y encriptarlo con base en el "<<endl;
    cout<<"método de Cesar"<<endl;
// el constructor de ifstream abre el archivo
ifstream textoPlano( "alicia2.txt", ios::in );
// sale del programa si ifstream no pudo abrir el archivo
if (!textoPlano)
{
cerr << "No se pudo abrir el archivo de lectura." << endl;
exit( 1 );
} 

////



ofstream archivoSalida("enctriptado.txt", ios::out);
// sale del programa si ifstream no pudo abrir el archivo
if (!archivoSalida)
{
cerr << "No se pudo abrir el archivo de salida." << endl;
exit( 1 );
} 

int k;
char c;
cout<<endl<<"Dame el valor de k: ";
cin>>k;  //!!!!!!!!!!!!!!


  //Procedimiento para cifrar el archivo.
  //Mientras haya caracteres en el archivo.
while((c=textoPlano.get())!=EOF){ //!!!!!!!!!!!!!
    cout<<c<<endl;
    
    //Si el caracter de entrada es una mayuscula...
        if((c>='A') &&( c<='Z')){
                     //Obtenemos el caracter pero ya cifrado.
                     c=c+(k%26);
                     //c=((c+k)%26);
                     //Si el caracter obtenido sobrepasa el limite de las mayusculas...
                     if(c>'Z'){
                         //Hacemos el cambio de manera circular, comenzamos en A.
                         //Y recorremos los lugares que hayan sobrado.
                      c=('A'-1)+c-'Z';
                   }
              }
//
//        //Si el caracter de entrada es una minuscula...
        if((c>='a')&&( c<='z')){
            //Obtenemos el caracter pero ya cifrado, con el modulo aplicado.
             c+=(k%26);
             //c=((c+k)%26);
             //Si el caracter obtenido sobrepasa el limite de las minusculas.
           if(c>'z'){
            c=('a'-1)+c-'z';
             }
//
      }
//

       
       archivoSalida<<c;
      //fputc(c,archivoSalida);
    
}
        
   //Cerramos los archivos.
    archivoSalida.close();
    textoPlano.close();
   return 0;
}
