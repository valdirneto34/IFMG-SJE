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

void Remove(TipoLista *Lista, TipoItem x)
{
    if (Vazia(*Lista))
        printf("ERRO: A lista esta vazia!\n");
    else
    {
        int removido = 0;
        TipoApontador aux2, aux = Lista->Primeiro->Prox;
        if (aux->Prox == NULL)
        {
            if (aux->Item.valor == x.valor)
            {
                Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
                Lista->Ultimo = Lista->Primeiro;
                Lista->Ultimo->Prox = NULL;
                Lista->Tam = 0;
                removido = 1;
            }
        }
        else
        {
            while (aux->Prox != NULL)
            {
                if (aux->Item.valor == x.valor)
                {
                    free(Lista->Primeiro);
                    Lista->Primeiro = aux;
                    Lista->Tam--;
                    removido = 1;
                    break;
                }
                aux2 = aux;
                aux = aux->Prox;
                if (aux->Item.valor == x.valor && aux->Prox != NULL)
                {
                    aux2->Prox = aux->Prox;
                    free(aux);
                    Lista->Tam--;
                    removido = 1;
                    break;
                }
                else if (aux->Item.valor == x.valor && aux->Prox == NULL)
                {
                    Lista->Ultimo = aux2;
                    Lista->Ultimo->Prox = NULL;
                    free(aux);
                    Lista->Tam--;
                    removido = 1;
                    break;
                }
            }
        }
        if (removido)
            printf("\nElemento %d removido com sucesso!\n", x.valor);
        else
            printf("\nElemento %d nao foi encontrado!\n", x.valor);
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
        printf("5 - Remover um elemento da lista\n");
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
            printf("Digite o valor que deseja remover: ");
            scanf("%d", &x.valor);
            Remove(&Lista, x);
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