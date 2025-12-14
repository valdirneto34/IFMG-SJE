#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <windows.h>
#include <climits>

using namespace std;

struct Vertice
{
    string nome;
    int u, x, y;
};

struct ControlBuscaEmProfu
{
    char cor;
    int u, antecessor, tempoDescoberta, tempoTermino;
};

struct ControlBuscaEmLargura
{
    char cor;
    int u, antecessor, distancia;
};

class Grafo
{
private:
    vector<vector<int>> arestas;
    vector<Vertice> vertices;
    queue<int> fila;
    int numVertices, numArestas, contArestas;
    bool direcionado;

    int getVertice(int vertice) const
    {
        for (const auto &x : vertices)
        {
            if (x.u == vertice)
                return vertice;
        }
        return -1;
    }

    void visitaEmProfundidade(int u_input, int *tempo, vector<ControlBuscaEmProfu> &control)
    {
        control[u_input].cor = 'c';
        (*tempo)++;
        control[u_input].tempoDescoberta = *tempo;
        cout << "Vértice " << u_input << " (" << vertices[u_input].nome << ") descoberto!\n";
        for (int v = 0; v < numVertices; v++)
        {
            if (arestas[u_input][v] != -1 && control[v].cor == 'b')
            {
                control[v].antecessor = vertices[u_input].u;
                visitaEmProfundidade(v, tempo, control);
            }
        }
        control[u_input].cor = 'p';
        (*tempo)++;
        control[u_input].tempoTermino = *tempo;
        cout << "Vértice " << u_input << " finalizado!\n";
    }

    void visitaEmLargura(int u_input, vector<ControlBuscaEmLargura> &control)
    {
        control[u_input].cor = 'c';
        control[u_input].distancia = 0;
        queue<Vertice> f;
        f.push(vertices[u_input]);
        fila.push(vertices[u_input].u);
        cout << "Vértice " << u_input << " (" << vertices[u_input].nome << ") descoberto!\n";

        while (!f.empty())
        {
            Vertice v = f.front();
            f.pop();
            for (int k = 0; k < numVertices; k++)
            {
                if (arestas[v.u][k] != -1 && control[k].cor == 'b')
                {
                    control[k].cor = 'c';
                    control[k].antecessor = v.u;
                    control[k].distancia = control[v.u].distancia + 1;
                    f.push(vertices[k]);
                    fila.push(vertices[k].u);
                    cout << "Vértice " << vertices[k].u << " (" << vertices[k].nome << ") descoberto!\n";
                }
            }
            control[v.u].cor = 'p';
            cout << "Vértice " << v.u << " finalizado!\n\n";
        }
    }

public:
    void importar(const char *nome_arquivo)
    {
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

        for (int i = 0; i < numVertices; i++)
        {
            string nome;
            int u, x, y;
            arq_grafo >> u >> x >> y;
            getline(arq_grafo, nome);
            if (!nome.empty() && nome[0] == ' ')
            {
                nome.erase(0, 1);
            }
            if (!nome.empty() && nome.back() == '\r')
            {
                nome.pop_back();
            }

            Vertice aux;
            aux.u = u;
            aux.x = x;
            aux.y = y;
            aux.nome = nome;
            vertices.push_back(aux);
        }
        arq_grafo >> numArestas;

        arestas.resize(numVertices, std::vector<int>(numVertices, -1));

        for (int i = 0; i < numArestas; i++)
        {
            int u, v, p;
            arq_grafo >> u >> v >> p;
            inserirAresta(u, v, p);
        }

        arq_grafo.close();

        cout << "\nGrafo importado com sucesso!" << endl;
    }

    void vazio(int qtd, bool direcionadoParam)
    {
        Vertice aux;
        arestas.clear();
        vertices.clear();
        contArestas = 0;

        numVertices = qtd;
        direcionado = direcionadoParam;

        for (int i = 0; i < numVertices; i++)
        {

            aux.u = i;
            aux.x = i * 10;
            aux.y = i * 10;
            aux.nome = "SEM NOME";
            vertices.push_back(aux);
        }
        arestas.resize(numVertices, std::vector<int>(numVertices, -1));
        cout << "\nGrafo criado com " << qtd << " vértices (IDs 0 a " << qtd - 1 << ")." << endl;
    }

