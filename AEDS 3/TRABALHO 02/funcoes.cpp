#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <windows.h>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <stack>

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

struct Aresta
{
    int u, v, p;
};

struct VerticePrim
{
    int u, p, antecessor;
};

class HeapKruskal
{
private:
    void troca(Aresta *a, Aresta *b)
    {
        Aresta aux = *a;
        *a = *b;
        *b = aux;
    }

    void refaz_cima_baixo(vector<Aresta> &A, int k, int N)
    {
        int j;
        while (2 * k <= N)
        {
            j = 2 * k;
            if (j < N && A[j].p > A[j + 1].p)
                j++;
            if (A[k].p <= A[j].p)
                break;
            troca(&A[k], &A[j]);
            k = j;
        }
    }

public:
    void heap_constroi(vector<Aresta> &A, int n)
    {
        for (int k = n / 2; k >= 1; k--)
            refaz_cima_baixo(A, k, n);
    }

    Aresta heap_remove_minimo(vector<Aresta> &A, int *n)
    {
        Aresta menor = A[1];
        troca(&A[1], &A[*n]);
        (*n)--;
        A.pop_back();
        if (*n > 0)
            refaz_cima_baixo(A, 1, *n);
        return menor;
    }
};

class HeapPrim
{
private:
    void troca(VerticePrim *a, VerticePrim *b)
    {
        VerticePrim aux = *a;
        *a = *b;
        *b = aux;
    }
    void refaz_cima_baixo(vector<VerticePrim> &A, int k, int N)
    {
        int j;
        while (2 * k <= N)
        {
            j = 2 * k;
            if (j < N && A[j].p > A[j + 1].p)
                j++;
            if (A[k].p <= A[j].p)
                break;
            troca(&A[k], &A[j]);
            k = j;
        }
    }

public:
    void heap_constroi(vector<VerticePrim> &A, int n)
    {
        for (int k = n / 2; k >= 1; k--)
            refaz_cima_baixo(A, k, n);
    }
    VerticePrim heap_remove_minimo(vector<VerticePrim> &A, int *n)
    {
        VerticePrim menor = A[1];
        troca(&A[1], &A[*n]);
        (*n)--;
        A.pop_back();
        if (*n > 0)
            refaz_cima_baixo(A, 1, *n);
        return menor;
    }
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
        for (int i = 0; i < vertices.size(); i++)
            if (vertices[i].u == vertice)
                return i;
        return -1;
    }

    int getIdPeloDoNomeVertice(string nome)
    {
        for (int i = 0; i < vertices.size(); i++)
            if (vertices[i].nome == nome)
                return i;
        return -1;
    }

    int encontrarChefe(int i, vector<int> &pais)
    {
        if (pais[i] == i)
            return i;
        return pais[i] = encontrarChefe(pais[i], pais);
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
        cout << "Vértice " << u_input << " (" << vertices[u_input].nome << ") finalizado!\n";
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
            cout << "Vértice " << v.u << " (" << vertices[v.u].nome << ") finalizado!\n";
        }
    }

public:
    void visualizar(vector<Aresta> arestasDestacadas = {}, vector<int> nosDestacados = {}, string titulo = "Grafo")
    {
        if (vertices.empty())
        {
            cout << "\nERRO: Grafo não existe!" << endl;
            return;
        }

        stringstream ss;
        ss << "direcionado=" << (direcionado ? "sim" : "nao") << "\n"
           << numVertices << "\n";
        for (auto v : vertices)
            ss << v.u << " " << v.x << " " << v.y << " " << v.nome << "\n";
        ss << contArestas << "\n";

        if (!direcionado)
        {
            for (int i = 0; i < numVertices; i++)
                for (int j = i; j < numVertices; j++)
                    if (arestas[i][j] != -1)
                        ss << vertices[i].u << " " << vertices[j].u << " " << arestas[i][j] << "\n";
        }
        else
        {
            for (int i = 0; i < numVertices; i++)
                for (int j = 0; j < numVertices; j++)
                    if (arestas[i][j] != -1)
                        ss << vertices[i].u << " " << vertices[j].u << " " << arestas[i][j] << "\n";
        }

        // Converte destaques para JSON
        stringstream ssDestaques;
        ssDestaques << "[";
        for (size_t i = 0; i < arestasDestacadas.size(); i++)
        {
            ssDestaques << "{u:" << arestasDestacadas[i].u << ",v:" << arestasDestacadas[i].v << "}";
            if (i < arestasDestacadas.size() - 1)
                ssDestaques << ",";
        }
        ssDestaques << "]";

        stringstream ssNos;
        ssNos << "[";
        for (size_t i = 0; i < nosDestacados.size(); i++)
        {
            ssNos << nosDestacados[i];
            if (i < nosDestacados.size() - 1)
                ssNos << ",";
        }
        ssNos << "]";

        ofstream arquivoHtml("visualizacao.html");
        // HTML embutido
        arquivoHtml << R"(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
<meta charset="UTF-8"><meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Visualização )"
                    << titulo << R"(</title>
