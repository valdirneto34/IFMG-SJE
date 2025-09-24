#include <iostream>
using namespace std;

int main()
{

    int x, inteiro;
    cout << "Digite um numero inteiro, postivo ou negativo: ";
    cin >> x;
    if (x < 0)
    {
        inteiro = (x * (-1));
    }
    else
    {
        inteiro = x;
    }
    cout << "Valor absoluto: " << inteiro << endl;

    system("pause");
    return 0;
}
