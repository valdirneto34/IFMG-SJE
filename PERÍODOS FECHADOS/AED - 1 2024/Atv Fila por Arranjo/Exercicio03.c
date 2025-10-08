#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MaxTam 13
#define InicioArranjo 1
typedef int Apontador;

typedef struct
{
    int temp;
} TipoItem;

typedef struct
{
    TipoItem Item[MaxTam];
    Apontador Frente;
    Apontador Tras;
} TipoFila;

TipoFila Fila;
TipoItem x;
int tamanho = 0;

void FFVazia(TipoFila *Fila)
{
    Fila->Frente = InicioArranjo;
    Fila->Tras = Fila->Frente;
    tamanho = 0;
}

int Vazia(TipoFila Fila)
{
    return (Fila.Frente == Fila.Tras);
}

void Enfileira(TipoItem x, TipoFila *Fila)
{
    if (Fila->Tras % MaxTam + 1 == Fila->Frente)
        printf("\nA Fila está cheia\n");
    else
    {
        Fila->Item[Fila->Tras - 1] = x;
        Fila->Tras = Fila->Tras % MaxTam + 1;
        tamanho++;
    }
}

float CalculaMedia(TipoFila *Fila)
{
    float media = 0;
    int cont = 0;
    for (int i = Fila->Frente - 1; i <= Fila->Tras - 2; i++)
    {
        media += Fila->Item[i].temp;
        cont++;
    }
    return (media / cont);
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int cont = 0;
    float media = 0;
    FFVazia(&Fila);
    for (int i = 1; i <= 5; i++)
    {
        printf("Digite a temperatura do %dº mês:\n", i);
        scanf("%d", &x.temp);
        Enfileira(x, &Fila);
    }
    media = CalculaMedia(&Fila);
    printf("\n\n   Meses acima da média:\n\n");
    for (int i = Fila.Frente - 1; i <= Fila.Tras - 2; i++)
    {
        cont++;
        if (Fila.Item[i].temp > media)
            printf("Mês %d: %d\n\n", cont, Fila.Item[i].temp);
    }

    return 0;
}
