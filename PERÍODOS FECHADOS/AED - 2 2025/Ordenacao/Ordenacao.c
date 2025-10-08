#include <stdio.h>
#include <stdlib.h>

#define MaxTam 3

typedef int ChaveTipo;
typedef struct
{
    ChaveTipo Chave;
} Item;
typedef Item Vetor[MaxTam + 1];
Vetor A;

void Preencher(int vetor[])
{
    vetor[0] = 0;
    for (int i = 1; i <= MaxTam; i++)
    {
        printf("Digite o valor da posicao %d: ", i);
        scanf("%d", &vetor[i]);
    }
}

void Copia(int Original[], int A[])
{
    for (int i = 1; i <= MaxTam; i++)
    {
        A[i] = Original[i];
    }
}

void Imprime(int v[])
{
    for (int i = 1; i <= MaxTam; i++)
    {
        printf("%d   ", v[i]);
    }
    printf("\n");
}

void Bubblesort(int A[])
{
    int i, j, aux;
    for (i = 1; i <= MaxTam - 1; i++)
    {
        for (j = 1; j <= MaxTam - i; j++)
        {
            if (A[j] > A[j + 1])
            {
                aux = A[j];
                A[j] = A[j + 1];
                A[j + 1] = aux;
            }
        }
    }
}

void Selecao(int A[])
{
    int i, j, min;
    int x;
    for (i = 1; i <= MaxTam - 1; i++)
    {
        min = i;
        for (j = i + 1; j <= MaxTam; j++)
        {
            if (A[j] < A[min])
                min = j;
        }
        x = A[min];
        A[min] = A[i];
        A[i] = x;
    }
}

void Insercao(int A[])
{
    int i, j;
    int x;
    for (i = 2; i <= 3; i++)
    {
        x = A[i];
        j = i - 1;
        A[0] = x;
        while (x < A[j])
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = x;
    }
}

void Shellsort(int A[])
{
    int i, j, h = 1;
    int x;

    do
    {
        h = h * 3 + 1;
    } while (h < MaxTam);

    do
    {
        h = h / 3;
        for (i = h + 1; i <= MaxTam; i++)
        {
            x = A[i];
            j = i;
            while (A[j - h] > x)
            {
                A[j] = A[j - h];
                j = j - h;
                if (j <= h)
                {
                    goto L999;
                }
            }
        L999:
            A[j] = x;
        }
    } while (h != 1);
}

void Quicksort(int A[], int left, int right)
{
    int i, j, x, y;
    i = left;
    j = right;
    x = A[(left + right) / 2];
    while (i <= j)
    {
        while (A[i] < x && i < right)
        {
            i++;
        }
        while (A[j] > x && j > left)
        {
            j--;
        }
        if (i <= j)
        {
            y = A[i];
            A[i] = A[j];
            A[j] = y;
            i++;
            j--;
        }
    }
    if (j > left)
    {
        Quicksort(A, left, j);
    }
    if (i < right)
    {

        Quicksort(A, i, right);
    }
    return;
}
int main()
{
    int vetor[MaxTam + 1];
    int opcao;
    do
    {
        printf("\nMENU\n\n");
        printf("Digite a opcao desejada:\n");
        printf("0 - Sair\n");
        printf("1 - Preencher o vetor\n");
        printf("2 - Metodo Bubblesort\n");
        printf("3 - Metodo da Selecao\n");
        printf("4 - Metodo da Insercao\n");
        printf("5 - Metodo Shellsort\n");
        printf("6 - Metodo Quicksort\n");
        printf("7 - Imprimir o vetor\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 0:
        {
            printf("\nPROGRAMA ENCERRADO\n\n");
            break;
        }
        case 1:
        {
            Preencher(vetor);
            break;
        }
        case 2:
        {
            Copia(vetor, A);
            Bubblesort(A);
            printf("\nVETOR ORDENADO (Bubble Sort):\n");
            Imprime(A);
            break;
        }
        case 3:
        {
            Copia(vetor, A);
            Selecao(A);
            printf("\nVETOR ORDENADO (Selecao):\n");
            Imprime(A);
            break;
        }
        case 4:
        {
            Copia(vetor, A);
            Insercao(A);
            printf("\nVETOR ORDENADO (Insercao):\n");
            Imprime(A);
            break;
        }
        case 5:
        {
            Copia(vetor, A);
            Shellsort(A);
            printf("\nVETOR ORDENADO (Shellsort):\n");
            Imprime(A);
            break;
        }
        case 6:
        {
            Copia(vetor, A);
            Quicksort(A, 1, 3);
            printf("\nVETOR ORDENADO (Quicksort):\n");
            Imprime(A);
            break;
        }
        case 7:
        {
            printf("\nVETOR ATUAL:\n");
            Imprime(vetor);
            break;
        }
        default:
        {
            printf("OPCAO INVALIDA\n\n");
            break;
        }
        }
        _getch();
        system("cls");
    } while (opcao != 0);

    return 0;
}