    void exibirTodasAsAdjacencias() const
    {
        if (arestas.empty())
        {
            cout << "\nERRO: Grafo não possui vértices!" << endl;
            return;
        }

        int largura = 6;

        cout << "\n------------------ MATRIZ DE ADJACÊNCIAS (Pesos) ------------------\n\n";

        cout << "      ";
        for (int i = 0; i < numVertices; i++)
        {
            cout << setw(largura) << i;
        }
        cout << endl;

        cout << "      " << setfill('-');
        cout << setw(numVertices * largura) << "" << setfill(' ') << endl;

        for (int i = 0; i < numVertices; i++)
        {
            cout << setw(4) << i << " |";

            for (int j = 0; j < numVertices; j++)
            {
                if (arestas[i][j] != -1)
                {
                    cout << setw(largura) << arestas[i][j];
                }
                else
                {
                    cout << setw(largura) << ".";
                }
            }
            cout << endl;
        }
        cout << "\n-------------------------------------------------------------------" << endl;
    }

    bool consultarSeAdjacente(int u_input, int v_input) const
    {
        int u = getVertice(u_input);
        int v = getVertice(v_input);

        if (u == -1 || v == -1)
        {
            cout << "\nERRO: Um dos vertices nao existe!" << endl;
            return false;
        }

        return (arestas[u][v] != -1);
    }

    void inserirAresta(int u_input, int v_input, int p)
    {
        int u = getVertice(u_input);
        int v = getVertice(v_input);

        if (!arestas.empty())
        {
            if (u != -1 && v != -1)
            {
                arestas[u][v] = p;
                if (!direcionado)
                {
                    arestas[v][u] = p;
                }
                contArestas++;
            }
            else
            {
                cout << "\nERRO: Vértices " << u_input << " ou " << v_input << " não existem no grafo!" << endl;
            }
        }
    }

    void removerAresta(int u_input, int v_input)
    {
        int u = getVertice(u_input);
        int v = getVertice(v_input);

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

    void editarCoordenadaDoVertice(int u_input, int x, int y)
    {
        int u = getVertice(u_input);
        if (u == -1)
        {
            cout << "\nERRO: Vértice não foi encontrado!" << endl;
            return;
        }
        else if (x < 0 || y < 0)
        {
            cout << "\nERRO: Coordenadas inseridas são inválidas!" << endl;
        }
        else
        {
            vertices[u].x = x;
            vertices[u].y = y;
            cout << "\nCoordenadas editadas com sucesso!" << endl;
        }
    }

    int primeiroAdjacenteDoVertice(int u_input)
    {
        int u = getVertice(u_input);

        if (u == -1)
            return -2;

        for (int j = 0; j < numVertices; j++)
        {
            if (arestas[u][j] != -1)
            {
                return vertices[j].u;
            }
        }
        return -1;
    }

    int proximoAdjacenteDoVertice(int u_input, int atual_real)
    {
        int u = getVertice(u_input);
        int atual = getVertice(atual_real);

        if (u == -1 || atual == -1)
            return -2;

        for (int j = atual + 1; j < numVertices; j++)
        {
            if (arestas[u][j] != -1)
            {
                return vertices[j].u;
            }
        }
        return -1;
    }

    void listaCompletaDeAdjacentesDoVertice(int u_input)
    {
        int u = getVertice(u_input);

        if (u != -1)
        {
            cout << "ADJACÊNCIAS DO VÉRTICE " << u_input << ": ";
            int qtd = 0;
            for (int j = 0; j < numVertices; j++)
            {
                if (arestas[u][j] != -1)
                {
                    cout << vertices[j].u << "  -  ";
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
            conteudo += to_string(v.u) + " " + to_string(v.x) + " " + to_string(v.y) + " " + v.nome + "\n";
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
                        conteudo += to_string(vertices[i].u) + " " + to_string(vertices[j].u) + " " + to_string(arestas[i][j]) + "\n";
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
                        conteudo += to_string(vertices[i].u) + " " + to_string(vertices[j].u) + " " + to_string(arestas[i][j]) + "\n";
                    }
                }
            }
        }

        arq_exportar << conteudo;
        arq_exportar.close();
        cout << "\nGrafo exportado com sucesso!" << endl;
    }

