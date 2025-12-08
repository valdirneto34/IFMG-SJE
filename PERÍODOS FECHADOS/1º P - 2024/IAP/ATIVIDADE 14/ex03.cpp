/*
3. Escreva um programa que cria uma matriz com alocação estática e 
com valores lidos do usuário e mostre a matriz transposta da matriz lida.
*/

#include <iostream>

using namespace std;

int main()
{
    int matriz[3][2];
    cout << "Lendo matriz:" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cin >> matriz[i][j];
        }
    }
    cout << "Matriz transposta:" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << matriz[j][i] << " ";
        }
        cout << endl;
    }
    return 0;
}
