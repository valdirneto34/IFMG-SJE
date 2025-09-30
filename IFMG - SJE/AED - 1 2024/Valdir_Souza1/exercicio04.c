#include <stdio.h>
#include <locale.h>

int main()
{
    int matrizA[3][5], matrizB[3][5], matrizC[3][5];
    cout("Preencha a matriz A:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout("Linha %d e coluna %d: ", i, j);
            scanf("%d", &matrizA[i][j]);
        }
    }
    cout("\nPreencha a matriz B:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout("Linha %d e coluna %d: ", i, j);
            scanf("%d", &matrizB[i][j]);
            matrizC[i][j] = matrizA[i][j] + matrizB[i][j];
        }
    }
    cout("\n\nMatriz A:\n");
    for (int i = 0; i < 3; i++)
    {
        cout("\n");
        for (int j = 0; j < 5; j++)
        {
            cout("%4d", matrizA[i][j]);
        }
    }
    cout("\n\nMatriz B:\n");
    for (int i = 0; i < 3; i++)
    {
        cout("\n");
        for (int j = 0; j < 5; j++)
        {
            cout("%4d", matrizB[i][j]);
        }
    }
    cout("\n\nMatriz que foi gerada da soma das duas inseridas:\n");
    for (int i = 0; i < 3; i++)
    {
        cout("\n");
        for (int j = 0; j < 5; j++)
        {
            cout("%4d", matrizC[i][j]);
        }
    }

    return 0;
}