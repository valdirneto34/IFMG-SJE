// PROGRAMA 2 (Testar com as entradas 5 e 6, uma de cada vez).

#include <iostream>

using namespace std;

int main()
{
    int n1 = 0, n2 = 1, soma, qtd;
    cin >> qtd;
    for (int i = 0; i < qtd; i = i + 1)
    {
        cout << n2 << ' ';
        soma = n1 + n2;
        n1 = n2;
        n2 = soma;
    }
    return 0;
}