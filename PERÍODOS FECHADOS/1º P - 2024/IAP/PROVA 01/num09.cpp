// Crie um programa que leia quatro números decimais digitados pelo usuário, calcule sua média simples e apresente o resultado na tela.

#include <iostream>

using namespace std;

int main()
{
    float num1, num2, num3, num4;
    cout << "Digite o primeiro numero: ";
    cin >> num1;
    cout << "Digite o segundo numero: ";
    cin >> num2;
    cout << "Digite o terceiro numero: ";
    cin >> num3;
    cout << "Digite o quarto numero: ";
    cin >> num4;
    cout << "O resultado e: ";
    cout << (num1 + num2 + num3 + num4) / 4 << endl;
    return 0;
}
