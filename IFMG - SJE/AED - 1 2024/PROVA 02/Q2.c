#include <stdio.h>
#include <stdlib.h>
#define InicioArranjo 1
#define MaxTam 5
typedef int Apontador;

typedef struct
{
    int valor;
} TipoItem;

typedef struct
{
    TipoItem Item[MaxTam];
    Apontador Inicio;
    Apontador Fim;

} TipoFila;

TipoFila Fila;
TipoFila Fila1;
TipoFila Fila2;
TipoItem x;

void FFVazia(TipoFila *Fila)
{
    Fila->Inicio = InicioArranjo;
    Fila->Fim = Fila->Inicio;
}

int Vazia(TipoFila Fila)
{
    return (Fila.Fim == Fila.Inicio);
}

void Insere(TipoFila *Fila, TipoItem x)
{
    if (Fila->Fim % MaxTam + 1 == Fila->Inicio)
    {
        cout("\nERRO: Fila esta cheia\n");
    }
    else
    {
        Fila->Item[Fila->Fim - 1] = x;
        Fila->Fim = Fila->Fim % MaxTam + 1;
    }
}

void DivideFila(TipoFila Fila, TipoFila *Fila1, TipoFila *Fila2)
{
    if (Vazia(Fila))
    {
        cout("\nERRO: Fila esta vazia\n");
    }
    else
    {
        for (int i = Fila.Inicio - 1; i <= Fila.Fim - 2; i++)
        {
            if (i % 2 == 0)
            {
                Fila1->Item[Fila1->Fim - 1] = Fila.Item[i];
                Fila1->Fim = Fila1->Fim % MaxTam + 1;
            }
            else
            {
                Fila2->Item[Fila2->Fim - 1] = Fila.Item[i];
                Fila2->Fim = Fila2->Fim % MaxTam + 1;
            }
        }
    }
}
void Imprime(TipoFila Fila)
{
    if (Vazia(Fila))
    {
        cout("\nERRO: Fila esta vazia\n");
    }
    else
    {
        cout("\n");
        for (int i = Fila.Inicio - 1; i <= Fila.Fim - 2; i++)
        {
            cout("%d   ", Fila.Item[i].valor);
        }
    }
}

int main()
{
    FFVazia(&Fila);
    FFVazia(&Fila1);
    FFVazia(&Fila2);
    int opcao;
    do
    {
        cout("\n\nMENU\n\n");
        cout("0 - Sair\n");
        cout("1 - Inserir valor na Fila\n");
        cout("2 - Imprimir Fila Principal\n");
        cout("3 - Imprimir Fila1\n");
        cout("4 - Imprimir Fila2\n");
        cout("5 - Dividir Fila Principal\n");
        cout("Sua escolha: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 0:
        {
            cout("\nPROGRAMA ENCERRADO\n");
            break;
        }
        case 1:
        {
            cout("Digite o valor: ");
            scanf("%d", &x.valor);
            Insere(&Fila, x);
            break;
        }
        case 2:
        {
            Imprime(Fila);
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
        case 5:
        {
            DivideFila(Fila, &Fila1, &Fila2);
            break;
        }
        default:
        {
            cout("\nOPCAO INVALIDA\n");
            break;
        }
        }
        _getch();
        system("cls");
    } while (opcao != 0);

    return 0;
}