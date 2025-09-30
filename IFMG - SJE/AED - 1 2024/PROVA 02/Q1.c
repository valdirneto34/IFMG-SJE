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
    cout("\n");
    for (int i = Lista->Inicio - 1; i <= Lista->Fim; i++)
        cout("Codigo: %d  -  Tipo: %d\n\n", Lista->Item[i].codigo, Lista->Item[i].tipo);
    cout("\n");
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
        cout("\n\nMENU\n\n");
        cout("0 - Sair\n");
        cout("1 - Inserir cliente\n");
        cout("2 - Imprimir lista\n");
        cout("Sua escolha: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 0:
        {
            cout("\nPROGRAMA ENCERRADO\n");
            break;
        }
        case 1:
        {
            cout("Digite o codigo: ");
            scanf("%d", &x.codigo);
            cout("Digite o tipo de casa(1-pequena, 2-media, 3-grande): ");
            scanf("%d", &x.tipo);
            cout("Digite a posicao: ");
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
            cout("\nOPCAO INVALIDA\n");
            break;
        }
        }
    } while (opcao != 0);

    return 0;
}