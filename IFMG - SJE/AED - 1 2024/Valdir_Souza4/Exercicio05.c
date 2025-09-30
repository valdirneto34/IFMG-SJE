#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#define InicioArranjo 1
#define MaxTam 5
typedef int Apontador;

typedef struct
{
    int resp;
} TipoItem;

typedef struct
{
    TipoItem Item[MaxTam];
    Apontador Primeiro;
    Apontador Ultimo;
    int Classificaco;
} TipoLista;

TipoLista Lista;
TipoItem x;
Apontador pos;

void FLVazia(TipoLista *Lista)
{
    Lista->Primeiro = InicioArranjo;
    Lista->Ultimo = Lista->Primeiro;
}

void Imprime(TipoLista *Lista)
{
    Lista->Classificaco = 0;
    cout("\n");
    for (int i = Lista->Primeiro - 1; i <= Lista->Ultimo - 2; i++)
    {
        if (Lista->Item[i].resp == 1)
            Lista->Classificaco++;
    }
    if (Lista->Classificaco == 2)
        cout("Suspeita\n");
    else if (Lista->Classificaco >= 3 && Lista->Classificaco <= 4)
        cout("Cúmplice\n");
    else if (Lista->Classificaco == 5)
        cout("Assassino\n");
    else
        cout("Inocente\n");
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    FLVazia(&Lista);
    system("cls");
    cout("\nRESPONDA COM 1 PARA SIM OU 0 PARA NÃO\n\n");

    cout("Telefonou para a vítima?\n");
    scanf("%d", &Lista.Item[Lista.Ultimo - 1].resp);
    Lista.Ultimo++;

    cout("Esteve no local do crime?\n");
    scanf("%d", &Lista.Item[Lista.Ultimo - 1].resp);
    Lista.Ultimo++;

    cout("Mora perto da vítima?\n");
    scanf("%d", &Lista.Item[Lista.Ultimo - 1].resp);
    Lista.Ultimo++;

    cout("Devia para a vítima?\n");
    scanf("%d", &Lista.Item[Lista.Ultimo - 1].resp);
    Lista.Ultimo++;

    cout("Já trabalhou com a vítima?\n");
    scanf("%d", &Lista.Item[Lista.Ultimo - 1].resp);
    Lista.Ultimo++;

    Imprime(&Lista);

    return 0;
}
