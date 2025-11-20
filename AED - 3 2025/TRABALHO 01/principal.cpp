#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <windows.h>

using namespace std;

struct Vertice
{
    int u, x, y;
};

class Grafo
{
private:
    map<int, int> id_para_indice;
    vector<int> indice_para_id;
    // declarar a matriz ou lista
    // declarar uma matriz para as coordenadas
    vector<vector<int>> arestas;
    vector<Vertice> vertices;
    // declarar variáveis de controle: número de vértices e arestas, se é direcionado, etc.
    int numVertices, numArestas, contArestas;
    bool direcionado;

    int getIndice(int idReal)
    {
        if (id_para_indice.find(idReal) != id_para_indice.end())
        {
            return id_para_indice[idReal];
        }
        return -1;
    }

public:
    void importar(const char *nome_arquivo)
    {
        id_para_indice.clear();
        indice_para_id.clear();
        vertices.clear();
        arestas.clear();
        contArestas = 0;

        ifstream arq_grafo(nome_arquivo);
        if (!arq_grafo.is_open())
        {
            cout << "\nERRO: Não foi possível abrir o arquivo!" << endl;
            return;
        }
        string linha;
        getline(arq_grafo, linha);
        direcionado = (linha.find("sim") != string::npos);

        arq_grafo >> numVertices;
        indice_para_id.resize(numVertices);

        for (int i = 0; i < numVertices; i++)
        {
            int idReal, x, y;
            arq_grafo >> idReal >> x >> y;

            id_para_indice[idReal] = i;
            indice_para_id[i] = idReal;

            Vertice aux;
            aux.u = idReal;
            aux.x = x;
            aux.y = y;
            vertices.push_back(aux);
        }
        arq_grafo >> numArestas;

        arestas.resize(numVertices, std::vector<int>(numVertices, -1));

        for (int i = 0; i < numArestas; i++)
        {
            int u_real, v_real, p;
            arq_grafo >> u_real >> v_real >> p;
            inserirAresta(u_real, v_real, p);
        }

        arq_grafo.close();

        cout << "\nGrafo importado com sucesso!" << endl;
    }

    void vazio(int qtd, bool direcionadoParam)
    {
        Vertice aux;
        arestas.clear();
        vertices.clear();
        id_para_indice.clear();
        indice_para_id.clear();
        contArestas = 0;

        numVertices = qtd;
        direcionado = direcionadoParam;

        indice_para_id.resize(numVertices);

        for (int i = 0; i < numVertices; i++)
        {
            int idPadrao = i;

            id_para_indice[idPadrao] = i;
            indice_para_id[i] = idPadrao;
            aux.u = idPadrao;
            aux.x = 0;
            aux.y = 0;
            vertices.push_back(aux);
        }
        arestas.resize(numVertices, std::vector<int>(numVertices, -1));
        cout << "\nGrafo vazio criado com " << qtd << " vertices (IDs 0 a " << qtd - 1 << ")." << endl;
    }

    void exibirTodasAsAdjacencias()
    {
        if (!arestas.empty())
        {
            cout << "\n---------- TODAS AS ADJACÊNCIAS ----------" << endl;
            for (int i = 0; i < numVertices; i++)
            {
                for (int j = 0; j < numVertices; j++)
                {
                    if (arestas[i][j] != -1)
                        cout << "[" << indice_para_id[i] << ", " << indice_para_id[j] << "]: " << arestas[i][j] << "  ";
                }
                cout << endl;
            }
            cout << "-------------------------------------------" << endl;
        }
        else
        {
            cout << "\nERRO: Grafo não possui vértices!" << endl;
        }
    }

    bool consultarSeAdjacente(int u_real, int v_real)
    {
        int u = getIndice(u_real);
        int v = getIndice(v_real);

        if (u == -1 || v == -1)
        {
            cout << "\nERRO: Um dos vertices nao existe!" << endl;
            return false;
        }

        return (arestas[u][v] != -1);
    }

    void inserirAresta(int u_real, int v_real, int p)
    {
        int u_ind = getIndice(u_real);
        int v_ind = getIndice(v_real);
        if (!arestas.empty())
        {
            if (u_ind != -1 && v_ind != -1)
            {
                arestas[u_ind][v_ind] = p;
                if (!direcionado)
                {
                    arestas[v_ind][u_ind] = p;
                }
                contArestas++;
            }
            else
            {
                cout << "\nERRO: Vertices " << u_real << " ou " << v_real << " nao existem no grafo!" << endl;
            }
        }
    }

