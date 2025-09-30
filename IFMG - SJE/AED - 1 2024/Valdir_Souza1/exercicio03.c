#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "portuguese");
    int matriz[8][8], a = 0;
    int diagonalprin = 0, diagonalsecun = 0, multplidiagonais = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i + j == 8)
            {
                a = (i * i) + (j * j) + 2;
            }
            else if (i + j > 8)
            {
                a = j + 4;
            }
            else if (i + j < 8)
            {
                a = (3 * i) + j;
            }
            matriz[i][j] = a;
            if (i == j)
            {
                diagonalprin += matriz[i][j];
            }
        }
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            if (i + j == 7)
            {
                diagonalsecun += matriz[i][j];
            }
        }
    }
    multplidiagonais = diagonalprin * diagonalsecun;
    cout("Diagonal Principal: %d\n", diagonalprin);
    cout("Diagonal Secundária: %d\n", diagonalsecun);
    cout("Multiplicação: %d\n", multplidiagonais);

    return 0;
}