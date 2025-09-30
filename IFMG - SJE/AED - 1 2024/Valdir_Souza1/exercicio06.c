#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "portuguese");
    int matriz[8][8], somaelementos = 0;
    cout("\nInsira a matriz:\n");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout("Linha %d e a coluna %d: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = i + 1; j < 8; j++)
        {
            somaelementos += matriz[i][j];
        }
    }
    cout("\n\nA soma dos elementos acima da diagonal principal é: %d",somaelementos);
    return 0;
}