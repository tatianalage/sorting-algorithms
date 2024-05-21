#include "sorting.h"
#include "sorting.cpp"



int main(){
    cout << "Ao inicializar o Radix Sort, encontramos o maior elemento da lista encadeada para assim determinar quantas digitos seram necessários para ordenação." << endl;
    cout << "Depois ordenados pelos dígitos agrupando-os em buckets. Após o agrupamento, reunimos todos o elementos prezando pela ordem encotrada pelos buckets e repetimos o mesmo processo para o dígito seguinte." << endl;
    cout << "Dividos nas seguintes etapas:" << endl;
    cout << "Etapa 1: Verifica se a lista está vazia" << endl;
    cout << "Etapa 2: Encontra o valor máximo na lista" << endl;
    cout << "Etapa 3: Ordenação dos elementos baseada nos dígitos" << endl;
    cout << "Etapa 4: Distribui os elementos nos baldes" << endl;
    cout << "Etapa 5: Adiciona o nó ao final do balde" << endl;
    cout << "Etapa 6: Concatena os baldes para formar a nova lista" << endl;
    cout << "Repete o processo!" << endl;

    cout << "EXEMPLO: " << endl;
    cout << "Analizemos [170, 45, 75, 90, 802, 24, 2, 66]" << endl;
    cout << "802 é o maior elemento! " << endl;

    cout << "exp = 10" << endl;
    cout << "Bucket 0: 170" << endl;
    cout << "Bucket 1: Nenhum" << endl;
    cout << "Bucket 2: 802, 2" << endl;
    cout << "Bucket 3: Nenhum" << endl;
    cout << "Bucket 4: 24" << endl;
    cout << "Bucket 5: 45, 75" << endl;
    cout << "Bucket 6: 66" << endl;
    cout << "Bucket 7: Nenhum" << endl;
    cout << "Bucket 8: Nenhum" << endl;
    cout << "Bucket 9: 90" << endl;
    cout << "Ordenação parcial dos elementos usando o primeiro dígito." << endl;
    cout << "170 90 802 2 24 45 75 66" << endl;
    cout << "Agora reunimos todos os buckets para formar a nova lista." << endl;

    cout << "exp = 100" << endl;
    cout << "Bucket 0: 802" << endl;
    cout << "Bucket 1: Nenhum" << endl;
    cout << "Bucket 2: 2, 24" << endl;
    cout << "Bucket 3: Nenhum" << endl;
    cout << "Bucket 4: 45" << endl;
    cout << "Bucket 5: 66" << endl;
    cout << "Bucket 6: Nenhum" << endl;
    cout << "Bucket 7: Nenhum" << endl;
    cout << "Bucket 8: Nenhum" << endl;
    cout << "Ordenação parcial dos elementos usando o segundo dígito." << endl;
    cout << "802 2 24 45 66 170 75 90" << endl;
    cout << "exp =1000"  << endl;
    cout << "Quebra do While" << endl;
    
    cout << "RESULTADO: " << endl;
    cout << "2 24 45 66 75 90 170 802" << endl;
    return 0;
}
