#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void Shellsort(int A[])
{
    int i, j, h = 1;
    int x;

    do
    {
        h = h * 3 + 1;
    } while (h < 3);

    do
    {
        h = h / 3;
        for (i = h + 1; i <= 3; i++)
        {
            x = A[i];
            j = i;
            while (A[j - h] > x)
            {
                A[j] = A[j - h];
                j = j - h;
                if (j <= h)
                {
                    goto L999;
                }
            }
        L999:
            A[j] = x;
        }
    } while (h != 1);
}

int main()
{
    char memoria_temporaria;
    int qtd_fitas, qtd_memoria;
    char entrada_dado = {};
    string dado = "";
    char fita1[50], fita2[50], fita3[50], fita4[50], fita5[50], fita6[50];
    cout << "Digite a quantidade de memoria disponivel:\n";
    cin >> qtd_memoria;
    cout << "Digite a quantidade de fitas disponiveis:\n";
    cin >> qtd_fitas;
    cout << "Digite uma palavra para ser ordenada:\n";
    cin.ignore();
    while (cin.get(entrada_dado) && entrada_dado != '\n')
    {
        dado += entrada_dado;
    }

    cout << "O tamanho da palavra e " << dado.length() << "." << endl;

    vector<string> pedacos;
    for (int i = 0; i < dado.length(); i += qtd_memoria)
    {
        pedacos.push_back(dado.substr(i, qtd_memoria)); 
    }

    cout << "\nA palavra foi dividida em " << pedacos.size() << " pedacos." << endl;
    for (int i = 0; i < pedacos.size(); i++)
    {
        cout << "Pedaco " << i + 1 << ": " << pedacos[i] << endl;
    }
    

    return 0;
}