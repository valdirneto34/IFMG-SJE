#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    char memoria_temporaria;
    int qtd_fitas, qtd_memoria, aux = 0, qtd_fitas_com_dados;
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
    cout << "Digite uma palavra para ser ordenada:\n";
    cin.ignore();
    vector<vector<string>> fitas(qtd_fitas);
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

    vector<vector<string>> *fitas_entrada = &fitas;
    vector<vector<string>> fitas_saida(qtd_fitas);
    int rodada = 0;
    while (qtd_fitas_com_dados > 1)
    {
        for (int i = 0; i < qtd_fitas; ++i)
        {
            fitas_saida[i].clear();
        }
        for (int i = 0; i < qtd_fitas / 2; ++i)
        {
            // Encontre os índices das fitas de entrada
            int indice_fita1 = i;
            int indice_fita2 = i + qtd_fitas / 2;

            // Encontre o índice da fita de saída correspondente
            int indice_fita_saida = i;

            // Verifique se as fitas de entrada não estão vazias
            // Esta verificação evita que o algoritmo tente mesclar fitas que já estão vazias.
            // Se ambas as fitas de um par não tiverem mais dados, o 'continue' pula para o próximo par de fitas,
            // otimizando o processamento.
            if (fitas_entrada->at(indice_fita1).empty() && fitas_entrada->at(indice_fita2).empty())
            {
                continue;
            }

            // --- Lógica de Intercalação (Merge) de Dois Caminhos ---
            // Esta é a parte central da fase de intercalação, onde os dados de duas fitas
            // de entrada são combinados em uma única fita de saída, de forma ordenada.

            // "Ponteiros de leitura" para cada fita de entrada
            // 'p1' e 'p2' são índices que simulam os "cabeçotes de leitura" das fitas.
            // Eles rastreiam o progresso da leitura em cada fita, começando do primeiro elemento (índice 0).
            size_t p1 = 0;
            size_t p2 = 0;

            // Laço principal para mesclar as duas fitas
            // O loop continua enquanto houver elementos a serem lidos em AMBAS as fitas de entrada.
            // Quando uma das fitas for completamente lida, o loop se encerra.
            while (p1 < fitas_entrada->at(indice_fita1).size() && p2 < fitas_entrada->at(indice_fita2).size())
            {
                // Compara o elemento atual de cada fita para encontrar o menor.
                // O <= garante estabilidade: se os elementos forem iguais, o da primeira fita é escolhido.
                if (fitas_entrada->at(indice_fita1)[p1] <= fitas_entrada->at(indice_fita2)[p2])
                {
                    // Se o elemento da fita 1 for o menor, ele é copiado para a fita de saída.
                    fitas_saida[indice_fita_saida].push_back(fitas_entrada->at(indice_fita1)[p1]);
                    // O ponteiro de leitura da fita 1 é avançado para o próximo elemento.
                    p1++;
                }
                else
                {
                    // Caso contrário, o elemento da fita 2 é o menor e é copiado para a fita de saída.
                    fitas_saida[indice_fita_saida].push_back(fitas_entrada->at(indice_fita2)[p2]);
                    // O ponteiro de leitura da fita 2 é avançado.
                    p2++;
                }
            }

            // --- Adicionar Elementos Restantes ---
            // Após o loop principal, uma das fitas pode ainda ter elementos.
            // Estes blocos garantem que todos os elementos restantes sejam movidos para a fita de saída.

            // Adiciona os elementos restantes da primeira fita. Este loop só é executado
            // se a fita 2 esgotou primeiro.
            while (p1 < fitas_entrada->at(indice_fita1).size())
            {
                fitas_saida[indice_fita_saida].push_back(fitas_entrada->at(indice_fita1)[p1]);
                p1++;
            }

            // Adiciona os elementos restantes da segunda fita. Este loop só é executado
            // se a fita 1 esgotou primeiro.
            while (p2 < fitas_entrada->at(indice_fita2).size())
            {
                fitas_saida[indice_fita_saida].push_back(fitas_entrada->at(indice_fita2)[p2]);
                p2++;
            }

            // --- Fim da Rodada de Intercalação ---
        } // Fim do loop 'for' que percorre os pares de fitas.

        // Agora, você precisa trocar os ponteiros para a próxima rodada
        // As fitas que eram de saída nesta rodada se tornam as de entrada na próxima,
        // permitindo que o algoritmo prossiga com a intercalação.
        fitas_entrada = &fitas_saida; // O ponteiro 'fitas_entrada' agora aponta para a 'fitas_saida'.

        // E recalcular o número de fitas com dados
        // Este cálculo é fundamental para a condição de parada do loop principal.
        // O algoritmo para quando apenas uma fita contiver dados.
        qtd_fitas_com_dados = 0;
        for (const auto &fita : *fitas_entrada)
        {
            if (!fita.empty())
            {
                qtd_fitas_com_dados++;
            }
        }
        rodada++; // Incrementa o contador da rodada.
    }

    return 0;
}