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

void FilasIguais(TipoFila *Fila1, TipoFila *Fila2, int *resposta)
{
    *resposta = 0;
    if (Vazia(*Fila1) || Vazia(*Fila2))
    {
        *resposta = 2;
        return;
    }
    else
        for (int i = Fila1->Frente - 1; i <= Fila1->Tras - 2; i++)
            if (Fila1->Item[i].cod != Fila2->Item[i].cod)
            {
                *resposta = 1;
                return;
            }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int opcao, resposta;
    FFVazia(&Fila1);
    FFVazia(&Fila2);
    do
    {
        printf("\n\nMENU\n\n");
        printf("Digite a opção desejada:\n");
        printf("0 - Sair\n");
        printf("1 - Enfileirar na Fila 1\n");
        printf("2 - Enfileirar na Fila 2\n");
        printf("3 - Verificar se as duas filas são iguais\n");
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
            printf("Digite o código:\n");
            scanf("%d", &x.cod);
            Enfileira(x, &Fila2);
            break;
        }
        case 3:
        {
            FilasIguais(&Fila1, &Fila2, &resposta);
            if (resposta == 0)
                printf("\nAs duas filas são iguais!\n");
            else if (resposta == 1)
                printf("\nAs duas filas não são iguais!\n");
            else if (resposta == 2)
                printf("ERRO: Uma das filas está Vazia");
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
