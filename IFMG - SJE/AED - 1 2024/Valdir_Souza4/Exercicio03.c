#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#define InicioArranjo 1
#define MaxTam 5
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
    Apontador Menor, Maior;
    float Media;
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

void Imprime(TipoLista *Lista)
{
    Lista->Maior = Lista->Primeiro - 1;
    Lista->Menor = Lista->Primeiro - 1;
    Lista->Media = 0;
    cout("\nNúmeros: ");
    for (int i = Lista->Primeiro - 1; i <= Lista->Ultimo - 2; i++)
    {
        cout("%d  ", Lista->Item[i].numero);
        Lista->Media += Lista->Item[i].numero;
        if (Lista->Item[i].numero > Lista->Item[Lista->Maior].numero)
            Lista->Maior = i;
        if (Lista->Item[i].numero < Lista->Item[Lista->Menor].numero)
            Lista->Menor = i;
    }
    Lista->Media /= Lista->Ultimo - 1;
    cout("\nMaior número: %d\n", Lista->Item[Lista->Maior].numero);
    cout("Menor número: %d\n", Lista->Item[Lista->Menor].numero);
    cout("Média dos números: %f\n", Lista->Media);
}

int main()
{
    int opcao, resposta;
    SetConsoleOutputCP(CP_UTF8);
    FLVazia(&Lista);
    do
    {
        cout("Insira o %dº número: ", Lista.Ultimo);
        scanf("%d", &x);
        Insere(&x, &Lista);
    } while (Lista.Ultimo <= MaxTam);
    Imprime(&Lista);

    return 0;
}
