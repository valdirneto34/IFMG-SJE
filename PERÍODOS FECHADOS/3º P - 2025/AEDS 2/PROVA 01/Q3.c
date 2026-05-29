#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int valor
} TipoItem;
typedef struct TipoCelula *TipoApontador;
typedef struct TipoCelula
{
    TipoItem Item;
    TipoApontador Prox;
} TipoCelula;

typedef struct
{
    TipoApontador Primeiro, Ultimo;
    int Tam;
} TipoLista;

TipoItem x;
TipoLista Lista;
TipoLista Lista2;
TipoLista Lista3;

void FLVazia(TipoLista *Lista)
{
    Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Ultimo->Prox = NULL;
    Lista->Tam = 0;
}

int Vazia(TipoLista Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoLista *Lista, TipoItem x)
{
    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = x;
    Lista->Ultimo->Prox = NULL;
    Lista->Tam++;
}

void Imprimir(TipoLista *Lista)
{
    if (Vazia(*Lista))
        printf("ERRO: A lista esta vazia!\n");
    else
    {
        TipoApontador aux = Lista->Primeiro->Prox;
        while (aux != NULL)
        {
            printf("Valor: %d\n", aux->Item.valor);
            aux = aux->Prox;
        }
    }
}

void DivideListas(TipoLista *Lista, TipoLista *Lista2, TipoLista *Lista3, TipoItem *x)
{
    if (Vazia(*Lista))
        printf("ERRO: A lista esta vazia!\n");
    else
    {
        FLVazia(Lista2);
        FLVazia(Lista3);
        TipoApontador aux = Lista->Primeiro->Prox;
        while (aux != NULL)
        {
            Insere(Lista2, aux->Item);
            if (aux->Item.valor == x->valor)
            {
                aux = aux->Prox;
                break;
            }
            aux = aux->Prox;
        }
        while (aux != NULL)
        {
            Insere(Lista3, aux->Item);
            aux = aux->Prox;
        }
        printf("\nLista da primeira parte:\n");
        Imprimir(Lista2);
        printf("\n\nLista da segunda parte:\n");
        Imprimir(Lista3);
        printf("\nE possivel dividir a lista principal novamente.\n");
        printf("Para isso, as duas listas paralelas sao\n esvaziadas a partir da segunda divisao.\n");
    }
}

int main()
{
    FLVazia(&Lista);
    FLVazia(&Lista2);
    FLVazia(&Lista3);
    int opcao, resposta;
    do
    {
        printf("\n\nMENU\n\n");
        printf("0 - Sair\n");
        printf("1 - Esvaziar a lista\n");
        printf("2 - Verificar se a lista esta vazia\n");
        printf("3 - Inserir elemento na lista\n");
        printf("4 - Imprimir os elementos da lista\n");
        printf("5 - Dividir a lista em outras duas\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 0:
        {
            printf("PROGRAMA ENCERRADO!\n");
            break;
        }
        case 1:
        {
            FLVazia(&Lista);
            break;
        }
        case 2:
        {
            resposta = Vazia(Lista);
            if (resposta == 1)
                printf("A lista esta vazia!\n");
            else
                printf("A lista nao esta vazia!\n");
            break;
        }
        case 3:
        {
            printf("Digite o valor: ");
            scanf("%d", &x.valor);
            Insere(&Lista, x);
            break;
        }
        case 4:
        {
            Imprimir(&Lista);
            break;
        }
        case 5:
        {
            printf("Digite a partir de qual valor deseja dividir a lista original: ");
            scanf("%d", &x.valor);
            DivideListas(&Lista, &Lista2, &Lista3, &x);
            break;
        }
        default:
        {
            printf("OPCAO INVALIDA!\n");
            break;
        }
        }
        _getch();
        system("cls");
    } while (opcao != 0);

    return 0;
}