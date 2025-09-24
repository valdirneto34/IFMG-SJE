#include <iostream>

using namespace std;

int main()
{
    int inteiros[10], num, cont = 0;
    for (int i = 0; i < 10; i++)
    {
        cin >> inteiros[i];
    }
    cin >> num;
    for (int i = 0; i < 10; i++)
    {
        if (num == inteiros[i])
        {
            cout << "SIM" << endl;
            cont++;
            break;
        }
    }
    if (cont == 0)
    {
        cout << "NAO" << endl;
    }
    return 0;
}
