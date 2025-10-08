#include <iostream>

using namespace std;

int main()
{
    int *sequencia; // cria um vetor sem determinar seu tamanho
    int tamanho;
    cout << "Quantos : ";
    cin >> tamanho;
    sequencia = new int[tamanho]; // meu vetor vai receber o valor da variavel tamanho
    // fiz um for para pedir os valores do vetor ao usuario
    for (int i = 0; i < tamanho; i = i + 1)
    {
        cin >> sequencia[i]; // pede o valor qu evai ser atribuido ao vetor na posicao i
    }
    // fiz outro for para imprimir os valores do vetor
    for (int i = 0; i < tamanho; i = i + 1)
    {
        cout << sequencia[i] << endl; // imprime o valor do meu vetor na posicao i
    }
    system("pause");
    return 0;
}