    void editarNomeVertice(int u_input)
    {
        int u = getVertice(u_input);
        if (u == -1)
        {
            cout << "\nERRO: Vértice não foi encontrado!" << endl;
            return;
        }
        else
        {
            string novoNome;
            cout << "Digite o novo nome do vértice " << u << " - " << vertices[u].nome << ": ";
            cin >> novoNome;
            vertices[u].nome = novoNome;
        }
    }

    void buscaEmProfundidade()
    {
        int tempo = 0;
        vector<ControlBuscaEmProfu> c;
        for (int i = 0; i < numVertices; i++)
        {
            ControlBuscaEmProfu aux;
            aux.u = i;
            aux.antecessor = -1;
            aux.cor = 'b';
            aux.tempoDescoberta = 0;
            aux.tempoTermino = 0;
            c.push_back(aux);
        }
        cout << "\n\n";
        for (int i = 0; i < numVertices; i++)
        {
            if (c[i].cor == 'b')
            {
                visitaEmProfundidade(i, &tempo, c);
            }
        }

        cout << "\n\n------ VÉRTICES APÓS A EXECUÇÃO ------" << endl;
        for (int i = 0; i < numVertices; i++)
        {
            printf("Vértice: %2d | Cor: %c | Ant: %2d | Descoberta: %2d | Término: %2d\n",
                   c[i].u, c[i].cor, c[i].antecessor, c[i].tempoDescoberta, c[i].tempoTermino);
        }
        cout << "--------------------------------------------" << endl;
    }

    void buscaEmLargura()
    {
        while (!fila.empty())
            fila.pop();

        vector<ControlBuscaEmLargura> c;
        for (int i = 0; i < numVertices; i++)
        {
            ControlBuscaEmLargura aux;
            aux.u = i;
            aux.antecessor = -1;
            aux.cor = 'b';
            aux.distancia = INT_MAX;
            c.push_back(aux);
        }
        cout << "\n\n";
        for (int i = 0; i < numVertices; i++)
        {
            if (c[i].cor == 'b')
            {
                visitaEmLargura(i, c);
            }
        }

        cout << "\nFila: ";
        while (!fila.empty())
        {
            cout << fila.front() << ", ";
            fila.pop();
        }
        cout << "\n\n------ VÉRTICES APÓS A EXECUÇÃO ------" << endl;
        for (int i = 0; i < numVertices; i++)
        {
            printf("Vértice: %2d | Cor: %c | Ant: %2d | Distância: %2d\n",
                   c[i].u, c[i].cor, c[i].antecessor, c[i].distancia);
        }
        cout << "--------------------------------------------" << endl;
    }
};

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    system("cls");
    Grafo grafo;
    string nomeVertice;
    string arquivo;
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
        cout << "13 - Editar Nome de Vértice" << endl;
        cout << "14 - Efetuar Busca em Profundidade" << endl;
        cout << "15 - Efetuar Busca em Largura" << endl;
        cout << "16 - Gerar Árvore Mínima" << endl;
        cout << "17 - Achar Menor Caminho (Dijkstra)" << endl;
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
            grafo.importar(arquivo.c_str());
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
            cout << "Para parar, digite: -1 -1 -1" << endl;
            cout << "Digite nessa ordem:" << endl;
            cout << "ORIGEM  DESTINO  PESO" << endl;
            do
            {
                cin >> u >> v >> p;
                if (u == -1 && v == -1 && p == -1)
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
                cout << "\nPrimeiro adjacente do vértice " << u << " é o: " << resposta << endl;
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
                cout << "\nPróximo adjacente do vértice " << u << " é o: " << resposta << endl;
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
            grafo.exportar(arquivo.c_str());
            break;
        }
        case 13:
        {
            cout << "Digite o número do vértice: ";
            cin >> u;
            grafo.editarNomeVertice(u);
            break;
        }
        case 14:
        {
            grafo.buscaEmProfundidade();
            break;
        }
        case 15:
        {
            grafo.buscaEmLargura();
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