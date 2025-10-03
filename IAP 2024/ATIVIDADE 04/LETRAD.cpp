#include <iostream>
using namespace std;

int main()
{

    float x, y;
    cout << "Digite dois numeros: ";
    cin >> x >> y;
    if (x > y)
    {
        cout << "O numero maior e: " << x << endl;
    }
    else if (x == y)
    {
        cout << "Os numeros sao iguais." << endl;
    }
    else
    {
        cout << "O numero maior e: " << y << endl;
    }

    system("pause");
    return 0;
}
