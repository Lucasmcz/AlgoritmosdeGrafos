#include <iostream>
#include <string>
#include <climits>

using namespace std;

// classe que guarda o grafo
class Graph{

    public:
        int number_vertices;
        int **edges;
        // constroi o grafo com V vertices e E arestas
        Graph(int V){
            this->number_vertices = V;
            this->edges = new int *[V];
            for(int i = 0; i < V; i++){
                this->edges[i] = new int[V];
                for(int j = 0; j < V; j++) this->edges[i][j] = INT_MAX;
                this->edges[i][i] = 0;
            }
        }

        // adiciona uma dada aresta ao grafo
        void addEdge(int src, int dst, int weight){
            this->edges[src][dst] = weight;
        }
};

void print_distance(int distance[], int V)
{
    cout << "\nA matrix de distancia para o F-W" << endl;
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if(distance[i*V+j] != INT_MAX)
                cout << distance[i*V+j] << "\t";
            else
                cout << "INF" << "\t";
        }
        cout << endl;
    }
}

void F_W(Graph graph)
{
    int V = graph.number_vertices;
    int dist[V][V];
    // incializa a distancia
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            dist[i][j] = graph.edges[i][j];
        }
    }

    for(int k = 0; k < V; k++){
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++)
                if(dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
        }
    }
    // vai converter a matrix em um array
    int dist1[V*V];
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            dist1[i*V+j] = dist[i][j];
        }
    }

    print_distance(dist1, V);
}

// funcao principal

int main()
{
    int V, E;
    int src, dst, weight;
    cout<< "Digite o numero de vertices: ";
    cin >> V;
    cout<< "Digite o numero de arestas: ";
    cin >> E;
    Graph G(V);
    for(int i = 0; i < E; i++){
        cout<< "\nAresta " << i + 1 << "\nDigite a fonte: ";
        cin >> src;
        cout << "Digite o destino: ";
        cin >> dst;
        cout << "Digite o peso: ";
        cin >> weight;
        G.addEdge(src, dst, weight);
    }

    F_W(G);

    return 0;
}

/* input:
6 8
0 1 5
0 2 4
0 3 2
0 5 6
1 3 1
1 4 7
2 4 6
3 5 1

output:
A matrix de distancia para o F-W
0       INF     INF     INF     INF     INF
INF     0       5       4       2       10
INF     INF     0       INF     1       7
INF     INF     INF     0       INF     6
INF     INF     INF     INF     0       INF
INF     INF     INF     INF     INF     0

*\
