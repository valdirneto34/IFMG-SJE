#include <iostream>
using namespace std;

int main()
{

    int num1, num2, num3, num4, num5, num6;
    float media;
    cout << "Insira o numero 1: ";
    cin >> num1;
    cout << "Insira o numero 2: ";
    cin >> num2;
    cout << "Insira o numero 3: ";
    cin >> num3;
    cout << "Insira o numero 4: ";
    cin >> num4;
    cout << "Insira o numero 5: ";
    cin >> num5;
    cout << "Insira o numero 6: ";
    cin >> num6;
    media = (num1 + num2 + num3 + num4 + num5 + num6) / 6.0;
    cout << "Media = " << media << endl;

    return 0;
}