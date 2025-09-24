#include <iostream>

using namespace std;

int main()
{
    string nomes[6] = {"Tereza", "Jonas", "Beatriz", "Jamal", "Alice", "Renzo"}; // criei um vetor do tipo string com 6 posicoes e guardei os nomes nelas

    for (int i = 0; i < 6; i++) // fiz um for para poupar linhas de codigo ao imprimir os nomes
    {
        cout << nomes[i] << endl; // imprimo o nome contido na posicao i do meu vetor
    }
    system("pause");
    return 0;
}
