// PROGRAMA 1 (Testar com 70, 500 e 30, um de cada vez).
#include <iostream>

using namespace std;

int main()
{
    int h, m;
    cin >> m;
    h = m / 60;
    m = m % 60;

    cout << h << endl;
    cout << m << endl;

    return 0;
}
