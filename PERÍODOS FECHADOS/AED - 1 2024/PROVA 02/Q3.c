#include <stdio.h>
#include <stdlib.h>
#define MaxTam 4
typedef struct
{
    int elemento;
} TipoItem;

typedef struct
{
    TipoItem Item[MaxTam];
    int Topo;

} TipoPilha;

TipoPilha Pilha;
TipoItem x;

void FPVazia(TipoPilha *Pilha)
{
    Pilha->Topo = 0;
}

int Vazia(TipoPilha *Pilha)
{
    return (Pilha->Topo == 0);
}

void Insere(TipoPilha *Pilha, TipoItem x)
{
    if (Pilha->Topo >= MaxTam)
    {
        printf("\nERRO: Pilha esta cheia\n");
    }
    else
    {
        Pilha->Item[Pilha->Topo] = x;
        Pilha->Topo++;
    }
}

void ImprimeFundoTopo(TipoPilha *Pilha)
{
    if (Vazia(Pilha))
    {
        printf("\nERRO: Pilha esta vazia\n");
    }
    else
    {
        printf("\n");
        for (int i = 0; i < Pilha->Topo; i++)
        {
            printf("%d   ", Pilha->Item[i].elemento);
        }
    }
}

void CalculaMedia(TipoPilha *Pilha)
{
    float aux = 0;
    int cont = 0;
    if (Vazia(Pilha))
    {
        printf("\nERRO: Pilha esta vazia\n");
    }
    else
    {

        for (int i = 0; i < Pilha->Topo; i++)
        {
            aux += Pilha->Item[i].elemento;
            cont++;
        }
        aux /= cont;
        printf("\nA media aritmetica e: %.2f\n", aux);
    }
}

int main()
{
    FPVazia(&Pilha);
    int opcao;
    do
    {
        printf("\n\nMENU\n\n");
        printf("0 - Sair\n");
        printf("1 - Inserir valor na Pilha\n");
        printf("2 - Imprimir Pilha\n");
        printf("3 - Calcular Media\n");
        printf("Sua escolha: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 0:
        {
            printf("\nPROGRAMA ENCERRADO\n");
            break;
        }
        case 1:
        {
            printf("Digite o valor: ");
            scanf("%d", &x.elemento);
            Insere(&Pilha, x);
            break;
        }
        case 2:
        {
            ImprimeFundoTopo(&Pilha);
            break;
        }
        case 3:
        {
            CalculaMedia(&Pilha);
            break;
        }
        default:
        {
            printf("\nOPCAO INVALIDA\n");
            break;
        }
        }
        _getch();
        system("cls");
    } while (opcao != 0);

    return 0;
}