<style>
    body { font-family: 'Segoe UI', sans-serif; margin: 0; background: #f8f9fa; display: flex; flex-direction: column; height: 100vh; overflow: hidden; }
    header { background: white; padding: 10px 20px; box-shadow: 0 1px 3px rgba(0,0,0,0.1); z-index: 10; display:flex; justify-content:space-between; align-items:center;}
    #canvas-container { flex-grow: 1; position: relative; overflow: hidden; cursor: grab; }
    #canvas-container:active { cursor: grabbing; }
    canvas { display: block; background-image: radial-gradient(#e2e8f0 1px, transparent 1px); background-size: 20px 20px; }
    .legend { display: flex; gap: 15px; font-size: 0.9em;}
    .dot { width: 10px; height: 10px; display: inline-block; border-radius: 50%; margin-right: 5px;}
</style>
</head>
<body>
<header>
    <h3>)" << titulo << R"(</h3>
    <div class="legend">
        <div><span class="dot" style="background:#3b82f6"></span>Normal</div>
        <div><span class="dot" style="background:#ef4444"></span>Destaque</div>
    </div>
</header>
<div id="canvas-container"><canvas id="graphCanvas"></canvas></div>
<script>
    const rawData = `)"
                    << ss.str() << R"(`;
    const highlightEdges = )"
                    << ssDestaques.str() << R"(;
    const highlightNodes = )"
                    << ssNos.str() << R"(;

    function parseGraphData(data) {
        const lines = data.trim().split('\n').map(l => l.trim()).filter(l => l);
        // Lógica para detectar se é direcionado
        const isDirected = lines[0].toLowerCase().includes('sim');
        const numNodes = parseInt(lines[1]);
        const nodes = [];
        const edges = [];
        for (let i = 0; i < numNodes; i++) {
            const parts = lines[2 + i].split(' ');
            nodes.push({ id: parseInt(parts[0]), x: parseInt(parts[1]), y: parseInt(parts[2]), label: parts.slice(3).join(' ') });
        }
        const edgeStart = 2 + numNodes + 1;
        const numEdges = parseInt(lines[2 + numNodes]);
        for (let i = 0; i < numEdges; i++) {
            const lineIdx = edgeStart + i;
            if (lineIdx >= lines.length) break;
            const parts = lines[lineIdx].split(' ');
            edges.push({ source: parseInt(parts[0]), target: parseInt(parts[1]), weight: parseInt(parts[2]) });
        }
        return { nodes, edges, isDirected };
    }

    const graphData = parseGraphData(rawData);
    const canvas = document.getElementById('graphCanvas');
    const ctx = canvas.getContext('2d');
    const container = document.getElementById('canvas-container');
    let width, height, transform = { x: 0, y: 0, k: 1 };
    let isDragging = false, draggedNode = null, lastMouse = { x: 0, y: 0 };
    const padding = 50;

    function resize() {
        width = container.clientWidth; height = container.clientHeight;
        canvas.width = width; canvas.height = height;
        draw();
    }

    function worldToScreen(x, y) {
        const drawW = width - (padding * 2); const drawH = height - (padding * 2);
        const screenX = padding + (x / 100) * drawW; const screenY = padding + (y / 100) * drawH;
        return { x: screenX * transform.k + transform.x, y: screenY * transform.k + transform.y };
    }
    
    function screenToWorld(sx, sy) {
        const drawW = width - (padding * 2); const drawH = height - (padding * 2);
        return { 
            x: (((sx - transform.x) / transform.k - padding) / drawW) * 100,
            y: (((sy - transform.y) / transform.k - padding) / drawH) * 100
        };
    }

    function isEdgeHighlighted(u, v) {
        return highlightEdges.some(e => (e.u === u && e.v === v) || (e.u === v && e.v === u));
    }

    function draw() {
        ctx.clearRect(0, 0, width, height);
        ctx.save();
        
        graphData.edges.forEach(edge => {
            const sNode = graphData.nodes.find(n => n.id === edge.source);
            const tNode = graphData.nodes.find(n => n.id === edge.target);
            if (!sNode || !tNode) return;
            const s = worldToScreen(sNode.x, sNode.y);
            const t = worldToScreen(tNode.x, tNode.y);
            
            const highlight = isEdgeHighlighted(edge.source, edge.target);
            const color = highlight ? '#ef4444' : '#94a3b8';
            const lineWidth = (highlight ? 4 : 2) * transform.k;
            
            ctx.beginPath();
            
            if (graphData.isDirected) {
                // MATEMÁTICA DA SETA
                const dx = t.x - s.x;
                const dy = t.y - s.y;
                const angle = Math.atan2(dy, dx);
                const nodeRadius = 6 * transform.k;
                
                // Recua o ponto final para a borda do nó de destino
                const endX = t.x - nodeRadius * Math.cos(angle);
                const endY = t.y - nodeRadius * Math.sin(angle);
                
                // Desenha a linha
                ctx.moveTo(s.x, s.y);
                ctx.lineTo(endX, endY);
                ctx.strokeStyle = color;
                ctx.lineWidth = lineWidth;
                ctx.stroke();
                
                // Desenha a cabeça da seta
                const headLen = 10 * transform.k;
                ctx.beginPath();
                ctx.moveTo(endX, endY);
                ctx.lineTo(endX - headLen * Math.cos(angle - Math.PI / 6), endY - headLen * Math.sin(angle - Math.PI / 6));
                ctx.lineTo(endX - headLen * Math.cos(angle + Math.PI / 6), endY - headLen * Math.sin(angle + Math.PI / 6));
                ctx.lineTo(endX, endY);
                ctx.fillStyle = color;
                ctx.fill();

            } else {
                // Grafo NÃO direcionado (linha simples)
                ctx.moveTo(s.x, s.y);
                ctx.lineTo(t.x, t.y);
                ctx.strokeStyle = color;
                ctx.lineWidth = lineWidth;
                ctx.stroke();
            }

            // PESO DA ARESTA
            const midX = (s.x + t.x) / 2, midY = (s.y + t.y) / 2;
            
            ctx.fillStyle = '#f8f9fa'; 
            const fontSize = (highlight ? 24 : 20) * transform.k;
            ctx.font = 'bold ' + fontSize + 'px Arial';
            
            const tm = ctx.measureText(edge.weight);
            const bgPad = 2 * transform.k;
            ctx.fillRect(midX - tm.width/2 - bgPad, midY - (fontSize/2 + bgPad), tm.width + bgPad*2, fontSize + bgPad*2);
            
            ctx.fillStyle = highlight ? '#ef4444' : '#64748b'; 
            ctx.textAlign = 'center'; ctx.textBaseline = 'middle';
            ctx.fillText(edge.weight, midX, midY);
        });

        // Desenhar Nós
        graphData.nodes.forEach(node => {
            const pos = worldToScreen(node.x, node.y);
            const r = 6 * transform.k;
            const highlight = highlightNodes.includes(node.id);

            ctx.beginPath(); ctx.arc(pos.x, pos.y, r, 0, Math.PI * 2); 
            ctx.fillStyle = highlight ? '#ef4444' : '#3b82f6'; 
            ctx.fill();
            
            ctx.strokeStyle = 'white'; ctx.lineWidth = 2 * transform.k; ctx.stroke();
            ctx.fillStyle = '#1e293b'; ctx.font = `${16 * transform.k}px Arial`; ctx.textAlign = 'center';
            
            ctx.fillText(node.id + " - " + node.label, pos.x, pos.y - r - 5 * transform.k);
        });
        ctx.restore();
    }

    function getMousePos(evt) { const rect = canvas.getBoundingClientRect(); return { x: evt.clientX - rect.left, y: evt.clientY - rect.top }; }
    function getNodeAtPos(pos) {
        for (let i = graphData.nodes.length - 1; i >= 0; i--) {
            const node = graphData.nodes[i];
            const sp = worldToScreen(node.x, node.y);
            if (Math.sqrt(Math.pow(pos.x - sp.x, 2) + Math.pow(pos.y - sp.y, 2)) < 15 * transform.k) return node;
        } return null;
    }
    window.addEventListener('resize', resize);
    canvas.addEventListener('mousedown', e => {
        const pos = getMousePos(e); lastMouse = pos;
        const node = getNodeAtPos(pos);
        if (node) { draggedNode = node; isDragging = true; canvas.style.cursor = 'grabbing'; }
        else { isDragging = true; canvas.style.cursor = 'move'; }
    });
    canvas.addEventListener('mousemove', e => {
        const pos = getMousePos(e);
        if (isDragging) {
            if (draggedNode) { const wp = screenToWorld(pos.x, pos.y); draggedNode.x = wp.x; draggedNode.y = wp.y; }
            else { transform.x += pos.x - lastMouse.x; transform.y += pos.y - lastMouse.y; }
            draw();
        } else { canvas.style.cursor = getNodeAtPos(pos) ? 'pointer' : 'grab'; }
        lastMouse = pos;
    });
    canvas.addEventListener('mouseup', () => { isDragging = false; draggedNode = null; canvas.style.cursor = 'grab'; });
    canvas.addEventListener('wheel', e => {
        e.preventDefault();
        const zoom = Math.exp((e.deltaY < 0 ? 1 : -1) * 0.1);
        const mouse = getMousePos(e);
        transform.x -= (mouse.x - transform.x) * (zoom - 1);
        transform.y -= (mouse.y - transform.y) * (zoom - 1);
        transform.k *= zoom;
        draw();
    }, { passive: false });
    resize();
</script></body></html>)";
        arquivoHtml.close();
        cout << "\nVisualização gerada! Verifique o navegador." << endl;
        system("start visualizacao.html");
    }

    void importar(const char *nome_arquivo)
    {
        vertices.clear();
        arestas.clear();
        contArestas = 0;
        ifstream arq(nome_arquivo);
        if (!arq.is_open())
        {
            cout << "Erro ao abrir arquivo!";
            return;
        }
        string linha;
        getline(arq, linha);
        direcionado = (linha.find("sim") != string::npos);
        arq >> numVertices;
        for (int i = 0; i < numVertices; i++)
        {
            Vertice v;
            arq >> v.u >> v.x >> v.y;
            getline(arq, linha);
            if (!linha.empty())
                v.nome = linha.substr(1);
            vertices.push_back(v);
        }
        arq >> numArestas;
        arestas.resize(numVertices, vector<int>(numVertices, -1));
        for (int i = 0; i < numArestas; i++)
        {
            int u, v, p;
            arq >> u >> v >> p;
            inserirAresta(u, v, p);
        }
        arq.close();
        cout << "Grafo importado com sucesso!" << endl;
    }

    void vazio(int qtd, bool dir)
    {
        vertices.clear();
        arestas.clear();
        contArestas = 0;
        numVertices = qtd;
        direcionado = dir;
        for (int i = 0; i < qtd; i++)
        {
            vertices.push_back({to_string(i), i, i * 10, i * 10});
        }
        arestas.resize(numVertices, vector<int>(numVertices, -1));
        cout << "Grafo vazio criado!" << endl;
    }

    void exibirTodasAsAdjacencias() const
    {
        if (arestas.empty())
        {
            cout << "\nERRO: Grafo não existe!" << endl;
            return;
        }

        cout << "\n------------- LEGENDA -------------\n";
        for (auto &x : vertices)
            cout << "Vértice " << setw(2) << x.u << ": " << x.nome << endl;
        cout << "----------------------------------\n";

        cout << "\n------------------ MATRIZ DE ADJACÊNCIAS (Pesos) ------------------\n";
        if (arestas.empty())
            return;
        cout << "\n   ";
        for (int i = 0; i < numVertices; i++)
            cout << setw(4) << i;
        cout << "\n";
        cout << "      " << setfill('-');
        cout << setw(numVertices * 4) << "" << setfill(' ') << endl;
        for (int i = 0; i < numVertices; i++)
        {
            cout << setw(2) << i << "|";
            for (int j = 0; j < numVertices; j++)
            {
                if (arestas[i][j] != -1)
                    cout << setw(4) << arestas[i][j];
                else
                    cout << setw(4) << ".";
            }
            cout << endl;
        }
        cout << "\n-------------------------------------------------------------------" << endl;
    }

    bool consultarSeAdjacente(int u_input, int v_input)
    {
        int u = getVertice(u_input), v = getVertice(v_input);
        if (u == -1 || v == -1)
            return false;
        return arestas[u][v] != -1;
    }

    void inserirAresta(int u_input, int v_input, int p)
    {
        int u = getVertice(u_input), v = getVertice(v_input);
        if (u != -1 && v != -1)
        {
            arestas[u][v] = p;
            if (!direcionado)
                arestas[v][u] = p;
            contArestas++;
        }
        else
            cout << "\nERRO: Vértice(s) não encontrado(s)!" << endl;
    }

    void removerAresta(int u_input, int v_input)
    {
        int u = getVertice(u_input), v = getVertice(v_input);
        if (u != -1 && v != -1 && arestas[u][v] != -1)
        {
            arestas[u][v] = -1;
            if (!direcionado)
                arestas[v][u] = -1;
            contArestas--;
        }
        else
            cout << "\nERRO: Vértice(s) ou aresta não encontrado(s)!" << endl;
    }

    void editarCoordenadaDoVertice(int u_input, int x, int y)
    {
        int u = getVertice(u_input);
        if (u != -1)
            if (x >= 0 && y >= 0)
            {
                vertices[u].x = x;
                vertices[u].y = y;
                cout << "\nCoordenadas editadas com sucesso!" << endl;
            }
            else
                cout << "\nERRO: Coordenadas inseridas são inválidas!" << endl;
        else
            cout << "\nERRO: Vértice não foi encontrado!" << endl;
    }

    int primeiroAdjacenteDoVertice(int u_input)
    {
        int u = getVertice(u_input);
        if (u == -1)
            return -2;
        for (int j = 0; j < numVertices; j++)
            if (arestas[u][j] != -1)
                return vertices[j].u;
        return -1;
    }

    int proximoAdjacenteDoVertice(int u_input, int atual_input)
    {
        int u = getVertice(u_input), atual = getVertice(atual_input);
        if (u == -1 || atual == -1)
            return -2;
        for (int j = atual + 1; j < numVertices; j++)
            if (arestas[u][j] != -1)
                return vertices[j].u;
        return -1;
    }

    void listaCompletaDeAdjacentesDoVertice(int u_input)
    {
        int u = getVertice(u_input);
        if (u == -1)
        {
            cout << "\nERRO: Vértice não foi encontrado!" << endl;
            return;
        }
        int qtd = 0;
        string adj = "Adjacentes de " + to_string(u) + ": ";
        for (int j = 0; j < numVertices; j++)
            if (arestas[u][j] != -1)
            {
                qtd++;
                adj += to_string(vertices[j].u) + " - ";
            }
        if (qtd == 0)
            cout << "\nVértice não possui adjacentes!" << endl;
        else
            cout << adj << endl;
    }

    void exportar(const char *nome)
    {
        if (vertices.empty())
        {
            cout << "\nERRO: Grafo não existe!" << endl;
            return;
        }

        ofstream arq(nome);
        if (!arq.is_open())
        {
            cout << "\nERRO: Não foi possivel criar o arquivo!" << endl;
            return;
        }

        arq << "direcionado=" << (direcionado ? "sim" : "nao") << "\n"
            << numVertices << "\n";
        for (auto v : vertices)
            arq << v.u << " " << v.x << " " << v.y << " " << v.nome << "\n";
        arq << contArestas << "\n";
        if (!direcionado)
        {
            for (int i = 0; i < numVertices; i++)
                for (int j = i; j < numVertices; j++)
                    if (arestas[i][j] != -1)
                        arq << vertices[i].u << " " << vertices[j].u << " " << arestas[i][j] << "\n";
        }
        else
        {
            for (int i = 0; i < numVertices; i++)
                for (int j = 0; j < numVertices; j++)
                    if (arestas[i][j] != -1)
                        arq << vertices[i].u << " " << vertices[j].u << " " << arestas[i][j] << "\n";
        }
        arq.close();
    }

    void editarNomeVertice(int u_input)
    {
        int u = getVertice(u_input);
        if (u != -1)
        {
            cout << "Novo nome: ";
            cin >> vertices[u].nome;
        }
    }

    void buscaEmProfundidade()
    {
        int tempo = 0;
        vector<ControlBuscaEmProfu> c(numVertices);
        for (int i = 0; i < numVertices; i++)
        {
            c[i].u = i;
            c[i].cor = 'b';
            c[i].antecessor = -1;
        }
        for (int i = 0; i < numVertices; i++)
            if (c[i].cor == 'b')
                visitaEmProfundidade(i, &tempo, c);

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
        if (vertices.empty())
        {
            cout << "\nERRO: Grafo não existe!" << endl;
            return;
        }
        while (!fila.empty())
            fila.pop();

        vector<ControlBuscaEmLargura> c(numVertices);
        for (int i = 0; i < numVertices; i++)
        {
            c[i].u = i;
            c[i].antecessor = -1;
            c[i].cor = 'b';
            c[i].distancia = INT_MAX;
        }
        for (int i = 0; i < numVertices; i++)
            if (c[i].cor == 'b')
                visitaEmLargura(i, c);

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

    void arvoreMininmaKruskal()
    {
        if (vertices.empty())
        {
            cout << "\nERRO: Grafo não existe!" << endl;
            return;
        }
        HeapKruskal heap;
        vector<Aresta> S;
        int pesoTotal = 0;
        vector<int> pais(numVertices);
        vector<int> nivel(numVertices, 0);
        for (int i = 0; i < numVertices; i++)
            pais[i] = i;

        vector<Aresta> A;
        A.push_back({-1, -1, -1});

        for (int i = 0; i < numVertices; i++)
        {
            for (int j = (direcionado ? 0 : i); j < numVertices; j++)
            {
                if (arestas[i][j] != -1)
                    A.push_back({i, j, arestas[i][j]});
            }
        }

        int n = A.size() - 1;
        heap.heap_constroi(A, n);

        cout << "\n--- EXECUÇÃO DO ALGORITMO DE KRUSKAL ---\n";
        while (n >= 1)
        {
            Aresta menor = heap.heap_remove_minimo(A, &n);
            int paiU = encontrarChefe(menor.u, pais);
            int paiV = encontrarChefe(menor.v, pais);

            if (paiU != paiV)
            {
                S.push_back(menor);
                printf("Aresta: (%d, %d) | Peso: %d\n", menor.u, menor.v, menor.p);
                pesoTotal += menor.p;
                if (nivel[paiU] > nivel[paiV])
                    pais[paiV] = paiU;
                else
                {
                    pais[paiU] = paiV;
                    if (nivel[paiU] == nivel[paiV])
                        nivel[paiV]++;
                }
            }
        }
        cout << "----------------------------------------" << endl;
        cout << "Peso Total da Árvore Geradora Mínima: " << pesoTotal << endl;

        char op;
        cout << "\nDeseja visualizar a Árvore Mínima? (s/n): ";
        cin >> op;
        if (op == 's' || op == 'S')
        {
            visualizar(S, {}, "Árvore Geradora Mínima (Kruskal)");
        }
    }

    void arvoreMininaPrim()
    {
        if (vertices.empty())
        {
            cout << "\nERRO: Grafo não existe!" << endl;
            return;
        }
        HeapPrim heap;
        vector<VerticePrim> v;
        v.push_back({-1, -1, -1});

        for (int i = 0; i < numVertices; i++)
            v.push_back({vertices[i].u, INT_MAX, -1});
        v[1].p = 0;
        int n = v.size() - 1;
        heap.heap_constroi(v, n);

        vector<Aresta> arestasSolucao;

        cout << "\n---- EXECUÇÃO DO ALGORITMO DE PRIM -----\n";
        while (n >= 1)
        {
            VerticePrim u_removido = heap.heap_remove_minimo(v, &n);
            if (u_removido.antecessor != -1)
            {
                arestasSolucao.push_back({u_removido.antecessor, u_removido.u, u_removido.p});
            }

            for (int k = 1; k <= n; k++)
            {
                int v_id = v[k].u;
                int indiceRealV = getVertice(v_id);
                int indiceRealU = getVertice(u_removido.u);

                if (arestas[indiceRealU][indiceRealV] != -1)
                {
                    int peso = arestas[indiceRealU][indiceRealV];
                    if (peso < v[k].p)
                    {
                        v[k].p = peso;
                        v[k].antecessor = u_removido.u;
                    }
                }
            }
            heap.heap_constroi(v, n);
        }

        int pesoTotal = 0;
        for (auto &a : arestasSolucao)
        {
            printf("Aresta: (%2d, %2d) | Peso: %2d\n", a.u, a.v, a.p);
            pesoTotal += a.p;
        }
        cout << "-----------------------------------------" << endl;
        cout << "Peso Total da Árvore Geradora Mínima: " << pesoTotal << endl;

        char op;
        cout << "\nDeseja visualizar a Árvore Mínima? (s/n): ";
        cin >> op;
        if (op == 's' || op == 'S')
        {
            visualizar(arestasSolucao, {}, "Árvore Geradora Mínima (Prim)");
        }
    }

    void dijkstra(string nomeVertice1, string nomeVertice2)
    {
        if (vertices.empty())
        {
            cout << "\nERRO: Grafo não existe!" << endl;
            return;
        }
        int u_input = getIdPeloDoNomeVertice(nomeVertice1), v_input = getIdPeloDoNomeVertice(nomeVertice2);

        if (u_input == -1 || v_input == -1)
        {
            cout << "\nERRO: Vértice(s) não encontrado(s)!" << endl;
            return;
        }
        HeapPrim heap;
        vector<VerticePrim> v;
        vector<VerticePrim> v2;
        stack<int> S;
        v.push_back({-1, -1, -1});

        for (int i = 0; i < numVertices; i++)
        {
            v.push_back({vertices[i].u, INT_MAX, -1});
            v2.push_back(v[i]);
        }
        v[u_input].p = 0;
        int n = v.size() - 1;
        heap.heap_constroi(v, n);

        cout << "\n--- EXECUÇÃO DO ALGORITMO DJKSTRA ---\n";
        while (n >= 1)
        {
            VerticePrim u_removido = heap.heap_remove_minimo(v, &n);

            for (int k = 1; k <= n; k++)
            {
                int v_id = v[k].u;
                int indiceRealV = getVertice(v_id);
                int indiceRealU = getVertice(u_removido.u);

                if (arestas[indiceRealU][indiceRealV] != -1)
                {
                    int peso = arestas[indiceRealU][indiceRealV] + v[indiceRealU].p;
                    if (peso < v[k].p)
                    {
                        v[k].p = peso;
                        v[k].antecessor = u_removido.u;
                    }
                }
            }
            heap.heap_constroi(v, n);
        }

        cout << "Caminho do vértice " << u_input << " (" << nomeVertice1 << ")";
        cout << " para o vértice " << v_input << " (" << nomeVertice2 << "): ";
        int i = v_input;
        if (v2[i].u != u_input)
            while (true)
            {
                if (v[i].antecessor != -1)
                {
                    cout << i << " --> ";
                    i = v[i].antecessor;
                }
                else
                    break;
            }
        else
            cout << i;

        cout << "\n----------------------------------------" << endl;
        cout << "Peso Total da Árvore Geradora Mínima: " << v[v_input].p << endl;
        /*
        char op;
        cout << "\nDeseja visualizar a Árvore Mínima? (s/n): ";
        cin >> op;
        if (op == 's' || op == 'S')
        {
            visualizar(arestasSolucao, {}, "Árvore Geradora Mínima (Prim)");
        }
        */
    }
};