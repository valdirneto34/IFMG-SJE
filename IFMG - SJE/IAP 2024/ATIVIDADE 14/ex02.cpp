/*2. Escreva um programa que cria duas matrizes com alocação estática e com valores lidos do usuário,
calcule uma matriz resultante com a média dos valores das matrizes lidas e mostre o resultado.
*/

#include <iostream>

using namespace std;

int main()
{
    float matriz1[2][2], matriz2[2][2], matrizesres[2][2];
    cout << "Lendo primeira matriz:" << endl;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cin >> matriz1[i][j];
        }
    }
    cout << "Lendo segunda matriz:" << endl;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cin >> matriz2[i][j];
        }
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            matrizesres[i][j] = (matriz1[i][j] + matriz2[i][j]) / 2;
        }
    }
    cout << "Matriz resultante:" << endl;
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
