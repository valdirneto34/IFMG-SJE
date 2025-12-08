// Calcular a raiz quadrada de números digitados pelo usuário até que o usuário digite 0;
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int num = 1;

    while (num != 0)
    {
        cout << "Digite um numero para ver sua raiz quadrada (0 para parar): ";
        cin >> num;
        if (num != 0)
        {
            cout << "Raiz quadrada: " << sqrt(num) << endl;
        }
    }

    cout << "FIM!" << endl;

    system("pause");
    return 0;
}
