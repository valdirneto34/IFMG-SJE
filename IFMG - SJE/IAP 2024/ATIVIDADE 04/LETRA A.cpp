#include <iostream>
using namespace std;

int main()
{

    int x, y;
    cout << "Digite um numero inteiro: ";
    cin >> x;
    if (x % 2 == 0)
    {
        y = (x / 2);
        cout << "O valor de y e: " << y << endl;
    }
    else
    {
        y = (3 * x + 1);
        cout << "O valor de y e: " << y << endl;
    }

    system("pause");
    return 0;
}
