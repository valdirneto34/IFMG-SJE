#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int x, y, z;
    cout << "Digite dois numeros inteiros: ";
    cin >> x >> y;
    z = pow(x, y);
    cout << "Resultado: " << z << endl;

    system("pause");
    return 0;
}
