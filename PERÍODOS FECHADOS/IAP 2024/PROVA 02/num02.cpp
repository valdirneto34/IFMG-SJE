#include <iostream>
using namespace std;
int main()
{
    int vetor[11] = {9, 14, 14, 4, 10, 1, 1, 3, 0, 0, 13};
    int inteiro, cont = 0;
    cout << "Digite o inteiro: ";
    cin >> inteiro;
    for (int i = 0; i < 11; i++)
    {
        if (vetor[i] == inteiro)
        {
            cont++;
        }
    }
    cout << "O numero " << inteiro << " aparece ";
    cout << cont << " vezes no vetor." << endl;
    return 0;
}