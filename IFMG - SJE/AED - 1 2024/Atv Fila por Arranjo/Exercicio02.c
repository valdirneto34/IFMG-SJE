#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MaxTam 3
#define InicioArranjo 1
typedef int Apontador;

typedef struct
{
    int cod;
} TipoItem;

typedef struct
{
    TipoItem Item[MaxTam];
    Apontador Frente;
    Apontador Tras;
} TipoFila;

TipoFila Fila1;
TipoFila Fila2;
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

void Imprime(TipoFila Fila)
{
    if (Vazia(Fila))
        printf("\nERRO: A Fila está vazia");
    else
    {
        printf("\n");
        for (int i = Fila.Frente - 1; i <= Fila.Tras - 2; i++)
        {
            printf("Código: %d\n\n", Fila.Item[i].cod);
        }
    }
}

void DividiFilas(TipoFila *Fila1, TipoFila *Fila2, int *resposta)
{
    int segundaMetade = (Fila1->Tras - 2) / 2;
    if (Vazia(*Fila1))
    {
        printf("ERRO: A Fila 1 está Vazia");
        return;
    }
    else
    {
        for (int i = Fila1->Frente - 1; i <= segundaMetade; i++)
        {
            Fila2->Item[Fila2->Tras - 1] = Fila1->Item[i];
            Fila1->Frente = Fila1->Frente % MaxTam + 1;
            Fila2->Tras = Fila2->Tras % MaxTam + 1;
        }
        *resposta = 1;
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int opcao, resposta = 0;
    FFVazia(&Fila1);
    FFVazia(&Fila2);
    do
    {
        printf("\n\nMENU\n\n");
        printf("Digite a opção desejada:\n");
        printf("0 - Sair\n");
        printf("1 - Enfileirar na Fila 1\n");
        printf("2 - Dividir a Fila 1\n");
        printf("3 - Imprimir a Fila 1\n");
        printf("4 - Imprimir a Fila 2\n");
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
            printf("Digite o código:\n");
            scanf("%d", &x.cod);
            Enfileira(x, &Fila1);
            break;
        }
        case 2:
        {
            if (resposta == 0)
                DividiFilas(&Fila1, &Fila2, &resposta);
            else
                printf("\nERRO: As filas já foram divididas!\n");
            break;
        }
        case 3:
        {
            Imprime(Fila1);
            break;
        }
        case 4:
        {
            Imprime(Fila2);
            break;
        }
        default:
            printf("\n\nOpção Inválida!\n\n");
        }
        _getch();
        system("cls");
    } while (opcao != 0);

    return 0;
}
