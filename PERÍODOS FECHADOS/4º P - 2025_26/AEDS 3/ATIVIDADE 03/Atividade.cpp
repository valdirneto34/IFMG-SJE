/*
Implemente em C++, usando arquivos para armazenamento dos dados, um programa que faça o cadastro e a listagem de pessoas,
armazenando nome completo, altura_str e idade_str. Monte um arquivo PDF contando resumidamente como fez a atividade,
quais problemas teve e como os superou, colocando prints do código e do resultado para ilustrar o que foi construído.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>
#include <windows.h>

using namespace std;

struct Pessoa
{
    string nome;
    float altura;
    int idade;
};

fstream arq;

int cadastraPessoa()
{
    arq.open("cadastros.txt", ios::app);
    if (!arq.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }
    Pessoa p;
    string altura_str;
    char opc;

    cout << "\nDigite o nome da pessoa: ";
    getline(cin, p.nome);
    cout << "Digite a altura da pessoa em metros: ";
    cin >> altura_str;
    cout << "Digite a idade da pessoa: ";
    cin >> p.idade;

    replace(altura_str.begin(), altura_str.end(), ',', '.');
    p.altura = stof(altura_str);
    cout << "\nNome..: " << p.nome << endl;
    cout << "Altura: " << setprecision(2) << fixed << p.altura << " metros" << endl;
    cout << "Idade.: " << p.idade << " anos\n\n";

    while (opc != 'S' && opc != 'N')
    {
        cout << "Deseja cadastrar essa pessoa? [S/N]:  ";
        cin >> opc;
        opc = toupper(opc);
        if (opc != 'S' && opc != 'N')
        {
            cout << "\nOpção inválida! ";
        }
    }
    if (opc == 'S')
    {
        arq << p.nome << endl;
        arq << setprecision(2) << fixed << p.altura << endl;
        arq << p.idade << endl;
        cout << "\nPessoa cadastrada com sucesso!\n\n";
    }
    else
    {
        cout << "\nA pessoa não foi cadastrada!\n\n";
        cin.ignore();
    }
    arq.close();
}

int listaPessoas()
{
    string nome, altura_str, idade_str;
    arq.open("cadastros.txt", ios::in);
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
        cout << "Nome..: " << nome << endl;
        cout << "Altura: " << altura_str << endl;
        cout << "Idade.: " << idade_str << endl;
        cout << "---------------------------------------" << endl;
    }

    arq.close();
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
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
            cadastraPessoa();
            break;
        }
        case 2:
        {
            listaPessoas();
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

    return 0;
}