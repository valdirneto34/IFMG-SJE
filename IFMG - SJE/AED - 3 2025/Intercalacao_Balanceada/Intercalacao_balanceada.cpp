#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    int qtd_fitas, qtd_memoria, aux = 0;
    string dado = "";
    fstream arq("instrucoes.txt", ios::in);
    fstream arq1, arq2, arq3, arq4, arq5, arq6;
    if (!arq.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }
    arq >> qtd_memoria;
    arq.ignore();
    arq >> qtd_fitas;
    arq.ignore();
    getline(arq, dado);
    arq.close();

    vector<vector<string>> fitas(qtd_fitas);
    cout << "O tamanho da palavra e " << dado.length() << "." << endl;

    // --- Fase de Distribuição Inicial (sem alterações) ---
    for (int i = 0; i < dado.length(); i += qtd_memoria)
    {
        vector<char> memoria_interna;
        for (int j = 0; j < qtd_memoria && (i + j) < dado.length(); ++j)
        {
            memoria_interna.push_back(dado[i + j]);
        }
        sort(memoria_interna.begin(), memoria_interna.end());

        string bloco(memoria_interna.begin(), memoria_interna.end());
        fitas[aux].push_back(bloco);

        aux++;
        if (aux == (qtd_fitas / 2))
        {
            aux = 0;
        }
    }

    cout << "\nConteudo das fitas apos a escrita balanceada (blocos ordenados):\n";
    for (int i = 0; i < qtd_fitas; i++)
    {
        cout << "Fita " << i + 1 << ": ";
        for (const auto &bloco : fitas[i])
        {
            cout << bloco << " | ";
        }
        cout << endl;
    }

    // --- Fase de Intercalação Balanceada ---
    bool usar_primeira_metade = true;
    int rodada = 0;
    int k = qtd_fitas / 2;

    while (true)
    {
        int inicio_leitura, inicio_escrita;
        if (usar_primeira_metade)
        {
            inicio_leitura = 0;
            inicio_escrita = k;
        }
        else
        {
            inicio_leitura = k;
            inicio_escrita = 0;
        }

        for (int i = 0; i < k; ++i)
        {
            fitas[inicio_escrita + i].clear();
        }

        vector<int> ponteiros_de_bloco(k, 0);
        int fita_saida_atual = 0;

        while (true)
        {
            vector<string> blocos_para_intercalar;
            vector<int> indices_fitas_origem;

            bool ha_blocos_para_ler = false;
            for (int i = 0; i < k; ++i)
            {
                int indice_fita_leitura = inicio_leitura + i;
                if (ponteiros_de_bloco[i] < fitas[indice_fita_leitura].size())
                {
                    blocos_para_intercalar.push_back(fitas[indice_fita_leitura][ponteiros_de_bloco[i]]);
                    indices_fitas_origem.push_back(i);
                    ha_blocos_para_ler = true;
                }
            }

            if (!ha_blocos_para_ler)
            {
                break;
            }

            for (int indice_fita : indices_fitas_origem)
            {
                ponteiros_de_bloco[indice_fita]++;
            }

            string bloco_intercalado = "";
            vector<int> ponteiros_de_char(blocos_para_intercalar.size(), 0);

            while (true)
            {
                char min_char = '~';
                int indice_bloco_com_min = -1;

                for (int i = 0; i < blocos_para_intercalar.size(); ++i)
                {
                    if (ponteiros_de_char[i] < blocos_para_intercalar[i].length())
                    {
                        if (blocos_para_intercalar[i][ponteiros_de_char[i]] < min_char)
                        {
                            min_char = blocos_para_intercalar[i][ponteiros_de_char[i]];
                            indice_bloco_com_min = i;
                        }
                    }
                }

                if (indice_bloco_com_min == -1)
                {
                    break;
                }

                bloco_intercalado += min_char;
                ponteiros_de_char[indice_bloco_com_min]++;
            }

            fitas[inicio_escrita + fita_saida_atual].push_back(bloco_intercalado);
            fita_saida_atual = (fita_saida_atual + 1) % k;
        }

        // <-- A CORREÇÃO CRÍTICA ESTÁ AQUI
        // Limpar as fitas de leitura APÓS a conclusão de toda a intercalação da rodada.
        // Isso garante que a contagem para a condição de parada seja feita corretamente.
        for (int i = 0; i < k; ++i)
        {
            fitas[inicio_leitura + i].clear();
        }

        // Checar a condição de parada.
        int fitas_com_dados = 0;
        for (int i = 0; i < qtd_fitas; ++i)
        {
            if (!fitas[i].empty())
            {
                fitas_com_dados++;
            }
        }
        if (fitas_com_dados <= 1)
        {
            cout << "\n--- Fim da intercalacao ---";
            // A impressão do estado final foi movida para fora do loop para evitar duplicação.
            break;
        }

        cout << "\n--- Conteudo das fitas apos a rodada " << rodada + 1 << " ---\n";
        for (int j = 0; j < qtd_fitas; j++)
        {
            cout << "Fita " << j + 1 << ": ";
            for (const auto &bloco : fitas[j])
            {
                cout << bloco << " | ";
            }
            cout << endl;
        }
        rodada++;
        usar_primeira_metade = !usar_primeira_metade;
    }

    // Imprimir o estado final das fitas, onde apenas uma conterá o resultado.
    cout << "\nEstado final das fitas:\n";
    for (int j = 0; j < qtd_fitas; j++)
    {
        cout << "Fita " << j + 1 << ": ";
        for (const auto &bloco : fitas[j])
        {
            cout << bloco << " | ";
        }
        cout << endl;
    }

    cout << "\nPalavra ordenada final:\n";
    for (const auto &fita : fitas)
    {
        if (!fita.empty())
        {
            for (const auto &bloco : fita)
            {
                cout << bloco;
            }
        }
    }
    cout << endl
         << endl;

    return 0;
}
