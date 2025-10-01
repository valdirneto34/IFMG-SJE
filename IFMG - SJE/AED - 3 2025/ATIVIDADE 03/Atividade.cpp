/*
Implemente em C++, usando arquivos para armazenamento dos dados, um programa que faça o cadastro e a listagem de pessoas,
armazenando nome completo, altura_str e idade_str. Monte um arquivo PDF contando resumidamente como fez a atividade,
quais problemas teve e como os superou, colocando prints do código e do resultado para ilustrar o que foi construído.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <windows.h>

using namespace std;

struct Pessoa
{
    string nome;
    float altura_str;
    int idade_str;
};

Pessoa cadastraPessoa()
{
    Pessoa p;
    char opc;
    while (true)
    {
        cout << "\nDigite o nome da pessoa: ";
        getline(cin, p.nome);
        cout << "Digite a altura da pessoa em metros: ";
        cin >> p.altura_str;
        cout << "Digite a idade da pessoa: ";
        cin >> p.idade_str;
        cout << "\nNome: " << p.nome << endl;
        cout << "Altura: " << p.altura_str << " metros" << endl;
        cout << "Idade: " << p.idade_str << " anos\n\n";

        while (true)
        {
            cout << "Deseja cadastrar essa pessoa? [S/N]:  ";
            cin >> opc;
            if (opc != 'S' && opc != 's' && opc != 'N' && opc != 'n')
            {
                cout << "\nOpção inválida! ";
                continue;
            }
            else if (opc == 'S' || opc == 's')
            {
                return p;
            }
            else
            {
                cin.ignore();
                break;
            }
        }
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    Pessoa pessoa;
    string nome, altura_str, idade_str;
    int opcao;

    do
    {
        cout << "\n------------ MENU ------------" << endl;
        cout << "0 - Sair" << endl;
        cout << "1 - Cadastrar Pessoa" << endl;
        cout << "2 - Listar Pessoas" << endl;
        cout << "--------------------------------" << endl;
        cout << "\nDigite a opção desejada: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao)
        {
        case 0:
        {
            cout << "\nPROGRAMA ENCERRADO!!" << endl;
            break;
        }
        case 1:
        {
            pessoa = cadastraPessoa();
            fstream arq("arquivo.txt", ios::app);
            if (!arq.is_open())
            {
                cout << "Erro ao abrir o arquivo!" << endl;
                return 1;
            }

            arq << pessoa.nome << endl;
            arq << pessoa.altura_str << endl;
            arq << pessoa.idade_str << endl;

            arq.close();
            break;
        }
        case 2:
        {
            fstream arq("arquivo.txt", ios::in);
            if (!arq.is_open())
            {
                cout << "Erro ao abrir o arquivo!" << endl;
                return 1;
            }
            cout << "\n--------- PESSOAS CADASTRADAS ---------" << endl;
            while (getline(arq, nome))
            {
                getline(arq, altura_str);
                getline(arq, idade_str);
                cout << "Nome: " << nome << endl;
                cout << "Altura: " << altura_str << endl;
                cout << "Idade: " << idade_str << endl;
                cout << "---------------------------------------" << endl;
            }

            arq.close();
            break;
        }
        default:
        {

            break;
        }
        }
        system("pause");
        system("cls");

    } while (opcao != 0);

    return 0;
}