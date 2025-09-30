#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#define InicioArranjo 1
#define MaxTam 10
typedef int Apontador;

typedef struct
{
    int notas;
} TipoItem;

typedef struct
{
    TipoItem Item[MaxTam];
    Apontador Primeiro;
    Apontador Ultimo;
    int qtdeValores, ValAcimaMedia;
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
    {
        cout("\nA Lista está cheia\n");
        x->notas = -1;
        return;
    }
    Lista->Item[Lista->Ultimo - 1] = *x;
    Lista->Ultimo++;
}

void Calcula(TipoLista *Lista)
{
    Lista->Media = 0;
    Lista->qtdeValores = 0;
    Lista->ValAcimaMedia = 0;
    cout("\n");
    for (int i = Lista->Primeiro - 1; i <= Lista->Ultimo - 2; i++)
    {
        Lista->Media += Lista->Item[i].notas;
        Lista->qtdeValores++;
    }
    Lista->Media /= Lista->Ultimo - 1;
    for (int i = Lista->Primeiro - 1; i <= Lista->Ultimo - 2; i++)
        if (Lista->Item[i].notas > Lista->Media)
            Lista->ValAcimaMedia++;
}

void Imprime(TipoLista *Lista)
{
    cout("Quantidade de valores lidos: %d\n", Lista->qtdeValores);
    cout("Valores na ordem que foram informados:\n");
    for (int i = Lista->Primeiro - 1; i <= Lista->Ultimo - 2; i++)
    {
        cout("%d  ", Lista->Item[i].notas);
    }
    cout("\nValores na ordem inversa:\n");
    for (int i = Lista->Ultimo - 2; i >= Lista->Primeiro - 1; i--)
    {
        cout("%d\n", Lista->Item[i].notas);
    }
    cout("Média dos valores: %.2f\n", Lista->Media);
    cout("Quantidade de valores acima da média: %d\n", Lista->ValAcimaMedia);
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    FLVazia(&Lista);
    system("cls");
    do
    {
        cout("Insira o %dº número: ", Lista.Ultimo);
        scanf("%d", &x.notas);
        if (x.notas == -1)
            break;
        Insere(&x, &Lista);
    } while (x.notas != -1);
    Calcula(&Lista);
    Imprime(&Lista);

    return 0;
}
