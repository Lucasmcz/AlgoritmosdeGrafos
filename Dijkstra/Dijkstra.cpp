/*
Implementation Dijkstra Algorithm with Priority Queue
Teacher: Rian Gabriel
Course: Graph Theory
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <queue>
#include <utility>

#define MAX_V 99999
#define INF 99999

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
    FILE* arch1 = fopen("out.txt", "w");
    if(arch1 == NULL){
        cout << "ERROR" << endl;
        exit(1);
    }
    else{
        for (int i = 1; i <= vertices; i++)
        {
            fprintf(arch1, "%d:%d ", i, dist[i]);
        }
    }
}

int main()
{
    int qtdVertex, arcs, A, B, w, src, vertices;
    vector <TAdj> adj[MAX_V];
    initialize_Graph(qtdVertex);
    FILE* arch = fopen("in.txt", "r+");
    if(arch == NULL){
        cout << "ERROR" << endl;
        exit(1);
    }
    else{
        fscanf(arch,"%d %d", &qtdVertex, &arcs);
        for(int i = 0; i < arcs; i++){
            fscanf(arch,"%d %d %d", &A, &B, &w);
            arc(A, B, w);
        }
        fscanf(arch, "%d", &src);
    }
    Dijkstra(src, qtdVertex);

    return 0;
}
