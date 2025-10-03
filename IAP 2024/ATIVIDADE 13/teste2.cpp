#include <iostream>

using namespace std;

void soma(int a, int b); // Assinatura da função para o programa reconhecê-la

int main()
{
    // Chamo a função inserindo os parâmetros necessários
    soma(23, 69);

    return 0;
}

void soma(int a, int b) // Criei a função(tipo, nome, parâmetros)
{
    // Código a ser executado ao chamar a função
    int soma;                         // Crio uma variável soma
    soma = a + b;                     // Jogo nessa variável o valor de a+b
    cout << "Soma: " << soma << endl; // Mostro na tela o valor de soma
}
