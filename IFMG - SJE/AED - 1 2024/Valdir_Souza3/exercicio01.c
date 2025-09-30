#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *nome;
    int tipo, diarias;
    float consumo = 0, totalgeral = 0, totaldiarias = 0, subtotal = 0, taxadeservico = 0;
    nome = (char *)malloc(sizeof(char) + 1);
    printf("Digite o nome......: ");
    gets(nome);
    printf("Tipo do apartamento: ");
    scanf("%d", &tipo);
    printf("Diarias............: ");
    scanf("%d", &diarias);
    printf("Consumo interno....: R$");
    scanf("%f", &consumo);
    switch (tipo)
    {
    case 1:
        totaldiarias = diarias * 150;
        break;
    case 2:
        totaldiarias = diarias * 100;
        break;
    case 3:
        totaldiarias = diarias * 75;
        break;
    case 4:
        totaldiarias = diarias * 50;
        break;
    default:
        printf("Tipo de apartamento invalido!\n");
    }
    subtotal = totaldiarias + consumo;
    taxadeservico = subtotal * 10 / 100;
    totalgeral = subtotal + taxadeservico;
    printf("\nNome do hospede.........: %s\n", nome);
    printf("Tipo do apartamento.....: %d\n", tipo);
    printf("Numero de diarias.......: %d\n", diarias);
    printf("Valor unitario da diaria: R$%.2f\n", (totaldiarias / diarias));
    printf("Valor total das diarias.: R$%.2f\n", totaldiarias);
    printf("Valor do consumo interno: R$%.2f\n", consumo);
    printf("Subtotal................: R$%.2f\n", subtotal);
    printf("Valor da taxa de servico: R$%.2f\n", taxadeservico);
    printf("Total geral.............: R$%.2f\n", totalgeral);

    free(nome);

    return 0;
}