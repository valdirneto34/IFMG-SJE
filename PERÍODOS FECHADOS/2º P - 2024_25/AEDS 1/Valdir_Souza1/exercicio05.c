#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "portuguese");
    int matriz[6][6], somaelemen = 0;
    printf("Preencha a matriz:\n");
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            printf("Linha %d e coluna %d: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
    printf("\n\nMatriz inserida:\n");
    for (int i = 0; i < 6; i++)
    {
        printf("\n");
        for (int j = 0; j < 6; j++)
        {
            printf("%4d", matriz[i][j]);
        }
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            somaelemen += matriz[i][j];
        }
    }
    printf("\n\nA soma dos elementos é: %d", somaelemen);

    return 0;
}