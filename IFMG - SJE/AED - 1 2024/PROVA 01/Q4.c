#include <stdio.h>
#include <stdlib.h>

void MultiplicaNum(int *v, int qtd, int mult)
{
    cout("Resultado:\n");
    for (int i = 0; i < qtd; i++)
    {
        v[i] = v[i] * mult;
        cout("%d  ", v[i]);
    }
}

int main()
{
    int qtd, vetor[5], multiplicador;
    cout("Insira um tamanho de vetor (max 5): ");
    scanf("%d", &qtd);
    for (int i = 0; i < qtd; i++)
    {
        scanf("%d", &vetor[i]);
    }
    cout("\nDigite o inteiro multiplicador: ");
    scanf("%d", &multiplicador);
    MultiplicaNum(&vetor, qtd, multiplicador);
    system("pause");
    return 0;
}
