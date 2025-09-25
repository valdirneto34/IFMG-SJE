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
    printf("\n");
    for (int i = Lista->Primeiro - 1; i <= Lista->Ultimo - 2; i++)
    {
        if (Lista->Item[i].resp == 1)
            Lista->Classificaco++;
    }
    if (Lista->Classificaco == 2)
        printf("Suspeita\n");
    else if (Lista->Classificaco >= 3 && Lista->Classificaco <= 4)
        printf("Cúmplice\n");
    else if (Lista->Classificaco == 5)
        printf("Assassino\n");
    else
        printf("Inocente\n");
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    FLVazia(&Lista);
    system("cls");
    printf("\nRESPONDA COM 1 PARA SIM OU 0 PARA NÃO\n\n");

    printf("Telefonou para a vítima?\n");
    scanf("%d", &Lista.Item[Lista.Ultimo - 1].resp);
    Lista.Ultimo++;

    printf("Esteve no local do crime?\n");
    scanf("%d", &Lista.Item[Lista.Ultimo - 1].resp);
    Lista.Ultimo++;

    printf("Mora perto da vítima?\n");
    scanf("%d", &Lista.Item[Lista.Ultimo - 1].resp);
    Lista.Ultimo++;

    printf("Devia para a vítima?\n");
    scanf("%d", &Lista.Item[Lista.Ultimo - 1].resp);
    Lista.Ultimo++;

    printf("Já trabalhou com a vítima?\n");
    scanf("%d", &Lista.Item[Lista.Ultimo - 1].resp);
    Lista.Ultimo++;

    Imprime(&Lista);

    return 0;
}
