#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Vertice
{
    int u, x, y;
};

class Grafo
{
    // declarar a matriz ou lista
    // declarar uma matriz para as coordenadas
    int **arestas;
    vector<vector<int>> arestas2;
    vector<Vertice> vertices;
    // declarar variáveis de controle: número de vértices e arestas, se é direcionado, etc.
    int numVertices, numArestas;
    bool direcionado;

public:
    void importar(const char *nome_arquivo)
    {
        ifstream arq_grafo(nome_arquivo);
        if (!arq_grafo.is_open())
        {
            cout << "Erro ao abrir o arquivo!" << endl;
        }

        string linha;
        getline(arq_grafo, linha);
        direcionado = (linha.find("sim") != string::npos);

        arq_grafo >> numVertices;

        for (int i = 0; i < numVertices; i++)
        {
            int vertice, x, y;
            arq_grafo >> vertice >> x >> y;
            Vertice aux;
            aux.u = vertice;
            aux.x = x;
            aux.y = y;
            vertices.push_back(aux);
        }

        arq_grafo >> numArestas;

        arestas2.resize(numVertices ,std::vector<int>(numVertices, -1));

        arestas = new int *[numVertices];
        for (int i = 0; i < numVertices; i++)
        {
            arestas[i] = new int[numVertices];
        }

        for (int i = 0; i < numArestas; i++)
        {
            for (int j = 0; j < numArestas; j++)
            {
                arestas[i][j] = -1;
            }
        }

        for (int i = 0; i < numArestas; i++)
        {
            int u, v, p;
            arq_grafo >> u >> v >> p;
            inserirAresta(u, v, p);
        }

        arq_grafo.close();
        cout << "Grafo importado com sucesso!" << endl;
    }

    void vazio(int qtd, bool direcionadoParam)
    {
        numVertices = qtd;
        direcionado = direcionadoParam;
        arestas = new int *[numVertices];
        for (int i = 0; i < numVertices; i++)
        {
            arestas[i] = new int[numVertices];
        }

        for (int i = 0; i < numArestas; i++)
        {
            for (int j = 0; j < numArestas; j++)
            {
                arestas[i][j] = -1;
            }
        }
    }

    void exibirTodasAsAdjacencias()
    {
        for (int i = 0; i < numArestas; i++)
        {
            for (int j = 0; j < numArestas; j++)
            {
                cout << "[" << i << ", " << j << "]: " << arestas[i][j] << "  ";
            }
            cout << endl;
        }
    }

    bool consultarSeAdjacente(int u, int v)
    {
    }

    void inserirAresta(int u, int v, int p)
    {
        arestas[u][v] = p;
        if (!direcionado)
        {
            arestas[u][v] = -1;
        }
    }

    void removerAresta(int u, int v)
    {
        arestas[u][v] = -1;
        if (!direcionado)
        {
            arestas[v][u] = -1;
        }
        numArestas--;
    }

    void editarCoordenadaDoVertice(int u, int x, int y)
    {
        bool encontrado = false;
        if (x >= 0 && y >= 0)
        {
            for (int i = 0; i < numVertices; i++)
            {
                if (vertices[i].u == u)
                {
                    encontrado = true;
                    vertices[i].x = x;
                    vertices[i].y = y;
                }
            }
        }
        else
        {
            cout << "Coordenadas inseridas são inválidas!" << endl;
        }

        if (!encontrado)
        {
            cout << "Vertice nao foi encontrado!" << endl;
        }
    }

    int primeiroAdjacenteDoVertice(int u)
    {
    }

    int proximoAdjacenteDoVertice(int u, int atual)
    {
    }

    void listaCompletaDeAdjacentesDoVertice(int u)
    {
    }

    void exportar()
    {
    }

    void mostrarGraficamente()
    {
    }
};

int main()
{
    Grafo grafo;
    int opcao, u, v, x, y;
    do
    {
        cout << "---------------------- MENU ----------------------" << endl;
        cout << "0 - Sair" << endl;
        cout << "1 - Importar Grafo de Arquivo de Texto" << endl;
        cout << "2 - Criar Grafo Vazio" << endl;
        cout << "3 - Exibir Adjacencias" << endl;
        cout << "4 - Consultar Adjacencia de Vertices" << endl;
        cout << "5 - Inserir Nova Aresta" << endl;
        cout << "6 - Inserir Nova Aresta em Conjunto" << endl;
        cout << "7 - Remover Arestas" << endl;
        cout << "8 - Editar Coordenadas de Vertice" << endl;
        cout << "9 - Consultar Primeiro Adjacente de Vertice" << endl;
        cout << "10 - Consultar Proximo Adjacente de Vertice" << endl;
        cout << "     a Partir de um Adjacente Informado" << endl;
        cout << "11 - Lista Completa de Adjacentes de um Vertice" << endl;
        cout << "12 - Exportar Grafo para Arquivo de Texto" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Digite sua opcao: ";
        cin >> opcao;

        switch (opcao)
        {
        case 0:
        {
            cout << "ENCERRANDO PROGRAMA!" << endl;
            break;
        }
        case 1:
        {
            char arquivo[100];
            cout << "Digite o nome do arquivo para importacao: ";
            cin >> arquivo;
            grafo.importar(arquivo);
            break;
        }
        case 2:
        {
            int qtd;
            bool direcionado;
            cout << "Digite a quantidade de vertices: ";
            cin >> qtd;
            cout << "Digite se o grafo e direcionado [0-nao/1-sim]: ";
            cin >> direcionado;
            grafo.vazio(qtd, direcionado);
            break;
        }
        case 3:
        {
            cout << "------ TODAS AS ADJACENCIAS ------" << endl;
            grafo.exibirTodasAsAdjacencias();
            cout << "----------------------------------" << endl;
            break;
        }
        case 4:
        {
            break;
        }
        case 5:
        {
            break;
        }
        case 6:
        {
            break;
        }
        case 7:
        {
            break;
        }
        case 8:
        {
            cout << "Digite o vertice que deseja editar: ";
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
            break;
        }
        case 10:
        {
            break;
        }
        case 11:
        {
            break;
        }
        case 12:
        {
            break;
        }
        default:
        {
            cout << "OPCAO INVALIDA!" << endl;
            break;
        }
        }

        system("pause");
        system("cls");

    } while (opcao != 0);

    return 0;
}