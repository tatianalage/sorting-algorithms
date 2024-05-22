#include "sorting.h"
#include "sorting.cpp"
using namespace SortingAlgorithms;




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
    
    Node<int>*head = createNode(170);
    insertNodeEnd(&head,45);
    insertNodeEnd(&head,75);
    insertNodeEnd(&head,90);
    insertNodeEnd(&head,802);
    insertNodeEnd(&head,24);
    insertNodeEnd(&head,2);
    insertNodeEnd(&head,66);
    cout << "================================================================================= " << endl;
    cout << "ALGORITMO FUNCIONANDO: " << endl;
    optimizedRadixSort(&head);


    return 0;
}
