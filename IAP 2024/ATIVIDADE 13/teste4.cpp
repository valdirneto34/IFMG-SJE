#include <iostream>

using namespace std;

int soma(int a, int b); // Assinatura da função para o programa reconhecê-la

int main()
{
    int n1, n2;
    // Leio os valores que serão atribuídos em "n1" e "n2"
    cin >> n1 >> n2;
    // Chamo a função inserindo os parâmetros necessários
    cout << "Soma: " << soma(n1, n2) << endl; // Mostra a soma entre "n1" e "n2"

    return 0;
}

int soma(int a, int b) // Criei a função(tipo, nome, parâmetros)
{
    // Código a ser executado ao chamar a função
    int soma;     // Crio uma variável "soma"
    soma = a + b; // "soma" = ("a" + "b")
    return soma;  // Retorna o valor de "soma"
}
