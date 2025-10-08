#include <iostream>

using namespace std;

int main()
{
    // criei um vetor do tipo int com 9 posicoes e atribui valores as suas posicoes
    int idades[9] = {14, 16, 14, 12, 8, 20, 17, 16, 14};
    // criei um for para mostrar os valores na posicao i do meu vetor
    for (int i = 0; i < 9; i++)
    {
        cout << idades[i] << endl; // mostra o valor guardado na posicao i do meu vetor
    }
    system("pause");
    return 0;
}
