// Para o programa abaixo (Testar com a sequência 11, 12, 7, 8, 15, 20, 19, 18, 12 e 10).
#include <iostream>

using namespace std;

int main()
{
    double a, m, s = 0;
    int n = 10;
    cout << "Digite os numeros: ";
    for (int i = 0; i < n; i = i + 1)
    {
        cin >> a;
        s = s + a;
    }
    m = s / 10;
    cout << "M: " << m << endl;

    return 0;
}