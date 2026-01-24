#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <windows.h>

using namespace std;

struct Vertice
{
    string nome;
    int u, x, y;
};

struct ControlBuscaEmProfu
{
    char cor;
    int u, antecessor, tempoDesc, tempoTer;
};

struct ControlBuscaEmLargura
{
    char cor;
    int u, antecessor, distancia;
};

struct Aresta
{
    int u, v, p;
};

struct VerticePrim
{
    int u, p, antecessor;
};

class HeapKruskal
{
private:
    void troca(Aresta *a, Aresta *b)
    {
        Aresta aux = *a;
        *a = *b;
        *b = aux;
    }

    void refaz_cima_baixo(vector<Aresta> &A, int k, int N)
    {
        int j;
        while (2 * k <= N)
        {
            j = 2 * k;
            if (j < N && A[j].p > A[j + 1].p)
                j++;
            if (A[k].p <= A[j].p)
                break;
            troca(&A[k], &A[j]);
            k = j;
        }
    }

public:
    void heap_constroi(vector<Aresta> &A, int n)
    {
        for (int k = n / 2; k >= 1; k--)
            refaz_cima_baixo(A, k, n);
    }

    Aresta heap_remove_minimo(vector<Aresta> &A, int *n)
    {
        Aresta menor = A[1];
        troca(&A[1], &A[*n]);
        (*n)--;
        A.pop_back();
        if (*n > 0)
            refaz_cima_baixo(A, 1, *n);
        return menor;
    }
};

class HeapPrim
{
private:
    void troca(VerticePrim *a, VerticePrim *b)
    {
        VerticePrim aux = *a;
        *a = *b;
        *b = aux;
    }
    void refaz_cima_baixo(vector<VerticePrim> &A, int k, int N)
    {
        int j;
        while (2 * k <= N)
        {
            j = 2 * k;
            if (j < N && A[j].p > A[j + 1].p)
                j++;
            if (A[k].p <= A[j].p)
                break;
            troca(&A[k], &A[j]);
            k = j;
        }
    }

public:
    void heap_constroi(vector<VerticePrim> &A, int n)
    {
        for (int k = n / 2; k >= 1; k--)
            refaz_cima_baixo(A, k, n);
    }
    VerticePrim heap_remove_minimo(vector<VerticePrim> &A, int *n)
    {
        VerticePrim menor = A[1];
        troca(&A[1], &A[*n]);
        (*n)--;
        A.pop_back();
        if (*n > 0)
            refaz_cima_baixo(A, 1, *n);
        return menor;
    }
};