#include <iostream>

using namespace std;

int soma(int a, int b); // Assinatura da função para o programa reconhecê-la

int main()
{
    // Chamo a função inserindo os parâmetros necessários
    cout << "Soma: " << soma(23, 69) << endl; // Mostro na tela o valor retornado na minha função

    return 0;
}

int soma(int a, int b) // Criei a função(tipo, nome, parâmetros)
{
    // Código a ser executado ao chamar a função
    int soma;     // Crio uma variável soma
    soma = a + b; // Atribuí a ela o valor de a+b(ambos inseridos nos parâmetros)
    return soma;  // Retorna o valor da vriável soma
}
