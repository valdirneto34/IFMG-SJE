#include <iostream>
using namespace std;
int main()
{
    int inteiro;
    string *nomes;
    cout << "Digite quantos nomes quer armazenar: ";
    cin >> inteiro;
    nomes = new string[inteiro];
    for (int i = 0; i < inteiro; i++)
    {
        cout << "Nome: ";
        cin >> nomes[i];
    }
    cout << endl;
    for (int i = (inteiro - 1); i >= 0; i--)
    {
        cout << nomes[i] << endl;
    }
    return 0;
}