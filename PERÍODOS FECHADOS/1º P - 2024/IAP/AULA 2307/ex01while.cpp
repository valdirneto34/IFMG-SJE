// Apresentar os números pares e um intervalo definido pelo usuário.
// COM WHILE >>>>

#include <iostream>

using namespace std;

int main()
{
    int n1, n2;
    cout << "Digite em qual numero deseja comecar uma sequencia: ";
    cin >> n1;
    cout << "Digite em qual numero deseja terminar essa sequencia: ";
    cin >> n2;

    while (n1 <= n2)
    {
        if (n1 % 2 == 0)
        {
            cout << n1 << endl;
            n1 += 2;
        }
        else
        {
            cout << n1 << endl;
            n1 += 1;
        }
    }
    cout << "FIM DA SEQUENCIA!" << endl;
    system("pause");
    return 0;
}
