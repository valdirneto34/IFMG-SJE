#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "portuguese");
    int matriz[5][5], somadiagonal = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout("Insira o valor para a linha %d e a coluna %d: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
    for (int i = 0; i < 5; i++)
    {
        somadiagonal += matriz[i][i];
    }
    cout("\nO resultado da soma é %d.", somadiagonal);
    return 0;
}
