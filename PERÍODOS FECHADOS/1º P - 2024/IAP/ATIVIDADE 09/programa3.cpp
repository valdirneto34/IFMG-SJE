// PROGRAMA 3 (Testar com as entradas 1, 2, 3, 5, uma de cada vez).

#include <iostream>

using namespace std;

int main()
{
    int n1 = 0, n2 = 1, soma, enesimo;
    cin >> enesimo;
    
    for (int i = 0; i < enesimo - 1; i = i + 1)
    {
        soma = n1 + n2;
        n1 = n2;
        n2 = soma;
    }

    cout << n2 << ' ';
    return 0;
}