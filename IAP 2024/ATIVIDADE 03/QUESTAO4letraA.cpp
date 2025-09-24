#include <iostream>
using namespace std;

int main()
{

    float tamanho, taxa, tempo;
    cout << "Insira o tamanho do arquivo: ";
    cin >> tamanho;
    cout << "Insira a taxa de transferencia: ";
    cin >> taxa;
    tempo = tamanho / taxa;
    cout << "Tempo = " << tempo << endl;

    system("pause");
    return 0;
}