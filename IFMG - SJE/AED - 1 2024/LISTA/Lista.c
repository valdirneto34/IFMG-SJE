#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#define InicioArranjo 1
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
    Apontador Primeiro;
    Apontador Ultimo;
} TipoLista;

TipoLista Lista;
TipoItem x;
Apontador pos;

void FLVazia(TipoLista *Lista)
{
    Lista->Primeiro = InicioArranjo;
    Lista->Ultimo = Lista->Primeiro;
}

int Vazia(TipoLista Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{
    if (Lista->Ultimo > MaxTam)
        cout("\nA Lista está cheia\n");
    else
    {
        Lista->Item[Lista->Ultimo - 1] = x;
        Lista->Ultimo = Lista->Ultimo + 1;
    }
}

void Imprime(TipoLista Lista)
{
    cout("\n");
    for (int i = Lista.Primeiro - 1; i <= Lista.Ultimo - 2; i++)
    {
        cout("Cód: %d -- Idade: %d\n\n", Lista.Item[i].cod, Lista.Item[i].idade);
    }
}

void Retira(Apontador pos, TipoLista *Lista, TipoItem *x)
{
    if (Vazia(*Lista) || pos >= Lista->Ultimo)
        cout("ERRO: Posição não existe\n");
    else
    {
        *x = Lista->Item[pos - 1];
        cout("O elemento retirado foi o de código %d\n", x->cod);
        Lista->Ultimo--;
        for (int i = pos; i < Lista->Ultimo - 1; i++)
            Lista->Item[i - 1] = Lista->Item[i];
    }
}

void RetiraPos(Apontador pos, TipoLista *Lista, TipoItem *x)
{
    if (Vazia(*Lista) || pos >= Lista->Ultimo)
        cout("ERRO: Posição não existe\n");
    else
    {
        *x = Lista->Item[pos];
        cout("O elemento retirado foi o de código %d\n", x->cod);
        Lista->Ultimo--;
        for (int i = pos; i < Lista->Ultimo - 1; i++)
            Lista->Item[i] = Lista->Item[i + 1];
    }
}

void Procura(TipoItem x, TipoLista Lista)
{
    if (Vazia(Lista))
    {
        cout("Lista está vazia\n");
        return;
    }
    int aux = 0;
    for (int i = Lista.Primeiro; i < Lista.Ultimo - 1; i++)
        if (Lista.Item[i].cod == x.cod)
            aux = 1;
    if (aux == 1)
        cout("Elemento encontrado\n");
    else
        cout("Elemento não encontrado\n");
}

void InserePrimeiraPosicao(TipoItem *x, TipoLista *Lista)
{
    if (Lista->Ultimo > MaxTam)
    {
        cout("\nA Lista está cheia\n");
        return;
    }
    else
    {
        Lista->Ultimo++;
        for (int i = Lista->Ultimo - 2; i > Lista->Primeiro - 1; i--)
            Lista->Item[i] = Lista->Item[i - 1];
        Lista->Item[Lista->Primeiro - 1] = *x;
    }
}

void InserePosEscUsu(TipoItem *x, TipoLista *Lista, Apontador pos)
{
    if (Lista->Ultimo > MaxTam)
    {
        cout("\nA Lista está cheia\n");
        return;
    }
    else
    {
        Lista->Ultimo++;
        for (int i = Lista->Ultimo - 2; i > pos - 1; i--)
            Lista->Item[i] = Lista->Item[i - 1];
        Lista->Item[pos] = *x;
    }
}

int main()
{
    int opcao, resposta;
    SetConsoleOutputCP(CP_UTF8);
    FLVazia(&Lista);
    do
    {
        cout("\n\nMENU\n\n");
        cout("Digite a opção desejada:\n");
        cout("0 - Sair\n");
        cout("1 - Esvaziar Lista\n");
        cout("2 - Verificar se a lista está vazia\n");
        cout("3 - Inserir elemento na lista\n");
        cout("4 - Imprimir os elementos da lista\n");
        cout("5 - Retirar elemento da lista antes da posição determinada\n");
        cout("6 - Retirar elemento da lista\n");
        cout("7 - Pesquisar elemento na lista\n");
        cout("8 - Inserir na primeira posição\n");
        cout("9 - Inserir um elemnto na posição determinada pelo usuário\n");
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
            FLVazia(&Lista);
            cout("\nLISTA VAZIA\n");
            break;
        }
        case 2:
        {
            resposta = Vazia(Lista);
            if (resposta == 1)
                cout("\n Lista está vazia\n");
            else
                cout("\n Lista não está vazia\n");
            break;
        }
        case 3:
        {
            cout("Digite o código\n");
            scanf("%d", &x.cod);
            cout("Digite a idade\n");
            scanf("%d", &x.idade);
            Insere(x, &Lista);
            break;
        }
        case 4:
        {
            Imprime(Lista);
            break;
        }
        case 5:
        {
            cout("Digite a posição\n");
            scanf("%d", &pos);
            Retira(pos, &Lista, &x);
            break;
        }
        case 6:
        {
            cout("Digite a posição\n");
            scanf("%d", &pos);
            RetiraPos(pos, &Lista, &x);
            break;
        }
        case 7:
        {
            cout("Digite o código do elemento\n");
            scanf("%d", &x.cod);
            Procura(x, Lista);
            break;
        }
        case 8:
        {
            cout("Digite o código\n");
            scanf("%d", &x.cod);
            cout("Digite a idade\n");
            scanf("%d", &x.idade);
            InserePrimeiraPosicao(&x, &Lista);
            break;
        }
        case 9:
        {
            cout("Digite o código\n");
            scanf("%d", &x.cod);
            cout("Digite a idade\n");
            scanf("%d", &x.idade);
            cout("Digite a posição\n");
            scanf("%d", &pos);
            InserePosEscUsu(&x, &Lista, pos);
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
