#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "portuguese");
    int matriz[8][8], a = 0;

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
        }
    }
    printf("\nMatriz gerada:\n");
    for (int i = 0; i < 8; i++)
    {
        printf("\n");
        for (int j = 0; j < 8; j++)
        {
            printf("%5d", matriz[i][j]);
        }
    }
    return 0;
}
