#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "portuguese");
    int matriz[6][6], somaelemen = 0;
    cout("Preencha a matriz:\n");
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            cout("Linha %d e coluna %d: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
    cout("\n\nMatriz inserida:\n");
    for (int i = 0; i < 6; i++)
    {
        cout("\n");
        for (int j = 0; j < 6; j++)
        {
            cout("%4d", matriz[i][j]);
        }
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            somaelemen += matriz[i][j];
        }
    }
    cout("\n\nA soma dos elementos é: %d", somaelemen);

    return 0;
}