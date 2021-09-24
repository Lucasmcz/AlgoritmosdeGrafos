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
    FILE* arch1 = fopen("out.txt", "w");
    if(arch1 == NULL){
        printf("Error");
        exit(1);
    }
    else{
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                if(distance[i*V+j] != INT_MAX)
                    fprintf(arch1, "%d ", distance[i*V+j]);
                else
                    // cout << "INF" << "\t";
                    fprintf(arch1, "INF ");
            }
        }
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
    int V, E, src, dst, weight;
    FILE* arch = fopen("in.txt","r+");
    if(arch == NULL){
        printf("Error");
        exit(1);
    }
    else{
        fscanf(arch,"%d %d", &V, &E);
        Graph G(V);
        for(int i = 0; i < E; i++){
            fscanf(arch,"%d %d %d", &src, &dst, &weight);
            G.addEdge(src, dst, weight);
        }
        F_W(G);
    }
    return 0;
}
