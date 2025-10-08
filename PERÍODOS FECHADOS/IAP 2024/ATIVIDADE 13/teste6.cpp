#include <iostream>

using namespace std;

// Assinatura da função para o programa reconhecê-la
double mediaDeVariosNumeros(int vetor[], int n);

int main()
{
    int vetor[] = {12, 36, 48, 78, 69, 25, 69};
    // Chamo a função inserindo os parâmetros necessários
    cout << "Media: " << mediaDeVariosNumeros(vetor, 7) << endl; // Mostra a média dos numeros no "vetor[]"

    return 0;
}

// Criei a função(tipo, nome, parâmetros)
double mediaDeVariosNumeros(int vetor[], int n)
{
    // Código a ser executado ao chamar a função
    double soma = 0, media; // Criei as variáveis "soma" e "media"
    // Criei um for para adicionar os valores do "vetor[]" na vaiável "soma"
    for (int i = 0; i < n; i++)
    {
        soma += vetor[i]; // soma = soma + vetor[i]
    }
    // A "media" recebe a "soma" dividida pela qtd de números
    media = soma / n;

    return media; // Retorna o valor de "media"
}
