#include <stdio.h>
#include <locale.h>

int main()
{
    int matrizA[3][5], matrizB[3][5], matrizC[3][5];
    printf("Preencha a matriz A:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("Linha %d e coluna %d: ", i, j);
            scanf("%d", &matrizA[i][j]);
        }
    }
    printf("\nPreencha a matriz B:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("Linha %d e coluna %d: ", i, j);
            scanf("%d", &matrizB[i][j]);
            matrizC[i][j] = matrizA[i][j] + matrizB[i][j];
        }
    }
    printf("\n\nMatriz A:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("\n");
        for (int j = 0; j < 5; j++)
        {
            printf("%4d", matrizA[i][j]);
        }
    }
    printf("\n\nMatriz B:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("\n");
        for (int j = 0; j < 5; j++)
        {
            printf("%4d", matrizB[i][j]);
        }
    }
    printf("\n\nMatriz que foi gerada da soma das duas inseridas:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("\n");
        for (int j = 0; j < 5; j++)
        {
            printf("%4d", matrizC[i][j]);
        }
    }

    return 0;
}