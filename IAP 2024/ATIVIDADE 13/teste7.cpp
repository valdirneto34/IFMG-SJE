#include <iostream>

using namespace std;

struct Pessoa
{
    string nome;
    int idade;
};

// Assinatura das funções para o programa reconhecê-las
Pessoa leDoTeclado();
void mostraPessoa(Pessoa pe);

int main()
{
    // Cria uma variável "pessoa" da struct Pessoa(recebe todas as variáveis da struct)
    Pessoa pessoa;
    // Chamo a função (não necessita de parâmetros)
    pessoa = leDoTeclado(); // A variável "pessoa" recebe os dados retornados na minha função
    // Chamo a função inserindo os parâmetros necessários
    mostraPessoa(pessoa); // Mostra os dados da minha variável "pessoa"
    return 0;
}

Pessoa leDoTeclado() // Criei a função(tipo, nome, parâmetros)
{
    // Código a ser executado ao chamar a função
    Pessoa p; // Cria uma variável "p" da struct Pessoa(recebe todas as variáveis da struct)
    cout << "Nome: ";
    // Lê do teclado o que vai ser inserido na variável "nome" da minha variável "p"
    cin >> p.nome;
    cout << "Idade: ";
    // Lê do teclado o que vai ser inserido na variável "idade" da minha variável "p"
    cin >> p.idade;
    return p; // Retorna os dados da variável "p"
}
void mostraPessoa(Pessoa pe) // Criei a função(tipo, nome, parâmetros)
{
    // Código a ser executado ao chamar a função
    cout << "--- DADOS PESSOAIS ---" << endl;
    // Mostra o nome da struct "pe", que recebeu os dados da struct "pessoa" nos parâmetros da função
    cout << pe.nome << endl;
    // Mostra a idade da struct "pe", que recebeu os dados da struct "pessoa" nos parâmetros da função
    cout << pe.idade << " anos" << endl;
    cout << "----------------------";
}
