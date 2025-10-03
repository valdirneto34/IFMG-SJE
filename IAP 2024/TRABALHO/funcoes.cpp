#include <iostream>

using namespace std;

struct Dependentes
{
    string nome, cpf, cpfDoFuncionario, dataDeNascimento;
};

struct Funcionarios
{
    string nome, cpf, telefone, email;
};

struct Limites
{
    int limiteF, limiteD;
};

Funcionarios leFuncionario()
{
    Funcionarios f;
    cout << "\nNome: ";
    getline(cin, f.nome);
    cout << "CPF: ";
    getline(cin, f.cpf);
    cout << "Telefone: ";
    getline(cin, f.telefone);
    cout << "Email: ";
    getline(cin, f.email);
    cout << "Funcionario cadastrado com sucesso!" << endl;
    return f;
}

Dependentes leDependente()
{
    Dependentes d;
    cout << "\nNome: ";
    getline(cin, d.nome);
    cout << "CPF: ";
    getline(cin, d.cpf);
    cout << "CPF do Funcionario: ";
    getline(cin, d.cpfDoFuncionario);
    cout << "Data de Nascimento: ";
    getline(cin, d.dataDeNascimento);
    cout << "Dependente cadastrado com sucesso!" << endl;
    return d;
}

void mostraFuncionarios(Funcionarios f[], int n)
{
    cout << "\n--------- DADOS FUNCIONARIOS ---------" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Nome: " << f[i].nome << endl;
        cout << "CPF: " << f[i].cpf << endl;
        cout << "Telefone: " << f[i].telefone << endl;
        cout << "Email: " << f[i].email << endl;
        cout << "--------------------------------------" << endl;
    }
}

void mostraDependentes(Dependentes d[], int n)
{
    cout << "\n--------- DADOS DEPENDENTES ----------" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Nome: " << d[i].nome << endl;
        cout << "CPF: " << d[i].cpf << endl;
        cout << "CPF do Funcionario: " << d[i].cpfDoFuncionario << endl;
        cout << "Data de Nascimento: " << d[i].dataDeNascimento << endl;
        cout << "--------------------------------------" << endl;
    }
}

Limites excluirFuncionarios(Funcionarios f[], Dependentes d[], int limiteFunc, int limiteDepen)
{
    Limites limites;
    string apagarFuncionario;
    int contF = 0;
    cout << "Digite o CPF do funcionario que deseja excluir: ";
    getline(cin, apagarFuncionario);
    for (int i = 0; i < limiteFunc; i++)
    {
        if (apagarFuncionario == f[i].cpf)
        {
            contF++;
            for (int j = i; j < limiteFunc - 1; j++)
            {
                f[j] = f[j + 1];
            }
            limiteFunc--;
            i--;
        }
    }
    for (int i = 0; i < limiteDepen; i++)
    {
        if (apagarFuncionario == d[i].cpfDoFuncionario)
        {
            for (int j = i; j < limiteDepen - 1; j++)
            {
                d[j] = d[j + 1];
            }
            limiteDepen--;
            i--;
        }
    }
    if (contF > 0)
    {
        cout << "Funcionario excluido com sucesso!" << endl;
    }
    else
    {
        cout << "Funcionario nao encontrado!" << endl;
    }
    limites.limiteF = limiteFunc;
    limites.limiteD = limiteDepen;
    return limites;
}

Limites excluirDependentes(Dependentes d[], int limiteFunc, int limiteDepen)
{
    Limites limites;
    int dependentesExcluidos = 0;
    string apagarDependente;
    cout << "Digite o CPF do dependente que deseja excluir: ";
    getline(cin, apagarDependente);
    for (int i = 0; i < limiteDepen; i++)
    {
        if (apagarDependente == d[i].cpf)
        {
            dependentesExcluidos++;
            for (int j = i; j < limiteDepen - 1; j++)
            {
                d[j] = d[j + 1];
            }
            limiteDepen--;
            i--;
        }
    }
    if (dependentesExcluidos > 0)
    {
        cout << "Dependente excluido com sucesso!" << endl;
    }
    else
    {
        cout << "Dependente nao encontrado!" << endl;
    }
    limites.limiteF = limiteFunc;
    limites.limiteD = limiteDepen;
    return limites;
}

void editarFuncionario(Funcionarios f[], int limite)
{
    string cpfEditar;
    cout << "\nDigite o CPF do Funcionario que deseja editar: ";
    getline(cin, cpfEditar);
    for (int i = 0; i < limite; i++)
    {
        if (cpfEditar == f[i].cpf)
        {
            cout << "Insira os novos dados do CPF " << cpfEditar << ".\n";
            cout << "Nome: ";
            getline(cin, f[i].nome);
            cout << "CPF: ";
            getline(cin, f[i].cpf);
            cout << "Telefone: ";
            getline(cin, f[i].telefone);
            cout << "Email: ";
            getline(cin, f[i].email);
            cout << "Funcionario editado com sucesso!" << endl;
            return;
        }
    }
    cout << "Funcionario nao encontrado!" << endl;
}

void editarDependentes(Dependentes d[], int limite)
{
    string cpfEditar;
    cout << "\nDigite o CPF do Dependente que deseja editar: ";
    getline(cin, cpfEditar);
    for (int i = 0; i < limite; i++)
    {
        if (cpfEditar == d[i].cpf)
        {
            cout << "Insira os novos dados do CPF " << cpfEditar << ".\n";
            cout << "Nome: ";
            getline(cin, d[i].nome);
            cout << "CPF: ";
            getline(cin, d[i].cpf);
            cout << "CPF do Funcionario: ";
            getline(cin, d[i].cpfDoFuncionario);
            cout << "Data de Nascimento: ";
            getline(cin, d[i].dataDeNascimento);
            cout << "Dependente editado com sucesso!" << endl;
            return;
        }
    }
    cout << "Dependente nao encontrado!" << endl;
}
