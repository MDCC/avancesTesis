#include <iostream>
using namespace std;
main(){
  int k =5;
  int l =10;


  int contador =0;
  int s=0;
  cout<<endl<<"Generador Lineal Congruencial"<<endl;
  cout<<endl<<"------------------------------"<<endl;
  while (contador <30){
    contador++;
    cout<<contador<<"  "<<s<<endl;
    s= (3*s+5)%31;
   
   }
  return 0;
}
