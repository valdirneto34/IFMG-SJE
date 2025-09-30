#include <stdio.h>
#include <stdlib.h>
#define InicioArranjo 1
#define MaxTam 3
typedef int Apontador;

typedef struct
{
    int codigo;
    int tipo;
} TipoItem;

typedef struct
{
    TipoItem Item[MaxTam];
    Apontador Inicio;
    Apontador Fim;

} TipoLista;

TipoLista Lista;
TipoItem x;
Apontador pos;

void IniciaLista(TipoLista *Lista)
{
    Lista->Inicio = InicioArranjo;
    Lista->Fim = MaxTam - 1;
}

int Vazia(TipoLista *Lista)
{
    return (Lista->Inicio == Lista->Fim);
}

void Imprime(TipoLista *Lista)
{
    printf("\n");
    for (int i = Lista->Inicio - 1; i <= Lista->Fim; i++)
        printf("Codigo: %d  -  Tipo: %d\n\n", Lista->Item[i].codigo, Lista->Item[i].tipo);
    printf("\n");
}

void Insere(TipoLista *Lista, TipoItem x, Apontador pos)
{
    Lista->Item[pos - 1] = x;
}

int main()
{
    IniciaLista(&Lista);
    int opcao;
    do
    {
        printf("\n\nMENU\n\n");
        printf("0 - Sair\n");
        printf("1 - Inserir cliente\n");
        printf("2 - Imprimir lista\n");
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
            printf("Digite o codigo: ");
            scanf("%d", &x.codigo);
            printf("Digite o tipo de casa(1-pequena, 2-media, 3-grande): ");
            scanf("%d", &x.tipo);
            printf("Digite a posicao: ");
            scanf("%d", &pos);
            Insere(&Lista, x, pos);
            break;
        }
        case 2:
        {
            Imprime(&Lista);
            break;
        }
        default:
        {
            printf("\nOPCAO INVALIDA\n");
            break;
        }
        }
    } while (opcao != 0);

    return 0;
}