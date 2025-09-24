#include <iostream>
using namespace std;
int main()
{
    int num[10], x, qtd;
    qtd = 0;
    for (int i = 0; i < 10; i++)
        cin >> num[i];
    cin >> x;
    for (int i = 0; i < 10; i++)
        if (num[i] == x)
            qtd++;

    if (qtd > 0)
    {
        cout << qtd << endl;
        for (int i = 0; i < 10; i++)
            if (num[i] == x)
                cout << i << " ";
    }
    else
    {
        cout << "Mia x";
    }
    return 0;
}