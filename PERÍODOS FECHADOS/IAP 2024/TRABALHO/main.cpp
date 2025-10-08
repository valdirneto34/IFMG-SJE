#include <iostream>
#include "menu.cpp"
#include "funcoes.cpp"

using namespace std;

const int MAX = 100;

int main()
{
    Funcionarios f[MAX];
    Dependentes d[MAX];
    Limites lim;
    lim.limiteF = 0;
    lim.limiteD = 0;
    int op;
    do
    {
        op = menu();
        if (op == 1)
        {
            f[lim.limiteF] = leFuncionario();
            lim.limiteF++;
        }
        else if (op == 2)
        {
            d[lim.limiteD] = leDependente();
            lim.limiteD++;
        }
        else if (op == 3)
        {
            mostraFuncionarios(f, lim.limiteF);
        }
        else if (op == 4)
        {
            mostraDependentes(d, lim.limiteD);
        }
        else if (op == 5)
        {
            lim = excluirFuncionarios(f, d, lim.limiteF, lim.limiteD);
        }
        else if (op == 6)
        {
            lim = excluirDependentes(d, lim.limiteF, lim.limiteD);
        }
        else if (op == 7)
        {
            editarFuncionario(f, lim.limiteF);
        }
        else if (op == 8)
        {
            editarDependentes(d, lim.limiteD);
        }
        else if (op != 0)
        {
            cout << "Inválido!" << endl;
        }
    } while (op != 0);

    cout << "Saindo..." << endl;

    system("pause");
    return 0;
}
