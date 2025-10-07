#include <iostream>
#include <vector>

using namespace std;

void troca(char *a, char *b)
{
    char aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void refaz_cima_baixo(vector<char> carac, int k, int N)
{
    int j; // Variável 'j' não declarada no PDF original
    while (2 * k <= N)
    {
        j = 2 * k;
        /* encontra maior filho */
        if (j < N && v[j].chave < v[j + 1].chave)
        {
            j++;
        }
        /* testa se pai é maior que filho */
        if (v[k].chave >= v[j].chave)
        {
            break;
        }
        /* troca pai e maior filho, repete */
        troca(v[k], v[j]);
        k = j;
    }
}

void refaz_baixo_cima(vector<char> carac, int k)
{
    /* se pai for menor que filho, troca */
    while (k > 1 && v[k / 2].chave < v[k].chave)
    { // No PDF, a comparação não inclui '.chave', mas é implícito
        troca(v[k], v[k / 2]);
        /* vai para o pai e repete o processo */
        k = k / 2;
    }
}

void heap_constroi(vector<char> carac, int n)
{
    int k = n / 2;
    while (k >= 1)
    {
        refaz_cima_baixo(carac, k, n);
        k--;
    }
}

// Insere um novo item no heap
void heap_insere(vector<char> carac, int *n, struct item novo)
{
    *n += 1;
    v[*n] = novo;
    refaz_baixo_cima(v, *n);
}

// Remove o maior item do heap (a raiz)
char heap_remove_maximo(vector<char> carac, int *n)
{
    troca(v[1], v[*n]);
    *n -= 1;
    refaz_cima_baixo(v, 1, *n);
    return v[*n + 1];
}

void heapsort(vector<char> carac, int n)
{
    heap_constroi(v, n);
    int k = n;
    while (k >= 1)
    {
        troca(v[k], v[1]);
        k--;
        /* elementos de v[1] a v[k] */
        refaz_cima_baixo(v, 1, k);
    }
}

int main()
{
    vector<char> caracteres;
    caracteres.push_back('E');
    caracteres.push_back('Y');
    caracteres.push_back('O');
    caracteres.push_back('A');
    caracteres.push_back('C');
    caracteres.push_back('F');
    caracteres.push_back('P');
    caracteres.push_back('V');

    return 0;
}