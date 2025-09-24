#include <iostream>
using namespace std;

int main()
{
    float nota1, nota2, nota3, nota4, recuperacao, total;
    cout << "Insira as quatro notas: ";
    cin >> nota1 >> nota2 >> nota3 >> nota4;

    total = (nota1 + nota2 + nota3 + nota4);

    if (total >= 60)
    {
        cout << "Aprovado!" << endl;
    }
    else
    {
        cout << "Insira a nota da recuperacao: ";
        cin >> recuperacao;
        if (total > recuperacao)
        {
            cout << "Reprovado!" << endl;
        }
        else if (recuperacao < 60)
        {
            cout << "Reprovado!" << endl;
        }
        else
        {
            cout << "Aprovado!" << endl;
        }
    }

    system("pause");
    return 0;
}
