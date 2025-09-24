#include <iostream>
#include <cmath>
using namespace std;

int main()
{

    int numero;
    float quadrado, cubo, raiz;
    cout << "Digite um numero inteiro postivo maior que zero: ";
    cin >> numero;
    quadrado = pow(numero, 2);
    cubo = pow(numero, 3);
    raiz = sqrt(numero);
    cout << "Numero ao quadrado: " << quadrado << endl;
    cout << "Numero ao cubo: " << cubo << endl;
    cout << "Raiz quadrada: " << raiz << endl;

    system("pause");
    return 0;
}
