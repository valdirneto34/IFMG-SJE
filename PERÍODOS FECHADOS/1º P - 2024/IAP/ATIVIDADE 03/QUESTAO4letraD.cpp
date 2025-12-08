#include <iostream>
using namespace std;

int main()
{

    int resultado, numpensado;
    cout << "Pense em um numero natural, multiplique ele por cinco, adicione seis ao resultado, multiplique por quatro, adicione mais nove e, multiplique por cinco." << endl;
    cout << "Insira o resultado : ";
    cin >> resultado;
    numpensado = (resultado - 165) / 100;
    cout << "Numero pensado = " << numpensado << endl;

    return 0;
}