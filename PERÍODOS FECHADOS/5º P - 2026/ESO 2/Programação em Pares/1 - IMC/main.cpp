#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    float peso, altura, imc;

    cout << "Digite sua altura em centímetros: ";
    cin >> altura;
    cout << "Digite seu peso em quilogramas: ";
    cin >> peso;
    imc = peso / ((altura / 100) * (altura / 100));

    cout << "Seu IMC é " << imc << endl;

    if (imc < 16)
    {
        cout << "Magreza grave" << endl;
    }
    else if (imc < 17)
    {
        cout << "Magreza moderada" << endl;
    }
    else if (imc < 18.5)
    {
        cout << "Magreza Leve" << endl;
    }
    else if (imc < 25)
    {
        cout << "Magreza Saudavel" << endl;
    }
    else if (imc < 30)
    {
        cout << "Sobrepeso" << endl;
    }
    else if (imc < 35)
    {
        cout << "Obesidade Grau 1" << endl;
    }
    else if (imc < 40)
    {
        cout << "Obesidade Grau 2" << endl;
    }
    else if (imc >= 40)
    {
        cout << "Obesidade Grau 3" << endl;
    }
}