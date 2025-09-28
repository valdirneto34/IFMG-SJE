#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main()

{

    char memoria_temporaria;
    int qtd_fitas, qtd_memoria, aux = 0;
    char entrada_dado;
    string dado = "";
    vector<string> pedacos;
    cout << "Digite a quantidade de memoria disponivel:\n";
    cin >> qtd_memoria;
    cout << "Digite a quantidade de fitas disponiveis:\n";
    cin >> qtd_fitas;
    while (qtd_fitas % 2 != 0)
    {
        cout << "A quantidade de fitas deve ser par. Digite novamente:\n";
        cin >> qtd_fitas;
        if (qtd_fitas % 2 == 0)
        {
            break;
        }
    }
    vector<vector<string>> fitas(qtd_fitas);
    cin.ignore();
    cout << "Digite uma palavra para ser ordenada:\n";
    while (cin.get(entrada_dado) && entrada_dado != '\n')
    {
        dado += entrada_dado;
    }

    cout << "O tamanho da palavra e " << dado.length() << "." << endl;
    for (int i = 0; i < dado.length(); i += qtd_memoria)
    {

        pedacos.push_back(dado.substr(i, qtd_memoria));
    }

    cout << "\nA palavra foi dividida em " << pedacos.size() << " pedacos." << endl;
    for (int i = 0; i < pedacos.size(); i++)
    {
        sort(pedacos[i].begin(), pedacos[i].end());
        fitas[aux].push_back(pedacos[i]);
        aux++;
        if (aux == (qtd_fitas / 2))
        {
            aux = 0;
        }
    }

    cout << "Conteudo das fitas apos a escrita balanceada:\n";

    for (int i = 0; i < qtd_fitas; i++)
    {
        cout << "Fita " << i + 1 << ": ";
        for (auto &p : fitas[i])
        {
            cout << p << " ";
        }
        cout << endl;
    }

    return 0;
}
