#include <iostream>

using namespace std;

int menu()
{
    int op;
    cout << "\n0. Sair." << endl;
    cout << "1. Cadastrar Funcionario." << endl;
    cout << "2. Cadastrar Dependente." << endl;
    cout << "3. Listar Funcionarios." << endl;
    cout << "4. Listar Dependentes." << endl;
    cout << "5. Excluir Funcionario." << endl;
    cout << "6. Excluir Dependente." << endl;
    cout << "7. Editar Funcionario." << endl;
    cout << "8. Editar Dependente." << endl;
    cout << "Sua opcao: ";
    cin >> op;
    cin.ignore();
    return op;
}
