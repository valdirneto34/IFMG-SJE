#include "funcoesGrafo.cpp";
#include "menu.cpp";

using namespace std;

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    system("cls");
    Grafo grafo;
    string nomeVertice, arquivo, verticeOrigem, verticeDestino;
    int opcao, resposta, u, v, x, y, p;
    do
    {
        opcao = menu();

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
                cout << "\nVértices " << u << " (" << grafo.getNomePeloIdVertice(u) << ")" << " e " << v << " (" << grafo.getNomePeloIdVertice(v) << ")" << " são adjacentes!" << endl;
            else
                cout << "\nVértices " << u << " (" << grafo.getNomePeloIdVertice(u) << ")" << " e " << v << " (" << grafo.getNomePeloIdVertice(v) << ")" << " não são adjacentes!" << endl;
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
            if (resposta == -2)
                cout << "\nERRO: Número de vértice inválido!" << endl;
            else
            {
                cout << "\nPrimeiro adjacente do vértice " << u << " (" << grafo.getNomePeloIdVertice(u) << ") " << " é o: " << resposta;
                cout << " (" << grafo.getNomePeloIdVertice(resposta) << ")" << endl;
            }
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
            {
                cout << "\nPróximo adjacente do vértice " << u << " (" << grafo.getNomePeloIdVertice(u) << ")" << " é o: " << resposta;
                cout << " (" << grafo.getNomePeloIdVertice(resposta) << ")" << endl;
            }
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
        case 16:
        {
            grafo.arvoreMininmaKruskal();
            break;
        }
        case 17:
        {
            grafo.arvoreMininaPrim();
            break;
        }
        case 18:
        {
            cout << "Digite o nome do vértice de ORIGEM: ";
            cin.ignore();
            getline(cin, verticeOrigem);
            cout << "Digite o nome do vértice de DESTINO: ";
            getline(cin, verticeDestino);
            grafo.dijkstra(verticeOrigem, verticeDestino);
            break;
        }
        case 19:
        {
            grafo.visualizar();
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