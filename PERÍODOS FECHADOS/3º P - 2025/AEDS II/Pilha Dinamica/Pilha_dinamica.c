#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef struct
{
    int cod;
    int idade;
} TipoItem;
typedef struct TipoCelula *TipoApontador;
typedef struct TipoCelula
{
    TipoItem Item;
    TipoApontador Prox;
} TipoCelula;
typedef struct
{
    TipoApontador Fundo, Topo;
    int Tam;
} TipoPilha;

TipoPilha Pilha;
TipoItem x;

void FPVazia(TipoPilha *Pilha)
{
    Pilha->Topo = (TipoApontador)malloc(sizeof(TipoCelula));
    Pilha->Fundo = Pilha->Topo;
    Pilha->Topo->Prox = NULL;
    Pilha->Tam = 0;
}

int Vazia(TipoPilha Pilha)
{
    return (Pilha.Fundo == Pilha.Topo);
}

void Empilha(TipoItem x, TipoPilha *Pilha)
{
    TipoApontador aux;
    aux = (TipoApontador)malloc(sizeof(TipoCelula));
    Pilha->Topo->Item = x;
    aux->Prox = Pilha->Topo;
    Pilha->Topo = aux;
    Pilha->Tam++;
}

void Imprime(TipoPilha Pilha)
{
    if (Vazia(Pilha))
        printf("ERRO: A pilha está vazia!\n");
    else
    {
        TipoApontador aux = Pilha.Topo->Prox;
        while (aux != NULL)
        {
            printf("Codigo: %d\n", aux->Item.cod);
            printf("Idade: %d\n\n", aux->Item.idade);
            aux = aux->Prox;
        }
    }
}

void Desempilha(TipoItem *x, TipoPilha *Pilha)
{
    if (Vazia(*Pilha))
        printf("ERRO: A pilha está vazia!\n");
    else
    {
        TipoApontador q = Pilha->Topo;
        Pilha->Topo = q->Prox;
        *x = q->Prox->Item;
        free(q);
        Pilha->Tam--;
    }
}

void Procura(TipoPilha Pilha, TipoItem x)
{
    if (Vazia(Pilha))
        printf("ERRO: A pilha está vazia!\n");
    else
    {
        int encontrou = 0;
        TipoApontador aux = Pilha.Topo->Prox;
        while (aux != NULL)
        {
            if (aux->Item.cod == x.cod)
            {
                encontrou = 1;
                break;
            }
            aux = aux->Prox;
        }
        if (encontrou)
        {
            printf("Elemento encontrado!\n\n");
            printf("Codigo: %d\n", aux->Item.cod);
            printf("Idade: %d\n\n", aux->Item.idade);
        }
        else
            printf("Elemento não encontrado!\n");
    }
}

void ContarIdadesPares(TipoPilha Pilha)
{
    if (Vazia(Pilha))
        printf("ERRO: A pilha está vazia!\n");
    else
    {
        int cont = 0;
        TipoApontador aux = Pilha.Topo->Prox;
        while (aux != NULL)
        {
            if (aux->Item.idade % 2 == 0)
                cont++;
            aux = aux->Prox;
        }
        printf("Existem %d pessoas com idades pares.\n", cont);
    }
}

void ContarIdadesImpares(TipoPilha Pilha)
{
    if (Vazia(Pilha))
        printf("ERRO: A pilha está vazia!\n");
    else
    {
        int cont = 0;
        TipoApontador aux = Pilha.Topo->Prox;
        while (aux != NULL)
        {
            if (aux->Item.idade % 2 != 0)
                cont++;
            aux = aux->Prox;
        }
        printf("Existem %d pessoas com idades ímpares.\n", cont);
    }
}

int main()
{
    FPVazia(&Pilha);
    SetConsoleOutputCP(CP_UTF8);
    int opcao, resposta;

    do
    {
        printf("\n\nMENU\n\n");
        printf("Digite a opção desejada:\n");
        printf("0 - Sair\n");
        printf("1 - Esvaziar a pilha\n");
        printf("2 - Verificar se a lista está pilha\n");
        printf("3 - Empilhar elemento na pilha\n");
        printf("4 - Imprimir os elementos da pilha\n");
        printf("5 - Desempilhar elemento da pilha\n");
        printf("6 - Procurar elemento pelo código\n");
        printf("7 - Contar idades pares na pilha\n");
        printf("8 - Contar idades ímpares na pilha\n");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
        {
            printf("PROGRAMA ENCERRADO\n");
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
            {
                printf("A pilha está vazia!\n");
            }
            else
            {
                printf("A pilha não está vazia!\n");
            }
            break;
        }
        case 3:
        {
            printf("Digite o código\n");
            scanf("%d", &x.cod);
            printf("Digite a idade\n");
            scanf("%d", &x.idade);
            Empilha(x, &Pilha);
            break;
        }
        case 4:
        {
            Imprime(Pilha);
            break;
        }
        case 5:
        {
            Desempilha(&x, &Pilha);
            break;
        }
        case 6:
        {
            printf("Digite o código do elemento\n");
            scanf("%d", &x.cod);
            Procura(Pilha, x);
            break;
        }
        case 7:
        {
            ContarIdadesPares(Pilha);
            break;
        }
        case 8:
        {
            ContarIdadesImpares(Pilha);
            break;
        }
        default:
        {
            printf("OPÇÃO INVALIDA!");
            break;
        }
        }
        _getch();
        system("cls");

    } while (opcao != 0);

    return 0;
}
