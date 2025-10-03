#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int num[10], menor = 101, ocorrencias[10], j = 0;
    for (int i = 0; i < 10; i++)
    {
        cin >> num[i];
        if (num[i] < menor)
        {
            menor = num[i];
        }
    }
    for (int i = 0; i < 10; i++)
    {
        if (num[i] == menor)
        {
            ocorrencias[j] = i;
            j++;
            num[i] = -1;
        }
    }
    cout << "Menor: " << menor << endl;
    cout << "Ocorrencias: ";
    for (int i = 0; i < j; i++)
    {
        cout << ocorrencias[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << num[i] << " ";
    }
    cout << endl;
    return 0;
}