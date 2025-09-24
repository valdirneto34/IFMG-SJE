#include <iostream>

using namespace std;

int main()
{
    // criei um vetor do tipo double sem especificar o seu tamanho, mas ao declarar os valores que serao atribuidos a ele, o compilador vai atribuir esse valor
    double notas[] = {20.5, 23.6, 28.7, 30.9, 20.0};
    // criei um for para mostrar os valores na posicao i do meu vetor
    for (int i = 0; i < 9; i++)
    {
        cout << notas[i] << endl; // mostra o valor guardado na posicao i do meu vetor
    }
    system("pause");
    return 0;
}
