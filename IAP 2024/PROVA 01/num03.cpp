// Crie um programa que leia dois números digitados pelo usuário e os apresente em ordem crescente na tela.

#include <iostream>

using namespace std;

int main()
{
    int num1, num2;
    cout << "Digite o primeiro numero: ";
    cin >> num1;
    cout << "Digite o segundo numero: ";
    cin >> num2;
    if (num1 > num2)
    {
        cout << num2 << endl;
        cout << num1 << endl;
    }
    else
    {
        cout << num1 << endl;
        cout << num2 << endl;
    }
    return 0;
}