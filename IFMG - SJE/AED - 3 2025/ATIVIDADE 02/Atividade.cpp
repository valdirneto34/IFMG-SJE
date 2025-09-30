#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    int opcao;
    fstream arq("arquivo.txt");
    arq.open("arquivo.txt", ios::in);
    if(!arq.is_open()){
        cout << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    do
    {
        cout << "\n\nMENU\n\n";
        cout << "Digite a opção desejada:\n";
        cout <<"0 - Sair\n");
        cout<< "1 - Esvaziar a pilha\n");
        cout("2 - Verificar se a lista está pilha\n");
        cout("3 - Empilhar elemento na pilha\n");
        cout("4 - Imprimir os elementos da pilha\n");
        cout("5 - Desempilhar elemento da pilha\n");
        cout("6 - Procurar elemento pelo código\n");
        cout("7 - Contar idades pares na pilha\n");
        cout("8 - Contar idades ímpares na pilha\n");

        scanf("%d", &opcao);
        
    } while (opcao != 0);
    


    arq.close();

    return 0;
}