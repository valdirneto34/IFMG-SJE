/*
Crie um programa para ler um conjunto de dados do usuário(máximo 100)
Composto por nome, idade e sexo.
Após a leitura, o programa deve calcular e mostrar:
a média de idade dos homens;
a media de idade das mulheres;
a media de idade geral;
a quantidade de homens e mulheres com idade acima da média geral;
o nome da pessoa mais velha;
*/

#include <iostream>
#include <windows.h>
#include "funcoes.cpp"
using namespace std;

const int MAX = 100;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    Pessoa pessoas[MAX];
    Dados d;
    d.qtdHomens = 0, d.qtdMulheres = 0, d.homens_acimamedia = 0, d.mulheres_acimamedia = 0, d.maiorIdade = -1, d.posicao_mais_velha = 0;
    d.mediahomens, d.mediamulheres, d.mediatodos;
    int qtd = 0;
    char opc = 'S';
    while (true)
    {
        pessoas[qtd] = inserePessoa();
        if (pessoas[qtd].idade > d.maiorIdade)
        {
            d.maiorIdade = pessoas[qtd].idade;
            d.posicao_mais_velha = qtd;
        }
        qtd++;
        opc = maisUmaPessoa();
        cout << endl;
        if (opc == 'N' || opc == 'n')
        {
            cout << "Finalizando processamento..." << endl;
            break;
        }
        if (qtd >= MAX)
        {
            cout << "Cheio..." << endl;
            break;
        }
    }
    d = calculaDados(pessoas, qtd, d);
    mostraDados(pessoas, qtd, d);
    mostraPessoas(pessoas, qtd);
    cout << "Volte Sempre!" << endl;
    system("pause");
    return 0;
}

/*
Valdir
20
M
S
Juliana
42
F
S
Sebastiao
62
M
S
Derlane
37
F
S
Anne
1
F
*/
