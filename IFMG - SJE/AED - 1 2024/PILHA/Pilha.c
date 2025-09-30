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
        cout("ERRO: Pilha está cheia");
    else
    {
        Pilha->Item[Pilha->Topo] = *x;
        Pilha->Topo++;
    }
}

void Desempilhar(TipoPilha *Pilha, TipoItem *x)
{
    if (Vazia(*Pilha))
        cout("ERRO: Pilha está vazia");
    else
    {
        *x = Pilha->Item[Pilha->Topo - 1];
        cout("O elemento retirado foi o de código %d\n", x->cod);
        Pilha->Topo--;
    }
}

void ImprimeFundoTopo(TipoPilha *Pilha)
{
    if (Vazia(*Pilha))
        cout("ERRO: Pilha está vazia");
    else
    {
        cout("\n");
        for (int i = 0; i < Pilha->Topo; i++)
        {
            cout("Cód: %d - Idade: %d\n\n", Pilha->Item[i].cod, Pilha->Item[i].idade);
        }
    }
}

void ImprimeTopoFundo(TipoPilha *Pilha)
{
    if (Vazia(*Pilha))
        cout("ERRO: Pilha está vazia");
    else
    {
        cout("\n");
        for (int i = Pilha->Topo - 1; i >= 0; i--)
        {
            cout("Cód: %d - Idade: %d\n\n", Pilha->Item[i].cod, Pilha->Item[i].idade);
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
        cout("\n\nMENU\n\n");
        cout("Digite a opção desejada:\n");
        cout("0 - Sair\n");
        cout("1 - Esvaziar Pilha\n");
        cout("2 - Verificar se a pilha está vazia\n");
        cout("3 - Inserir elemento na pilha\n");
        cout("4 - Retirar elemento da pilha\n");
        cout("5 - Imprimir os elementos da pilha no sentido Fundo_Topo\n");
        cout("6 - Imprimir os elementos da pilha no sentido Topo_Fundo\n");
        cout("7 - Verificar tamanho da pilha\n");

        scanf("%d", &opcao);
        switch (opcao)
        {
        case 0:
        {
            cout("PROGRAMA ENCERRADO!\n");
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
                cout("Pilha está vazia");
            else
                cout("Pilha não está vazia");
            break;
        }
        case 3:
        {
            cout("Digite o código: ");
            scanf("%d", &x.cod);
            cout("Digite a idade: ");
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
            cout("O tamanho da pilha é %d", Tamanho(&Pilha));
            break;
        }
        default:
            cout("\n\nOpção inválida\n\n");
        }
        _getch();
        system("cls");
    } while (opcao != 0);

    return 0;
}
