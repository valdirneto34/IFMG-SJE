#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct
{
    int cod;
    int idade;
} TipoItem;
typedef struct TipoCelula *TipoApontador;
typedef struct TipoCelula
{
    TipoItem Item;
    TipoApontador Prox;
} TipoCelula;
typedef struct
{
    TipoApontador Frente, Tras;
    int Tam;
} TipoFila;

TipoFila Fila;
TipoItem x;

void FFVazia(TipoFila *Fila)
{
    Fila->Frente = (TipoApontador)malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Frente;
    Fila->Frente->Prox = NULL;
    Fila->Tam = 0;
}

int Vazia(TipoFila Fila)
{
    return (Fila.Frente == Fila.Tras);
}

void Enfileira(TipoItem x, TipoFila *Fila)
{
    TipoApontador aux;
    Fila->Tras->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Tras->Prox;
    Fila->Tras->Item = x;
    Fila->Tras->Prox = NULL;
}

void Imprime(TipoFila Fila)
{
    if (Vazia(Fila))
        cout("ERRO: A fila está vazia!\n");
    else
    {
        TipoApontador aux = Fila.Frente->Prox;
        while (aux != NULL)
        {
            cout("Codigo: %d\n", aux->Item.cod);
            cout("Idade: %d\n\n", aux->Item.idade);
            aux = aux->Prox;
        }
    }
}

void Desenfileira(TipoFila *Fila, TipoItem *x)
{
    TipoApontador q;
    if (Vazia(*Fila))
        cout("ERRO: A fila está vazia!\n");
    else
    {
        q = Fila->Frente;
        Fila->Frente = Fila->Frente->Prox;
        *x = Fila->Frente->Item;
        free(q);
    }
}

void Procurar(TipoFila Fila, TipoItem *x)
{
    if (Vazia(Fila))
        cout("\nERRO: Lista está vazia!\n");
    else
    {
        int encontrou = 0;
        TipoApontador aux = Fila.Frente->Prox;
        while (aux != NULL)
        {
            if (aux->Item.cod == x->cod)
            {
                encontrou = 1;
                break;
            }
            aux = aux->Prox;
        }
        if (encontrou)
            cout("Elemento encontrado!\n");
        else
            cout("Elemento não encontrado!\n");
    }
}

void ContarIdadesPares(TipoFila Fila)
{
    if (Vazia(Fila))
        cout("\nERRO: Lista está vazia!\n");
    else
    {
        int cont = 0;
        TipoApontador aux = Fila.Frente->Prox;
        while (aux != NULL)
        {
            if (aux->Item.idade % 2 == 0)
                cont++;
            aux = aux->Prox;
        }
        cout("Existem %d pessoas com idades pares.\n", cont);
    }
}

void ContarIdadesImpares(TipoFila Fila)
{
    if (Vazia(Fila))
        cout("\nERRO: Lista está vazia!\n");
    else
    {
        int cont = 0;
        TipoApontador aux = Fila.Frente->Prox;
        while (aux != NULL)
        {
            if (aux->Item.idade % 2 != 0)
                cont++;
            aux = aux->Prox;
        }
        cout("Existem %d pessoas com idades ímpares.\n", cont);
    }
}

int main()
{
    FFVazia(&Fila);
    SetConsoleOutputCP(CP_UTF8);
    int opcao, resposta;

    do
    {
        cout("\n\nMENU\n\n");
        cout("Digite a opção desejada:\n");
        cout("0 - Sair\n");
        cout("1 - Esvaziar a fila\n");
        cout("2 - Verificar se a fila está pilha\n");
        cout("3 - Enfileirar elemento na fila\n");
        cout("4 - Imprimir os elementos da fila\n");
        cout("5 - Desenfileirar elemento da fila\n");
        cout("6 - Procurar elemento pelo código\n");
        cout("7 - Contar idades pares na fila\n");
        cout("8 - Contar idades ímpares na fila\n");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
        {
            cout("PROGRAMA ENCERRADO\n");
            break;
        }
        case 1:
        {
            FFVazia(&Fila);
            break;
        }
        case 2:
        {
            resposta = Vazia(Fila);
            if (resposta == 1)
            {
                cout("A fila está vazia!\n");
            }
            else
            {
                cout("A fila não está vazia!\n");
            }
            break;
        }
        case 3:
        {
            cout("Digite o código\n");
            scanf("%d", &x.cod);
            cout("Digite a idade\n");
            scanf("%d", &x.idade);
            Enfileira(x, &Fila);
            break;
        }
        case 4:
        {
            Imprime(Fila);
            break;
        }
        case 5:
        {
            Desenfileira(&Fila, &x);
            break;
        }
        case 6:
        {
            cout("Digite o código do elemento\n");
            scanf("%d", &x.cod);
            Procurar(Fila, &x);
            break;
        }
        case 7:
        {
            ContarIdadesPares(Fila);
            break;
        }
        case 8:
        {
            ContarIdadesImpares(Fila);
            break;
        }
        default:
        {
            cout("OPÇÃO INVALIDA!");
            break;
        }
        }
        _getch();
        system("cls");

    } while (opcao != 0);

    return 0;
}
