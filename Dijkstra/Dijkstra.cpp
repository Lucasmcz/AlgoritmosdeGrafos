/*
Implementation Dijkstra Algorithm with Priority Queue
Teacher: Rian Gabriel
Class: Graph Theory
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <queue>
#include <utility>
#define MAX_V 9999
#define INF 9999

using namespace std;
// Info about the arcs
typedef struct
{
    int v;
    int weight; // Weight
}TAdj;

vector <TAdj> adj[MAX_V]; // adjacent list
int degree[MAX_V];

void initialize_Graph(int qtdVertex)
{
    memset(degree, 0, sizeof(degree));
    for (int i = 0; i < qtdVertex; i++){
        adj[i].clear();
    }
}
// create arc of A to B with weight w
void arc(int A, int B, int w)
{
    TAdj aux;
    aux.v = B;
    aux.weight = w;
    degree[A]++;
    adj[A].push_back(aux);
}

int dist[MAX_V];
int pred[MAX_V]; // stores predecessor of each vertex
// Dijkstra algorithm
void Dijkstra(int src, int vertices)
{
    priority_queue< pair< int, int > > heap; // distance and vertex
    vector<int> dist(vertices, INF);
    int s, t, w;
    memset(pred,-1, sizeof(pred));
    // make the distance of src equal 0
    heap.push(make_pair(dist[src] = 0, src));
    while(!heap.empty()){
        s = heap.top().second;
        heap.pop();
        for(int i = 0; i < degree[s]; i++){
            t = adj[s][i].v;
            w = adj[s][i].weight;
            if(dist[s] + w < dist[t]){
                dist[t] = dist[s] + w;
                pred[t] = s;
                heap.push(make_pair(-dist[t], t));
            }
        }
    }
    cout << "\nVertex Distance from the source\n";
    for (int i = 0; i < vertices; i++)
    {
        cout << "\t\n" << i << " " << dist[i] << endl;
    }
}

int main()
{
    int qtdVertex, arcs, A, B, w, src, vertices;
    cout << "Enter with number of vertices: ";
    cin >> qtdVertex;
    cout << "Enter with number of arcs: ";
    cin >> arcs;
    vector <TAdj> adj[MAX_V];
    initialize_Graph(qtdVertex);
    for(int i = 0; i < arcs; i++){
        cout <<"\nArcs " << i + 1 << "\nEnter the source: ";
        cin >> A;
        cout << "Destination: ";
        cin >> B;
        cout << "Enter with weights: ";
        cin >> w;
        arc(A, B, w);
    }
    cout << "Enter the initial vertex: ";
    cin >> src;
    Dijkstra(src, qtdVertex);
}

/*
INTPUT:

Enter with number of vertices: 6
Enter with number of arcs: 8
Arcs 1
Enter the source: 1
Destination: 2
Enter with weights: 5
Arcs 2
Enter the source: 1
Destination: 3
Enter with weights: 4
Arcs 3
Enter the source: 1
Destination: 4
Enter with weights: 2
Arcs 4
Enter the source: 1
Destination: 6
Enter with weights: 6
Arcs 5
Enter the source: 2
Destination: 4
Enter with weights: 1
Arcs 6
Enter the source: 2
Destination: 5
Enter with weights: 7
Arcs 7
Enter the source: 3
Destination: 5
Enter with weights: 6
Arcs 8
Enter the source: 4
Destination: 6
Enter with weights: 1
Enter the initial vertex: 1

OUTPUT:

Vertex Distance from the source
0 9999
1 0
2 5
3 4
4 2
5 10
*/