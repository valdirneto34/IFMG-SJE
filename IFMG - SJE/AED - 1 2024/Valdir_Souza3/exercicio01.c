#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *nome;
    int tipo, diarias;
    float consumo = 0, totalgeral = 0, totaldiarias = 0, subtotal = 0, taxadeservico = 0;
    nome = (char *)malloc(sizeof(char) + 1);
    cout("Digite o nome......: ");
    gets(nome);
    cout("Tipo do apartamento: ");
    scanf("%d", &tipo);
    cout("Diarias............: ");
    scanf("%d", &diarias);
    cout("Consumo interno....: R$");
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
        cout("Tipo de apartamento invalido!\n");
    }
    subtotal = totaldiarias + consumo;
    taxadeservico = subtotal * 10 / 100;
    totalgeral = subtotal + taxadeservico;
    cout("\nNome do hospede.........: %s\n", nome);
    cout("Tipo do apartamento.....: %d\n", tipo);
    cout("Numero de diarias.......: %d\n", diarias);
    cout("Valor unitario da diaria: R$%.2f\n", (totaldiarias / diarias));
    cout("Valor total das diarias.: R$%.2f\n", totaldiarias);
    cout("Valor do consumo interno: R$%.2f\n", consumo);
    cout("Subtotal................: R$%.2f\n", subtotal);
    cout("Valor da taxa de servico: R$%.2f\n", taxadeservico);
    cout("Total geral.............: R$%.2f\n", totalgeral);

    free(nome);

    return 0;
}