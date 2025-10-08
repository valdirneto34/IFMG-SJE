#include <iostream>

using namespace std;

int main()
{
    int n, cont = 0;
    cin >> n;
    char respostas[n], gabarito[n];
    for (int i = 0; i < n; i++)
    {
        cin >> gabarito[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> respostas[i];
    }
    for (int i = 0; i < n; i++)
    {
        if (respostas[i] == gabarito[i])
        {
            cont++;
        }
    }
    cout << cont;
    return 0;
}
