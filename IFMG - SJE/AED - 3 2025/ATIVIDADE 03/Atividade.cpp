#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <windows.h>

/*
Implemente em C++, usando arquivos para armazenamento dos dados, um programa que faça o cadastro e a listagem de pessoas,
armazenando nome completo, altura e idade. Monte um arquivo PDF contando resumidamente como fez a atividade,
quais problemas teve e como os superou, colocando prints do código e do resultado para ilustrar o que foi construído.
*/

struct Pessoa
{
    string nome;
    float altura;
    int idade;
};


Pessoa cadastraPessoa(Pessoa p)
{
    cout << "\nDigite o nome da pessoa: ";
    getline(cin, p.nome);
    cout << "Digite a altura da pessoa em metros: ";
    cin >> p.altura;
    cout << "Digite a idade da pessoa: ";
    cin >> p.idade;
    cout << p.nome << " tem " << p.idade << " anos e altura de " << p.altura << " metros." << endl;
    return p;
}

void listaPessoas(){
    
}

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    Pessoa pessoa_ler, pessoa_saida;
    int opcao;
    fstream arq("arquivo.txt");
    arq.open("arquivo.txt", ios::in);
    if (!arq.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

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
            cadastraPessoa(pessoa_ler);
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

    arq.close();

    return 0;
}