#include <iostream>

using namespace std;

int main()
{
    int n, x, cont = 0;
    cin >> n;
    int v[n];
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    cin >> x;
    for (int i = 0; i < n; i++)
    {
        if (v[i] == x)
        {
            cont = 1;
        }
    }
    if (cont == 0)
    {
        cout << "nao_pertence" << endl;
    }
    else
    {
        cout << "pertence" << endl;
    }
    return 0;
}