#include <iostream>

using namespace std;

int main()
{
    int num[10], i;
    for (i = 0; i < 10; i++)
    {
        cin >> num[i];
    }
    for (i = 9; i >= 0; i--)
    {
        cout << num[i] << endl;
    }

    return 0;
}
