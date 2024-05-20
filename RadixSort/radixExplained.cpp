#include "sorting.h"
using namespace std;
#include "sorting.cpp"

int main(){
   
    cout <<"70,45,75,90,802,24,2,66" << endl;
    cout << "Incialmente, localizamos o maior elemento da lista" << endl;
    cout << "Após isso ordenamos em relação a menor dígito das unidades:" << endl;
    cout <<"170,90,802,2,24,45,75,66" << endl;
    cout << "Repetimos esse processo usando os elementos das dezenas!" << endl; 
    cout << "802,2,24,45,66,170,75,90" << endl;
    cout << "Agora repetimos o mesmo processo para as centenas" << endl;
    cout << "2,24,45,66,75,90,170,802" << endl;

}