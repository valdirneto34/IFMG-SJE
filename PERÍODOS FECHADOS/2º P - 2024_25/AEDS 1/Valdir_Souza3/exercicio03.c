#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *k, aux;
    k = malloc(sizeof(int) * 6);
    printf("ENTRADA:\n");
    for (int i = 0; i < 6; i++)
    {
        scanf("%d", &k[i]);
    }
    for (int i = 0; i < 6; i += 2)
    {
        aux = k[i];
        k[i] = k[i + 1];
        k[i + 1] = aux;
    }
    printf("\nSAIDA:\n");
    for (int i = 0; i < 6; i++)
    {
        printf("%d\n", k[i]);
    }
    free(k);

    return 0;
}