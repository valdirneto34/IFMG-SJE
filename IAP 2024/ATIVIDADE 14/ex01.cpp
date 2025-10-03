/*
1. Escreva um programa que cria duas matrizes com alocação estática e com valores pré-definidos,
realize a subtração de uma matriz pela outra e mostre o resultado.
*/

#include <iostream>

using namespace std;

int main()
{
    int matriz1[2][2] = {{9, 3}, {15, 10}};
    int matriz2[2][2] = {{5, 6}, {7, 8}};
    int matrizesres[2][2];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            matrizesres[i][j] = matriz1[i][j] - matriz2[i][j];
        }
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << matrizesres[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