    void removerAresta(int u_real, int v_real)
    {
        int u = getIndice(u_real);
        int v = getIndice(v_real);

        if (u != -1 && v != -1)
        {
            if (arestas[u][v] != -1)
            {
                arestas[u][v] = -1;
                if (!direcionado)
                {
                    arestas[v][u] = -1;
                }
                contArestas--;
                cout << "\nAresta removida com sucesso!" << endl;
            }
            else
            {
                cout << "\nAresta não existia!" << endl;
            }
        }
        else
        {
            cout << "\nERRO: Um dos vértices não existe!" << endl;
        }
    }

    void editarCoordenadaDoVertice(int u_real, int x, int y)
    {
        bool encontrado = false;
        if (x >= 0 && y >= 0)
        {
            for (int i = 0; i < numVertices; i++)
            {
                if (vertices[i].u == u_real)
                {
                    vertices[i].x = x;
                    vertices[i].y = y;
                    encontrado = true;
                    cout << "\nCoordenadas editadas com sucesso!" << endl;
                    break;
                }
            }
        }
        else
        {
            cout << "\nERRO: Coordenadas inseridas sao invalidas!" << endl;
            return;
        }

        if (!encontrado)
        {
            cout << "\nERRO: Vertice nao foi encontrado!" << endl;
        }
    }

    int primeiroAdjacenteDoVertice(int u_real)
    {
        int u = getIndice(u_real);

        if (u == -1)
            return -2;

        for (int j = 0; j < numVertices; j++)
        {
            if (arestas[u][j] != -1)
            {
                return indice_para_id[j];
            }
        }
        return -1;
    }

    int proximoAdjacenteDoVertice(int u_real, int atual_real)
    {
        int u = getIndice(u_real);
        int atual = getIndice(atual_real);

        if (u == -1 || atual == -1)
            return -2;

        for (int j = atual + 1; j < numVertices; j++)
        {
            if (arestas[u][j] != -1)
            {
                return indice_para_id[j];
            }
        }
        return -1;
    }

    void listaCompletaDeAdjacentesDoVertice(int u_real)
    {
        int u = getIndice(u_real);

        if (u != -1)
        {
            cout << "ADJACÊNCIAS DO VÉRTICE \"" << u_real << "\": ";
            int qtd = 0;
            for (int j = 0; j < numVertices; j++)
            {
                if (arestas[u][j] != -1)
                {
                    cout << indice_para_id[j] << ",  ";
                    qtd++;
                }
            }
            if (qtd == 0)
                cout << "\nVértice não possui adjacentes!" << endl;
            else
                cout << endl;
        }
        else
        {
            cout << "\nERRO: Vértice não foi encontrado!" << endl;
        }
    }

