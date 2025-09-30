#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int codigoProduto, tipoDeCompra;
    float valor;
} Transacao;

int main()
{
    Transacao compras[3];
    float totalAVista = 0, totalAPrazo = 0, totalDasCpmpras = 0;
    for (int i = 0; i < 3; i++)
    {
        scanf("%d", &compras[i].codigoProduto);
        scanf("%f", &compras[i].valor);
        scanf("%d", &compras[i].tipoDeCompra);
    }
    for (int i = 0; i < 3; i++)
    {
        if (compras[i].tipoDeCompra == 1)
            totalAVista += compras[i].valor;
        else if (compras[i].tipoDeCompra == 2)
            totalAPrazo += compras[i].valor;
    }
    totalDasCpmpras = totalAVista + totalAPrazo;
    cout("Valor total das compras A Vista..: R$%.2f\n", totalAVista);
    cout("Valor total das compras A Prazo..: R$%.2f\n", totalAPrazo);
    cout("Valor total das compras efetuadas: R$%.2f\n", totalDasCpmpras);
    system("pause");
    return 0;
}
