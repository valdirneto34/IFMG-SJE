#include <iostream>

using namespace std;

void hello(); // Assinatura da função para o programa reconhecê-la

int main()
{
    hello(); // Chamo a função

    return 0;
}

void hello() // Criei a função(tipo, nome, parâmetros)
{
    // Código a ser executado ao chamar a função
    cout << "Hello!" << endl;
}
