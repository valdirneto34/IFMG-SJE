#include <iostream>

using namespace std;

int main()
{
    int num[10];
    for (int i = 0; i < 10; i++)
    {
        cin >> num[i];
    }
    for (int i = 0; i < 10; i++)
    {
        if (num[i] % 2 == 0)
        {
            cout << num[i] << " ";
        }
    }
    cout << endl;
    for (int i = 0; i < 10; i++)
    {
        if (num[i] % 2 != 0)
        {
            cout << num[i] << " ";
        }
    }
    return 0;
}