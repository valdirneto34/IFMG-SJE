#include <iostream>
using namespace std;

int main()
{

    float pes, polegadas, jardas, milhas;
    cout << "Digite um numero na medida de comprimento pes: ";
    cin >> pes;
    polegadas = pes * 12;
    jardas = pes / 3;
    milhas = jardas / 1.76;
    cout << "Polegadas: " << polegadas << endl;
    cout << "Jardas: " << jardas << endl;
    cout << "Milhas: " << milhas << endl;

    system("pause");
    return 0;
}
