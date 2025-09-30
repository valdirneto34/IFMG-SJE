#include <stdio.h>
#include <stdlib.h>

int main()
{
    int vetor[3], matriz[3][3];
    printf("VETOR\n");
    for (int i = 0; i < 3; i++)
    {
        scanf("%d", &vetor[i]);
    }
    printf("\nMATRIZ\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &matriz[i][j]);
        }
    }
    printf("\nSAIDA");
    for (int i = 0; i < 3; i++)
    {
        printf("\n");
        for (int j = 0; j < 3; j++)
        {
            printf("%d  ", matriz[i][j] * vetor[j]);
        }
    }

    return 0;
}