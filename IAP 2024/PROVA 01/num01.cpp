// Crie um programa que leia três números decimais digitados pelo usuário e os apresente em ordem crescente na tela.

#include <iostream>

using namespace std;

int main()
{
    float num1, num2, num3;
    cout << "Digite o primeiro numero: ";
    cin >> num1;
    cout << "Digite o segundo numero: ";
    cin >> num2;
    cout << "Digite o terceiro numero: ";
    cin >> num3;
    if (num1 > num2 && num2 > num3)
    {
        cout << num3 << endl;
        cout << num2 << endl;
        cout << num1 << endl;
    }
    else if (num1 > num3 && num3 > num2)
    {
        cout << num2 << endl;
        cout << num3 << endl;
        cout << num1 << endl;
    }
    else if (num2 > num1 && num1 > num3)
    {
        cout << num3 << endl;
        cout << num1 << endl;
        cout << num2 << endl;
    }
    else if (num2 > num3 && num3 > num1)
    {
        cout << num1 << endl;
        cout << num3 << endl;
        cout << num2 << endl;
    }
    else if (num3 > num2 && num2 > num1)
    {
        cout << num1 << endl;
        cout << num2 << endl;
        cout << num3 << endl;
    }
    else if (num3 > num1 && num1 > num2)
    {
        cout << num2 << endl;
        cout << num1 << endl;
        cout << num3 << endl;
    }
    return 0;
}
