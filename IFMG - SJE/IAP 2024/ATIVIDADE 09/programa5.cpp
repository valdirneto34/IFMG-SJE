// PROGRAMA 5 (Testar com sequência 5 12 0 85221 -98 78).

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int n;
    long a, g = 0, l = INFINITY;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        if (a > g)
        {
            g = a;
        }
        if (a < l)
        {
            l = a;
        }
    }

    cout << "G: " << g << endl;
    cout << "L: " << l << endl;
    return 0;
}