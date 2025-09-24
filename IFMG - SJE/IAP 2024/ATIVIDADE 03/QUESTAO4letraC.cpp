#include <iostream>
using namespace std;

int main()
{

    float num1, num2, num3, num4, num5, peso1, peso2, peso3, peso4, peso5;
    float media;
    cout << "Ola,eu sou um programa que calcula a media ponderada de cinco numeros decimais e seus respectivos pesos. Vamos Comecar!" << endl;
    cout << "Insira o primeiro numero: ";
    cin >> num1;
    cout << "Insira o primeiro peso: ";
    cin >> peso1;
    cout << "Insira o segundo numero: ";
    cin >> num2;
    cout << "Insira o segundo peso: ";
    cin >> peso2;
    cout << "Insira o terceiro numero: ";
    cin >> num3;
    cout << "Insira o terceiro peso: ";
    cin >> peso3;
    cout << "Insira o quarto numero: ";
    cin >> num4;
    cout << "Insira o quarto peso: ";
    cin >> peso4;
    cout << "Insira o quinto numero: ";
    cin >> num5;
    cout << "Insira o quinto peso: ";
    cin >> peso5;
    media = (num1 * peso1 + num2 * peso2 + num3 * peso3 + num4 * peso4 + num5 * peso5) / (peso1 + peso2 + peso3 + peso4 + peso5);
    cout << "Media ponderada = " << media << endl;

    return 0;
}