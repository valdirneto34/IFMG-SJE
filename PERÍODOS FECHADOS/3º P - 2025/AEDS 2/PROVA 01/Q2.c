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

void RemoveNnumeros(TipoLista *Lista, TipoItem x)
{
    if (Vazia(*Lista))
        printf("ERRO: A lista esta vazia!\n");
    else
    {
        if (x.valor > Lista->Tam)
        {
            FLVazia(Lista);
            printf("\nA nova lista esta vazia!\n");
        }
        else
        {
            int cont = 2;
            TipoApontador aux2, aux = Lista->Primeiro->Prox;
            while (aux->Prox != NULL && cont <= x.valor)
            {
                aux2 = aux;
                aux = aux->Prox;
                free(aux2);
                cont++;
            }
            Lista->Primeiro = aux;
            Lista->Tam -= x.valor;
            printf("\nA nova lista e:\n\n");
            Imprimir(Lista);
        }
    }
}

int main()
{
    FLVazia(&Lista);
    int opcao, resposta;
    do
    {
        printf("\n\nMENU\n\n");
        printf("0 - Sair\n");
        printf("1 - Esvaziar a lista\n");
        printf("2 - Verificar se a lista esta vazia\n");
        printf("3 - Inserir elemento na lista\n");
        printf("4 - Imprimir os elementos da lista\n");
        printf("5 - Remover N elementos da lista\n");
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
            printf("Digite a quantidade de valores que deseja remover: ");
            scanf("%d", &x.valor);
            RemoveNnumeros(&Lista, x);
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