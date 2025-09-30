// PROGRAMA QUE CALCULA A FÓRMULA DE BHASKARA

#include <iostream>
#include <cmath>
#include <windows.h>

using namespace std;

struct Formula
{
    double a, b, c, xVertice, yVertice, cortaEixoY;
};

void limpaTela();
void leDoTeclado();
void calculaBhaskara();
void maisUmCalculo();
void msgFinal();

Formula bhaskara;
string opc = "S";
int cont = 0;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    system("cls");
    cout << "\n>>>>>>Fórmula de Bhaskara<<<<<<\n";
    while (true)
    {
        cont++;
        leDoTeclado();
        calculaBhaskara();
        maisUmCalculo();
        if (opc == "N" || opc == "n")
            break;
        limpaTela();
    }
    msgFinal();

    system("pause");
    return 0;
}

void msgFinal()
{
    if (cont == 1)
        cout << "\nRealizamos " << cont << " cálculo dessa vez!" << endl;
    else
        cout << "\nRealizamos " << cont << " cálculos dessa vez!" << endl;
    cout << "Volte sempre que precisar!" << endl;
}

void maisUmCalculo()
{
    while (true)
    {
        cout << "\nMais um cálculo: [S/N] ";
        cin >> opc;
        if (opc == "S" || opc == "s" || opc == "N" || opc == "n")
            break;
        cout << "Opção inválida! ";
    }
}

void limpaTela()
{
    system("cls");
    cout << "Vamos mais uma vez!" << "\n\n";
}

void calculaBhaskara()
{
    float delta, x1, x2;
    delta = pow(bhaskara.b, 2) - (4 * bhaskara.a * bhaskara.c);
    if (delta < 0)
    {
        cout << "\nDelta é igual a: " << delta << endl;
        cout << "Não existe raízes reais, pois o delta é menor que zero." << "\n\n";
    }
    else if (delta == 0)
    {
        x1 = (-bhaskara.b + sqrt(delta)) / (2 * bhaskara.a);
        cout << "\nEquação possui apenas uma raíz, pois o delta é igual a zero." << endl;
        cout << "A raíz é igual a: " << x1 << "\n\n";
    }
    else
    {
        x1 = (-bhaskara.b + sqrt(delta)) / (2 * bhaskara.a);
        x2 = (-bhaskara.b - sqrt(delta)) / (2 * bhaskara.a);
        cout << "\nDelta é igual a: " << delta << endl;
        cout << "X1 é igual a: " << x1 << endl;
        cout << "X2 é igual a: " << x2 << "\n\n";
    }
    bhaskara.cortaEixoY = pow(bhaskara.a * 0, 2) + 0 * bhaskara.b + bhaskara.c;
    cout("Intercepta o eixo Y no %.2f\n", bhaskara.cortaEixoY);
    bhaskara.xVertice = -bhaskara.b / 2 * bhaskara.a;
    bhaskara.yVertice = -delta / 4 * bhaskara.a;
    cout("X do vértice é: %.2f\n", bhaskara.xVertice);
    cout("Y do vértice é: %.2f\n", bhaskara.yVertice);
    if (bhaskara.a > 0)
    {
        cout("Como a = %.2f > 0, ponto de mínimo.\n", bhaskara.a);
        cout("Im = {Y e R | y >= %.2f}\n", bhaskara.yVertice);
    }
    else
    {
        cout("Como a = %.2f < 0, ponto de máximo.\n", bhaskara.a);
        cout("Im = {Y e R | y <= %.2f}\n", bhaskara.yVertice);
    }
}

void leDoTeclado()
{
    cout << "Insira o valor de A: ";
    cin >> bhaskara.a;
    cout << "Insira o valor de B: ";
    cin >> bhaskara.b;
    cout << "Insira o valor de C: ";
    cin >> bhaskara.c;
}