#include <stdio.h>
#include <stdlib.h>

int main()
{
    int vetor[3], matriz[3][3];
    cout("VETOR\n");
    for (int i = 0; i < 3; i++)
    {
        scanf("%d", &vetor[i]);
    }
    cout("\nMATRIZ\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &matriz[i][j]);
        }
    }
    cout("\nSAIDA");
    for (int i = 0; i < 3; i++)
    {
        cout("\n");
        for (int j = 0; j < 3; j++)
        {
            cout("%d  ", matriz[i][j] * vetor[j]);
        }
    }

    return 0;
}