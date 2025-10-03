#include <iostream>

using namespace std;

struct Dados
{
    int qtdHomens, qtdMulheres, homens_acimamedia, mulheres_acimamedia, maiorIdade, posicao_mais_velha;
    double mediahomens, mediamulheres, mediatodos;
};

struct Pessoa
{
    string nome;
    int idade;
    char sexo;
};

char maisUmaPessoa()
{
    char opc = 'S';
    while (true)
    {
        cout << "Quer adicionar mais? [S/N] ";
        cin >> opc;
        if (opc == 'S' || opc == 's' || opc == 'N' || opc == 'n')
            break;
        cout << "Opção inválida! ";
    }
    return opc;
};

void mostraDados(Pessoa people[], int qtd, Dados data)
{
    cout << "\nMédia da idade dos homens: " << data.mediahomens << endl;
    cout << "Média da idade das mulheres: " << data.mediamulheres << endl;
    cout << "Média da idade de todos: " << data.mediatodos << endl;
    cout << "Homens com idade acima da média geral: " << data.homens_acimamedia << endl;
    cout << "Mulheres com idade acima da média geral: " << data.mulheres_acimamedia << endl;
    if (qtd > 0)
        cout << "Nome da pessoa mais velha: " << people[data.posicao_mais_velha].nome << endl;
    else
        cout << "Nome da pessoa mais velha: Nenhuma pessoa foi adicionada!" << endl;
};

Dados calculaDados(Pessoa people[], int qtd, Dados data)
{
    for (int i = 0; i < qtd; i++)
    {
        data.mediatodos += people[i].idade;
        if (people[i].sexo == 'M' || people[i].sexo == 'm')
        {
            data.mediahomens += people[i].idade;
            data.qtdHomens++;
        }
        else
        {
            data.mediamulheres += people[i].idade;
            data.qtdMulheres++;
        }
    }
    if (data.qtdHomens == 0)
        data.mediahomens = 0;
    else
        data.mediahomens /= data.qtdHomens;
    if (data.qtdMulheres == 0)
        data.mediamulheres = 0;
    else
        data.mediamulheres /= data.qtdMulheres;
    if (qtd == 0)
        data.mediatodos = 0;
    else
        data.mediatodos /= qtd;

    for (int i = 0; i < qtd; i++)
    {
        if ((people[i].sexo == 'M' || people[i].sexo == 'm') && people[i].idade > data.mediatodos)
            data.homens_acimamedia++;
        else if ((people[i].sexo == 'F' || people[i].sexo == 'f') && people[i].idade > data.mediatodos)
            data.mulheres_acimamedia++;
    }
    return data;
};

Pessoa inserePessoa()
{
    Pessoa p;
    cout << "Digite o nome: ";
    cin >> p.nome;
    cout << "Digite a idade: ";
    cin >> p.idade;
    while (true)
    {
        cout << "Digite o sexo: [M/F] ";
        cin >> p.sexo;
        if (p.sexo == 'M' || p.sexo == 'm' || p.sexo == 'F' || p.sexo == 'f')
            break;
        cout << "Opção inválida! ";
    }
    return p;
};

void mostraPessoas(Pessoa people[], int cont)
{
    cout << endl;
    char opc = 'S';
    while (true)
    {
        cout << "Deseja ver as pessoas cadastradas? [S/N] ";
        cin >> opc;
        if (opc == 'S' || opc == 's' || opc == 'N' || opc == 'n')
            break;
        cout << "Opção inválida! ";
    }
    cout << endl;
    if (opc == 'S' || opc == 's')
    {
        cout << "\n------------ PESSOAS CADASTRADAS ------------" << endl;
        for (int i = 0; i < cont; i++)
        {
            cout << people[i].nome << " tem ";
            cout << people[i].idade;
            if (people[i].idade < 2)
                cout << " ano e é do sexo ";
            else
                cout << " anos e é do sexo ";
            if (people[i].sexo == 'M' || people[i].sexo == 'm')
                cout << "masculino." << endl;
            else
                cout << "feminino." << endl;
        }
        cout << "---------------------------------------------" << "\n\n";
    }
    cout << "\nEncerrando programa..." << endl;
};