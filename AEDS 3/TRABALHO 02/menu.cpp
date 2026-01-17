#include <iostream>

using namespace std;

int menu()
{
    int op;
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
    cout << "11 - Lista Completa de Adjacentes de um Vértice" << endl;
    cout << "12 - Exportar Grafo para Arquivo de Texto" << endl;
    cout << "13 - Editar Nome de Vértice" << endl;
    cout << "14 - Efetuar Busca em Profundidade" << endl;
    cout << "15 - Efetuar Busca em Largura" << endl;
    cout << "16 - Gerar Árvore Mínima (Kruskal)" << endl;
    cout << "17 - Gerar Árvore Mínima (Prim)" << endl;
    cout << "18 - Achar Menor Caminho (Dijkstra)" << endl;
    cout << "19 - Visualizar Grafo (HTML)" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "\nDigite sua opção: ";
    cin >> op;
    return op;
}
