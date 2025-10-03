#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MaxTam 5
typedef int Apontador;
typedef struct
{
    int cod;
    int idade;
} TipoItem;

typedef struct
{
    TipoItem Item[MaxTam];
    Apontador Topo;
} TipoPilha;

TipoPilha Pilha;
TipoItem x;

void FPVazia(TipoPilha *Pilha)
{
    Pilha->Topo = 0;
}

int Vazia(TipoPilha Pilha)
{
    return (Pilha.Topo == 0);
}

void Empilhar(TipoPilha *Pilha, TipoItem *x)
{
    if (Pilha->Topo >= MaxTam)
        printf("ERRO: Pilha está cheia");
    else
    {
        Pilha->Item[Pilha->Topo] = *x;
        Pilha->Topo++;
    }
}

void Desempilhar(TipoPilha *Pilha, TipoItem *x)
{
    if (Vazia(*Pilha))
        printf("ERRO: Pilha está vazia");
    else
    {
        *x = Pilha->Item[Pilha->Topo - 1];
        printf("O elemento retirado foi o de código %d\n", x->cod);
        Pilha->Topo--;
    }
}

void ImprimeFundoTopo(TipoPilha *Pilha)
{
    if (Vazia(*Pilha))
        printf("ERRO: Pilha está vazia");
    else
    {
        printf("\n");
        for (int i = 0; i < Pilha->Topo; i++)
        {
            printf("Cód: %d - Idade: %d\n\n", Pilha->Item[i].cod, Pilha->Item[i].idade);
        }
    }
}

void ImprimeTopoFundo(TipoPilha *Pilha)
{
    if (Vazia(*Pilha))
        printf("ERRO: Pilha está vazia");
    else
    {
        printf("\n");
        for (int i = Pilha->Topo - 1; i >= 0; i--)
        {
            printf("Cód: %d - Idade: %d\n\n", Pilha->Item[i].cod, Pilha->Item[i].idade);
        }
    }
}

int Tamanho(TipoPilha *Pilha)
{
    return Pilha->Topo;
}

int main()
{
    int opcao, resposta;
    SetConsoleOutputCP(CP_UTF8);
    FPVazia(&Pilha);
    do
    {
        printf("\n\nMENU\n\n");
        printf("Digite a opção desejada:\n");
        printf("0 - Sair\n");
        printf("1 - Esvaziar Pilha\n");
        printf("2 - Verificar se a pilha está vazia\n");
        printf("3 - Inserir elemento na pilha\n");
        printf("4 - Retirar elemento da pilha\n");
        printf("5 - Imprimir os elementos da pilha no sentido Fundo_Topo\n");
        printf("6 - Imprimir os elementos da pilha no sentido Topo_Fundo\n");
        printf("7 - Verificar tamanho da pilha\n");

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
            FPVazia(&Pilha);
            break;
        }
        case 2:
        {
            resposta = Vazia(Pilha);
            if (resposta == 1)
                printf("Pilha está vazia");
            else
                printf("Pilha não está vazia");
            break;
        }
        case 3:
        {
            printf("Digite o código: ");
            scanf("%d", &x.cod);
            printf("Digite a idade: ");
            scanf("%d", &x.idade);
            Empilhar(&Pilha, &x);
            break;
        }
        case 4:
        {
            Desempilhar(&Pilha, &x);
            break;
        }
        case 5:
        {
            ImprimeFundoTopo(&Pilha);
            break;
        }
        case 6:
        {
            ImprimeTopoFundo(&Pilha);
            break;
        }
        case 7:
        {
            printf("O tamanho da pilha é %d", Tamanho(&Pilha));
            break;
        }
        default:
            printf("\n\nOpção inválida\n\n");
        }
        _getch();
        system("cls");
    } while (opcao != 0);

    return 0;
}