    void exportar(const char *nome_arquivo)
    {
        if (vertices.empty())
        {
            cout << "\nERRO: Grafo não possui vértices!" << endl;
            return;
        }

        ofstream arq_exportar(nome_arquivo);
        if (!arq_exportar.is_open())
        {
            cout << "\nERRO: Não foi possivel criar o arquivo!" << endl;
            return;
        }

        string conteudo = "direcionado=";
        conteudo += (direcionado ? "sim\n" : "nao\n");
        conteudo += to_string(numVertices) + "\n";

        for (auto v : vertices)
        {
            conteudo += to_string(v.u) + " " + to_string(v.x) + " " + to_string(v.y) + "\n";
        }

        conteudo += to_string(contArestas) + "\n";

        if (!direcionado)
        {
            for (int i = 0; i < numVertices; i++)
            {
                for (int j = i; j < numVertices; j++)
                {
                    if (arestas[i][j] != -1)
                    {
                        conteudo += to_string(indice_para_id[i]) + " " + to_string(indice_para_id[j]) + " " + to_string(arestas[i][j]) + "\n";
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < numVertices; i++)
            {
                for (int j = 0; j < numVertices; j++)
                {
                    if (arestas[i][j] != -1)
                    {
                        conteudo += to_string(indice_para_id[i]) + " " + to_string(indice_para_id[j]) + " " + to_string(arestas[i][j]) + "\n";
                    }
                }
            }
        }

        arq_exportar << conteudo;
        arq_exportar.close();
        cout << "\nGrafo exportado com sucesso!" << endl;
    }
};

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    system("cls");
    Grafo grafo;
    char arquivo[100];
    int opcao, resposta, u, v, x, y, p;
    do
    {
        cout << "---------------------- MENU ----------------------" << endl;
        cout << "0 - Sair" << endl;
        cout << "1 - Importar Grafo de Arquivo de Texto" << endl;
        cout << "2 - Criar Grafo Vazio" << endl;
        cout << "3 - Exibir Adjacências" << endl;
        cout << "4 - Consultar Adjacência de Vértices" << endl;
        cout << "5 - Inserir Nova Aresta" << endl;
        cout << "6 - Inserir Nova Aresta em Conjunto" << endl;
        cout << "7 - Remover Arestas" << endl;
        cout << "8 - Editar Coordenadas de Vértice" << endl;
        cout << "9 - Consultar Primeiro Adjacente de Vértice" << endl;
        cout << "10 - Consultar Próximo Adjacente de Vértice" << endl;
        cout << "     a Partir de um Adjacente Informado" << endl;
        cout << "11 - Lista Completa de Adjacentes de um Vértice" << endl;
        cout << "12 - Exportar Grafo para Arquivo de Texto" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "\nDigite sua opção: ";
        cin >> opcao;

        switch (opcao)
        {
        case 0:
        {
            cout << "\nENCERRANDO PROGRAMA!" << endl;
            break;
        }
        case 1:
        {
            cout << "\nDigite o nome do arquivo para importação: ";
            cin >> arquivo;
            grafo.importar(arquivo);
            break;
        }
        case 2:
        {
            int qtd;
            bool direcionado;
            cout << "\nDigite a quantidade de vértices: ";
            cin >> qtd;
            cout << "Digite se o grafo e direcionado [0-nao/1-sim]: ";
            cin >> direcionado;
            grafo.vazio(qtd, direcionado);
            break;
        }
        case 3:
        {
            grafo.exibirTodasAsAdjacencias();
            break;
        }
        case 4:
        {
            cout << "Digite o vértice de origem: ";
            cin >> u;
            cout << "Digite o vértice de destino: ";
            cin >> v;
            if (grafo.consultarSeAdjacente(u, v))
                cout << "\nVértices são adjacentes!" << endl;
            else
                cout << "\nVértices não são adjacentes!" << endl;
            break;
        }
        case 5:
        {
            cout << "\nDigite o vértice de origem: ";
            cin >> u;
            cout << "Digite o vértice de destino: ";
            cin >> v;
            cout << "Digite o peso da aresta: ";
            cin >> p;
            grafo.inserirAresta(u, v, p);
            break;
        }
        case 6:
        {
            cout << "Para parar, digite: -1 -1" << endl;
            cout << "Digite nessa ordem:" << endl;
            cout << "ORIGEM  DESTINO  PESO" << endl;
            do
            {
                cin >> u >> v >> p;
                if (u == -1 && v == -1)
                    break;
                grafo.inserirAresta(u, v, p);
            } while (true);

            break;
        }
        case 7:
        {
            cout << "\nDigite o vértice de origem: ";
            cin >> u;
            cout << "Digite o vértice de destino: ";
            cin >> v;
            grafo.removerAresta(u, v);
            break;
        }
        case 8:
        {
            cout << "\nDigite o vértice que deseja editar: ";
            cin >> u;
            cout << "Digite o valor de x: ";
            cin >> x;
            cout << "Digite o valor de y: ";
            cin >> y;
            grafo.editarCoordenadaDoVertice(u, x, y);
            break;
        }
        case 9:
        {
            cout << "\nDigite o número do vértice: ";
            cin >> u;
            resposta = grafo.primeiroAdjacenteDoVertice(u);

            if (resposta == -1)
                cout << "\nERRO: Primeiro adjacente não foi encontrado!" << endl;
            else if (resposta == -2)
                cout << "\nERRO: Número de vértice inválido!" << endl;
            else
                cout << "\nPrimeiro adjacente do vértice \"" << u << "\" é: " << resposta << endl;
            break;
        }
        case 10:
        {
            cout << "\nDigite o número do vértice: ";
            cin >> u;
            cout << "Digite o número do vértice atual: ";
            cin >> v;
            resposta = grafo.proximoAdjacenteDoVertice(u, v);

            if (resposta == -1)
                cout << "\nERRO: Próximo adjacente não foi encontrado!" << endl;
            else if (resposta == -2)
                cout << "\nERRO: Número de vértice inválido!" << endl;
            else
                cout << "\nPróximo adjacente do vértice \"" << u << "\" é: " << resposta << endl;
            break;
        }
        case 11:
        {
            cout << "Digite o número do vértice: ";
            cin >> u;
            grafo.listaCompletaDeAdjacentesDoVertice(u);
            break;
        }
        case 12:
        {
            cout << "\nDigite o nome do arquivo para exportação: ";
            cin >> arquivo;
            grafo.exportar(arquivo);
            break;
        }
        default:
        {
            cout << "\nERRO: OPÇÃO INVÁLIDA!" << endl;
            break;
        }
        }

        system("pause");
        system("cls");

    } while (opcao != 0);

    return 0;
}