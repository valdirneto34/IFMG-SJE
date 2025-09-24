#include <stdio.h>
#include <stdlib.h>

void MultiplicaNum(int *v, int qtd, int mult)
{
    printf("Resultado:\n");
    for (int i = 0; i < qtd; i++)
    {
        v[i] = v[i] * mult;
        printf("%d  ", v[i]);
    }
}

int main()
{
    int qtd, vetor[5], multiplicador;
    printf("Insira um tamanho de vetor (max 5): ");
    scanf("%d", &qtd);
    for (int i = 0; i < qtd; i++)
    {
        scanf("%d", &vetor[i]);
    }
    printf("\nDigite o inteiro multiplicador: ");
    scanf("%d", &multiplicador);
    MultiplicaNum(&vetor, qtd, multiplicador);
    system("pause");
    return 0;
}
