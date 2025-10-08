#include <iostream>

using namespace std;

// Assinatura da função para o programa reconhecê-la
double mediaDeVariosNumeros(int a, int b, int c, int d, int e);

int main()
{
    int n1, n2, n3, n4, n5;
    // Leio no teclado os valores de "n1", "n2", "n3", "n4", "n5"
    cin >> n1 >> n2 >> n3 >> n4 >> n5;
    // Chamo a função inserindo os parâmetros necessários
    // Retorna a média dos valores inseridos
    cout << "Media: " << mediaDeVariosNumeros(n1, n2, n3, n4, n5) << endl;

    return 0;
}

// Criei a função(tipo, nome, parâmetros)
double mediaDeVariosNumeros(int a, int b, int c, int d, int e)
{
    // Código a ser executado ao chamar a função
    double soma, media;       // Criei as variáveis "soma" e "media"
    soma = a + b + c + d + e; // Atribuí a "soma" os valores inseridos nos parâmetros
    media = soma / 5;         // Atribuí a "media" o valor de "soma" dividido por 5
    return media;             // Retorna o valor de "media"
}
