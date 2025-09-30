#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

/*
Implemente em C++, usando arquivos para armazenamento dos dados, um programa que faça o cadastro e a listagem de pessoas,
armazenando nome completo, altura e idade. Monte um arquivo PDF contando resumidamente como fez a atividade,
quais problemas teve e como os superou, colocando prints do código e do resultado para ilustrar o que foi construído.
*/

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    string nome;
    float altura;
    int opcao, idade;
    fstream arq("arquivo.txt");
    arq.open("arquivo.txt", ios::in);
    if (!arq.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    do
    {
        cout << "\n\nMENU\n\n";
        cout << "0 - Sair" << endl;
        cout << "1 - Cadastrar Pessoa" << endl;
        cout << "2 - Listar Pessoas" << endl;
        cout << "Digite a opção desejada: ";
        cin >> opcao;

        switch (opcao)
        {
        case 0:
        {
            cout << "\nPROGRAMA ENCERRADO!!" << endl;
            break;
        }
        case 1:
        {
            cout << "\nDigite o nome da pessoa: ";
            getline(cin, nome);
            cin.ignore();
            cout << "Digite a altura da pessoa em metros: ";
            cin >> altura;
            cin.ignore();
            cout << "Digite a idade da pessoa: ";
            cin >> idade;
            cin.ignore();
            cout << nome << " tem " << idade << " anos e altura de " << altura << " metros." << endl;
            break;
        }
        default:
        {
            cout << "\nOPÇÃO INVÁLIDA!!" << endl;
            break;
        }
        }
        system("pause");
        system("cls");

    } while (opcao != 0);

    arq.close();

    return 0;
}