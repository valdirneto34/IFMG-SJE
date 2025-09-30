#include <stdio.h>
#include <stdlib.h>

int main()
{
    int matriz[3][3], diagonalP = 0, diagonalS = 0, linha1 = 0, linha2 = 0, linha3 = 0, col1 = 0, col2 = 0, col3 = 0;
    cout("Insira a matriz:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &matriz[i][j]);
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == 0)
                linha1 += matriz[i][j];
            else if (i == 1)
                linha2 += matriz[i][j];
            else if (i == 2)
                linha3 += matriz[i][j];
            if (j == 0)
                col1 += matriz[i][j];
            else if (j == 1)
                col2 += matriz[i][j];
            else if (j == 2)
                col3 += matriz[i][j];
            if (i == j)
                diagonalP += matriz[i][j];
            if (i + j == 2)
                diagonalS += matriz[i][j];
        }
    }
    if (diagonalP == diagonalS)
    {
        if (linha1 == linha2 && linha2 == linha3)
            if (col1 == col2 && col2 == col3)
                cout("\n%d\n", linha1);
    }
    else
    {
        cout("-1\n");
    }
    system("pause");
    return 0;
}
