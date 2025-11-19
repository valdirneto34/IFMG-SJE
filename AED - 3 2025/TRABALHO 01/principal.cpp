#include <iostream>
#include <fstream>

using namespace std;

struct Aresta
{
    int u, v, p;
};

struct Vertice
{
    int vertice, x, y;
};

class Grafo
{
    // declarar a matriz ou lista
    // declarar uma matriz para as coordenadas
    Aresta *matrizArestas;
    int **matrizVertices;
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
        }

        arq_grafo >> numArestas;

        for (int i = 0; i < numArestas; i++)
        {
            int u, v, p;
            arq_grafo >> u >> v >> p;
            inserirAresta(u, v, p);
        }

        cout << "Grafo importado com sucesso!" << endl;
    }

    void vazio(int qtd, bool direcionado)
    {
    }

    void exibirTodasAsAdjacencias()
    {
    }

    bool consultarSeAdjacente(int u, int v)
    {
    }

    void inserirAresta(int u, int v, int p)
    {
        matrizArestas = new Aresta[numArestas + 1];
        matrizArestas[numArestas - 1].u = u;
        matrizArestas[numArestas - 1].v = v;
        matrizArestas[numArestas - 1].p = p;
    }

    void removerAresta(int u, int v)
    {
        for (int i = 0; i < numArestas; i++)
        {
            if (matrizArestas[i].u == u && matrizArestas[i].v == v)
            {
                for (int j = i; j < numArestas - 1; j++)
                {
                    matrizArestas[j].u = matrizArestas[j + 1].u;
                    matrizArestas[j].v = matrizArestas[j + 1].v;
                    matrizArestas[j].v = matrizArestas[j + 1].v;
                }
                --numArestas;
                matrizArestas = new Aresta[numArestas];
            }
        }
    }

    void editarCoordenadaDoVertice(int u, int x, int y)
    {
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
    int opcao;
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
            char *arquivo;
            cout << "Digite o nome do arquivo para importacao: ";
            cin >> arquivo;
            grafo.importar(arquivo);
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
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