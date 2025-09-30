#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MaxTam 6
typedef int Apontador;
typedef struct
{
    int valor;
} TipoItem;

typedef struct
{
    TipoItem Item[MaxTam];
    Apontador Topo;
} TipoPilha;

TipoPilha Pilha_Pares;
TipoPilha Pilha_Impares;
TipoItem x;

void FPVazia(TipoPilha *Pilha)
{
    Pilha->Topo = 0;
}

void Empilhar(TipoPilha *Pilha, TipoItem *x)
{
    if (Pilha->Topo >= MaxTam)
    {
        if (Pilha->Item[Pilha->Topo - 1].valor % 2 == 0)
            cout("\nERRO: Pilha dos Pares está cheia\n");
        else
            cout("\nERRO: Pilha dos Ímpares está cheia\n");
    }
    else
    {
        Pilha->Item[Pilha->Topo] = *x;
        Pilha->Topo++;
    }
}

void ImprimeTopoFundo(TipoPilha Pilha)
{
    for (int i = Pilha.Topo - 1; i >= 0; i--)
    {
        cout("%d   ", Pilha.Item[i].valor);
    }
}

int main()
{
    char resp;
    SetConsoleOutputCP(CP_UTF8);
    FPVazia(&Pilha_Pares);
    FPVazia(&Pilha_Impares);
    for (int i = 0; i < 12; i++)
    {
        cout("\nDigite um número: ");
        scanf("%d", &x.valor);
        if (x.valor % 2 == 0)
        {
            Empilhar(&Pilha_Pares, &x);
        }
        else
        {
            Empilhar(&Pilha_Impares, &x);
        }
        cout("\nMais um número? [S/N]: ");
        scanf("%s", &resp);
        if (resp == 'N' || resp == 'n' || (Pilha_Pares.Topo >= MaxTam && Pilha_Impares.Topo >= MaxTam))
            break;
    }
    cout("\n\nPilha dos Pares:\n");
    ImprimeTopoFundo(Pilha_Pares);
    cout("\n\nPilha dos Impares:\n");
    ImprimeTopoFundo(Pilha_Impares);

    return 0;
}