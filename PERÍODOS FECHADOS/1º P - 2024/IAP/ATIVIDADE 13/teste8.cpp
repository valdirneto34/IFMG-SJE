#include <iostream>

using namespace std;

int a = 10; // Variável global com o valor 10

// Assinatura das funções para o programa reconhecê-las
int funcao1(int a, int b);
int funcao2(int b);

int main()
{
    // Chamo a função inserindo os parâmetros necessários
    funcao1(1, 1);
    // Chamo a função inserindo o parâmetro necessário
    funcao2(5);
    return 0;
}

int funcao1(int a, int b) // Criei a função(tipo, nome, parâmetros)
{
    // Código a ser executado ao chamar a função
    cout << a + b << endl; // Mostro na tela o valor de a+b(as duas variáveis inseridas nos parâmetros)
    return 0;              // Me retorna nada
}

int funcao2(int b) // Criei a função(tipo, nome, parâmetros)
{
    // Código a ser executado ao chamar a função
    cout << a + b << endl; // Mostro na tela o valor de a+b( apenas uma variável inserida nos parâmetros,
                           // a variável a recebeu o valor atribuído na global)
    return 0;              // Me retorna nada
}
