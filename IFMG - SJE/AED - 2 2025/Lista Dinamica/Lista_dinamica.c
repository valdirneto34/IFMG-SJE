#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

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
    TipoApontador Primeiro, Ultimo;

} TipoLista;

TipoLista Lista;
TipoItem x;

TipoApontador p;
int pos, i, tam = 0;

void FLVazia(TipoLista *Lista)
{
    Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

int Vazia(TipoLista Lista)
{
    return (Lista.Ultimo == Lista.Primeiro);
}

void Insere(TipoItem x, TipoLista *Lista)
{
    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = x;
    Lista->Ultimo->Prox = NULL;
    tam++;
}

void Imprime(TipoLista Lista)
{
    if (Vazia(Lista))
        cout("\nERRO: Lista esta vazia!\n");
    else
    {
        TipoApontador aux = Lista.Primeiro->Prox;
        while (aux != NULL)
        {
            cout("Codigo: %d\n", aux->Item.cod);
            cout("Idade: %d\n\n", aux->Item.idade);
            aux = aux->Prox;
        }
    }
}

void RetiraUltimo(TipoLista *Lista, TipoItem *x)
{
    if (Vazia(*Lista))
        cout("\nERRO: Lista esta vazia!\n");
    else
    {
        TipoApontador q, z;
        q = Lista->Primeiro->Prox;
        if (q->Prox == NULL)
        {
            *x = q->Item;
            cout("O elemento retirado foi o de codigo %d\n", x->cod);
            Lista->Ultimo = Lista->Primeiro;
            Lista->Primeiro->Prox = NULL;
        }
        else
        {
            while (q->Prox != NULL)
            {
                z = q;
                q = q->Prox;
            }
            *x = q->Item;
            cout("O elemento retirado foi o de codigo %d\n", x->cod);
            Lista->Ultimo = z;
            z->Prox = NULL;
        }
        free(q);
    }
}

void RetiraElemento(TipoLista *Lista, TipoItem *x)
{
    if (Vazia(*Lista))
        cout("\nERRO: Lista esta vazia!\n");
    else
    {
        TipoApontador q, z;
        q = Lista->Primeiro->Prox;
        if (q->Prox == NULL)
        {
            *x = q->Item;
            cout("O elemento retirado foi o de codigo %d\n", x->cod);
            Lista->Ultimo = Lista->Primeiro;
            Lista->Primeiro->Prox = NULL;
        }
        else
        {
            int retira = 0;
            while (q->Prox != NULL)
            {
                z = q;
                q = q->Prox;
                if (q->Item.cod == x->cod)
                {
                    z->Prox = q->Prox;
                    retira = 1;
                    break;
                }
            }
            if (retira)
                cout("Elemento retirado com sucesso!\n");
            else
                cout("Elemento não encontrado!\n");
        }
        free(q);
    }
}

void Procurar(TipoLista Lista, TipoItem *x)
{
    if (Vazia(Lista))
        cout("\nERRO: Lista está vazia!\n");
    else
    {
        int encontrou = 0;
        TipoApontador aux = Lista.Primeiro->Prox;
        while (aux != NULL)
        {
            if (aux->Item.cod == x->cod)
            {
                encontrou = 1;
                break;
            }
            aux = aux->Prox;
        }
        if (encontrou)
            cout("Elemento encontrado!\n");
        else
            cout("Elemento não encontrado!\n");
    }
}

void ContarIdadesPares(TipoLista Lista)
{
    if (Vazia(Lista))
        cout("\nERRO: Lista está vazia!\n");
    else
    {
        int cont = 0;
        TipoApontador aux = Lista.Primeiro->Prox;
        while (aux != NULL)
        {
            if (aux->Item.idade % 2 == 0)
                cont++;
            aux = aux->Prox;
        }
        cout("Existem %d pessoas com idades pares.\n", cont);
    }
}

void ContarIdadesImpares(TipoLista Lista)
{
    if (Vazia(Lista))
        cout("\nERRO: Lista está vazia!\n");
    else
    {
        int cont = 0;
        TipoApontador aux = Lista.Primeiro->Prox;
        while (aux != NULL)
        {
            if (aux->Item.idade % 2 != 0)
                cont++;
            aux = aux->Prox;
        }
        cout("Existem %d pessoas com idades ímpares.\n", cont);
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    FLVazia(&Lista);
    int opcao, resposta;

    do
    {
        cout("\n\nMenu\n\n");
        cout("Digite a opção desejada:\n");
        cout("0 - Sair\n");
        cout("1 - Esvaziar a lista\n");
        cout("2 - Verificar se a lista está vazia\n");
        cout("3 - Inserir elemento na lista\n");
        cout("4 - Imprimir os elemento da lista\n");
        cout("5 - Retirar último elemento da lista\n");
        cout("6 - Retirar elemento da lista pelo código\n");
        cout("7 - Procurar elemento pelo código\n");
        cout("8 - Contar idades pares na lista\n");
        cout("9 - Contar idades ímpares na lista\n");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
        {
            cout("PROGRAMA ENCERRADO\n");
            break;
        }
        case 1:
        {
            FLVazia(&Lista);
            cout("\nA lista agora está vazia\n");
            break;
        }
        case 2:
        {
            resposta = Vazia(Lista);
            if (resposta == 1)
            {
                cout("A lista está vazia!!\n");
            }
            else
            {
                cout("A lista não está vazia!!\n");
            }
            break;
        }
        case 3:
        {
            cout("Digite o codigo\n");
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
            RetiraUltimo(&Lista, &x);
            break;
        }
        case 6:
        {
            cout("Digite o código do elemento\n");
            scanf("%d", &x.cod);
            RetiraElemento(&Lista, &x);
            break;
        }
        case 7:
        {
            cout("Digite o código do elemento\n");
            scanf("%d", &x.cod);
            Procurar(Lista, &x);
            break;
        }
        case 8:
        {
            ContarIdadesPares(Lista);
            break;
        }
        case 9:
        {
            ContarIdadesImpares(Lista);
            break;
        }
        default:
        {
            cout("OPÇÃO INVALIDA!");
            break;
        }
        }
        _getch();
        system("cls");

    } while (opcao != 0);

    return 0;
}
