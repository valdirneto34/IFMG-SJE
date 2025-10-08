/*Crie um programa em C++ que receba os dados necessário, calcule o IMC da pessoa e mostre o valor do IMC e a classificação da pessoa com base no valor calculado.
Poste aqui, em um único arquivo PDF, um breve parágrafo explicando o que fez, seguido de prints do código criado e do programa em execução.*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    float altura, peso, imc;
    cout << "Ola, sou um programa que calcula o seu IMC." << endl;
    cout << "Para comecarmos, insira a sua altura em metros: ";
    cin >> altura;
    cout << "Insira o seu peso em Kg: ";
    cin >> peso;
    imc = (peso / pow(altura, 2));
    cout << "O seu IMC e: " << imc << endl;

    if (imc <= 16.9)
    {
        cout << "Muito abaixo do peso." << endl;
    }
    else if (imc <= 18.4)
    {
        cout << "Abaixo do peso." << endl;
    }
    else if (imc <= 24.9)
    {
        cout << "Peso normal." << endl;
    }
    else if (imc <= 29.9)
    {
        cout << "Acima do peso." << endl;
    }
    else if (imc <= 34.9)
    {
        cout << "Obesidade grau I." << endl;
    }
    else if (imc <= 40)
    {
        cout << "Obesidade grau II." << endl;
    }
    else if (imc > 40)
    {
        cout << "Obesidade grau III." << endl;
    }

    system("pause");
    return 0;
}
