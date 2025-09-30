#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#define InicioArranjo 1
#define MaxTam 10
typedef int Apontador;

typedef struct
{
    int numero;
} TipoItem;

typedef struct
{
    TipoItem Item[MaxTam];
    Apontador Primeiro;
    Apontador Ultimo;
} TipoLista;

TipoLista Lista;
TipoItem x;
Apontador pos;

void FLVazia(TipoLista *Lista)
{
    Lista->Primeiro = InicioArranjo;
    Lista->Ultimo = Lista->Primeiro;
}

void Insere(TipoItem *x, TipoLista *Lista)
{
    if (Lista->Ultimo > MaxTam)
        cout("\nA Lista está cheia\n");
    else
    {
        Lista->Item[Lista->Ultimo - 1] = *x;
        Lista->Ultimo++;
    }
}

void OrdenaDec(TipoLista *Lista)
{
    TipoItem aux;
    for (int i = MaxTam - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (Lista->Item[j].numero < Lista->Item[j + 1].numero)
            {
                aux = Lista->Item[j];
                Lista->Item[j] = Lista->Item[j + 1];
                Lista->Item[j + 1] = aux;
            }
        }
    }
}

void Imprime(TipoLista *Lista)
{
    cout("\nLista em ordem decrescente:\n");
    for (int i = Lista->Primeiro - 1; i < Lista->Ultimo - 1; i++)
        cout("%d  ", Lista->Item[i].numero);
    cout("\n");
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    FLVazia(&Lista);
    cout("\nInsira %d números\n\n", MaxTam);
    do
    {
        cout("Insira o %dº número: ", Lista.Ultimo);
        scanf("%d", &x);
        Insere(&x, &Lista);

    } while (Lista.Ultimo <= MaxTam);
    OrdenaDec(&Lista);
    Imprime(&Lista);

    return 0;
}
