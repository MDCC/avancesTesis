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
    cout<<"método de Vigenere"<<endl;
// el constructor de ifstream abre el archivo
ifstream textoPlano( "alicia2.txt", ios::in );
// sale del programa si ifstream no pudo abrir el archivo
if (!textoPlano)
{
cerr << "No se pudo abrir el archivo de lectura." << endl;
exit( 1 );
} 


ofstream archivoSalida("enctriptado.txt", ios::out);
// sale del programa si ifstream no pudo abrir el archivo
if (!archivoSalida)
{
cerr << "No se pudo abrir el archivo de salida." << endl;
exit( 1 );
} 


char c;

// Por el momento declaramos una llave en mayusculas.
unsigned char llave[]={'L','O','U','P'};

//Formamos la tabla de thritemius.
unsigned char **tablat = new unsigned char*[26];
for(int i =0; i<26; i++){
    tablat[i]= new unsigned char[26];
}
unsigned char valor;
for(int i =0; i<26; i++){
    for(int j =0; j<26; j++){
        valor=(65+i)+j;
        if(valor>90){
            valor-=26;
        }
        tablat[i][j]=valor;
    }
}

for(int i =0; i<26; i++){
    for(int j =0; j<26; j++){
        cout<<tablat[i][j]<<" ";
    }
    cout<<endl;
}


  //Procedimiento para cifrar el archivo.
  //Mientras haya caracteres en el archivo.
int posicion=0;
int posicionLlave=0;
unsigned char caracter1;
while((c=textoPlano.get())!=EOF){ 

    //Si el caracter de entrada es una mayuscula...
        if((c>='A') &&( c<='Z')){
           //Obtenemos el caracter pero ya cifrado.
            if(posicion>25){
                posicion-=26;
            }
            
            if(posicionLlave>3){
              posicionLlave-=4;
            }
                
                caracter1=tablat[c-65][llave[posicionLlave]-65];  
                archivoSalida<<caracter1;
                posicion++;
                
                
                posicionLlave++;
          }
        else{
          archivoSalida<<c;
        }
    
  
      }
    
    //Cerramos los archivos.
    archivoSalida.close();
    textoPlano.close();
   return 0;
 }
         

