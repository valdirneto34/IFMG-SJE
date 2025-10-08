// PROGRAMA 4 (Testar com a sequência 32, s, 0, s, 10, n).

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    double c, f;
    char outra = 's';
    while (outra != 'n')
    {
        cout << "C: ";
        cin >> c;
        f = (c * 9 / 5) + 32;
        cout << "F: " << fixed << setprecision(2) << f << endl;
        cout << "Outra? [s|n]: ";
        cin >> outra;
    }
    return 0;
}