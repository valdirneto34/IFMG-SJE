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

TipoItem Desenfileira(TipoFila *Fila, TipoItem *x)
{
    if (Vazia(*Fila))
        printf("ERRO: Fila Vazia");
    else
    {
        *x = Fila->Item[Fila->Frente - 1];
        Fila->Frente = Fila->Frente % MaxTam + 1;
        tamanho--;
    }
    return *x;
}

void Procura(TipoFila *Fila, TipoItem *x, int *resposta)
{
    if (Vazia(*Fila))
        printf("ERRO: Fila Vazia");
    else
        for (int i = Fila->Frente - 1; i <= Fila->Tras - 2; i++)
            if (Fila->Item[i].cod == x->cod)
            {
                *resposta = 1;
                return;
            }
    *resposta = 0;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int opcao, resposta;
    FFVazia(&Fila);
    do
    {
        printf("\n\nMENU\n\n");
        printf("Digite a opção desejada:\n");
        printf("0 - Sair\n");
        printf("1 - Esvaziar Fila\n");
        printf("2 - Verificar se a fila está vazia\n");
        printf("3 - Enfileirar\n");
        printf("4 - Imprimir os elementos da fila\n");
        printf("5 - Desenfileira elemento na fila\n");
        printf("6 - Tamanho da fila\n");
        printf("7 - Procurar elemento na fila\n");
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
            FFVazia(&Fila);
            printf("\nA FILA VAZIA\n");
            break;
        }
        case 2:
        {
            resposta = Vazia(Fila);
            if (resposta == 1)
                printf("\n Fila está vazia\n");
            else
                printf("\n Fila não está vazia\n");
            break;
        }
        case 3:
        {
            printf("Digite o código:\n");
            scanf("%d", &x.cod);
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
            x = Desenfileira(&Fila, &x);
            printf("O elemento desenfileirado foi o código %d\n", x.cod);
            break;
        }
        case 6:
        {
            printf("\nA Fila contém %d elementos\n", tamanho);
            break;
        }
        case 7:
        {
            printf("Digite o código que eseja procurar: ");
            scanf("%d", &x.cod);
            Procura(&Fila, &x, &resposta);
            if (resposta == 1)
                printf("\nElemento encontrado!\n");
            else
                printf("\nElemento não encontrado\n");
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
