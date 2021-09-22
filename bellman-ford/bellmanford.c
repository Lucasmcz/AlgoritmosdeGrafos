// Bellman Ford Algorithm in C

#include <stdio.h>
#include <stdlib.h>

#define INFINITY 99999

//Struct que Arestas que foi construida para formar o Grafo
struct Edge {
  int u;  //Vertice Inicial
  int v;  //Vertice Final
  int w;  //Peso
};

//GRAFO
struct Graph {
  int V;//Numero de Vertices
  int E;//Numero de Arestas
  struct Edge *edge;//Array de Arestas que foi utilizada a Struct Arestas que foi feita anteriormente
};

void bellmanford(struct Graph *g, int source);//O GRAFO G , e o vertice Source(Inicial)
void display(int arr[], int size);//Feito para printar as distancia depois do algoritmo completo

int main(void) {

  FILE *arq;
  int vertices;
  int arestas;
  arq = fopen("entrada1.txt","r+");
  if(arq == NULL)
  {
    printf("ERRO");
  }
  else
  {
    fscanf(arq,"%d %d",&vertices,&arestas);
      //printf("%d %d\n",vertices,arestas);
  }

  struct Graph *g = (struct Graph *)malloc(sizeof(struct Graph));
  g->V = vertices;
  g->E = arestas;

  //array of edges for graph
  g->edge = (struct Edge *)malloc(g->E * sizeof(struct Edge));

  //------- adding the edges of the graph
  /*
		edge(u, v)
		where 	u = start vertex of the edge (u,v)
				v = end vertex of the edge (u,v)

		w is the weight of the edge (u,v)
	*/

  for(int i = 0;i < arestas;i++)
  {
    fscanf(arq,"%d %d %d",&g->edge[i].u,&g->edge[i].v,&g->edge[i].w);
    //printf("\n%d %d %d\n", g->edge[i].u,g->edge[i].v,g->edge[i].w);
  }


  bellmanford(g, 0);  //0 is the source vertex

  return 0;
}

void bellmanford(struct Graph *g, int source) {
  FILE *arq1;
  //variables
  int i, j, u, v, w;

  //total vertex in the graph g
  int tV = g->V;

  //total edge in the graph g
  int tE = g->E;

  //distance array
  //size equal to the number of vertices of the graph g
  int d[tV];

  //predecessor array
  //size equal to the number of vertices of the graph g
  int p[tV];

  //step 1: fill the distance array and predecessor array
  for (i = 0; i < tV; i++) {
    d[i] = INFINITY;
    p[i] = 0;
  }

  //mark the source vertex
  d[source] = 0;

  //step 2: relax edges |V| - 1 times
  for (i = 1; i <= tV - 1; i++) {
    for (j = 0; j < tE; j++) {
      //get the edge data
      u = g->edge[j].u;
      v = g->edge[j].v;
      w = g->edge[j].w;

      if (d[u] != INFINITY && d[v] > d[u] + w) {
        d[v] = d[u] + w;
        p[v] = u;
      }
    }
  }

  //step 3: detect negative cycle
  //if value changes then we have a negative cycle in the graph
  //and we cannot find the shortest distances
  for (i = 0; i < tE; i++) {
    u = g->edge[i].u;
    v = g->edge[i].v;
    w = g->edge[i].w;
    if (d[u] != INFINITY && d[v] > d[u] + w) {
      printf("Negative weight cycle detected!\n");
      return;
    }
  }

  //No negative weight cycle found!
  //print the distance and predecessor array
  printf("Distance array: ");
  display(d, tV);
  arq1 = fopen("saida.txt","w");
  if(arq1 == NULL)
  {
    puts("Erro");
  }
  else
  {
    for(int i = 0;i < 5;i++)
    {
      fprintf(arq1,"%d ",d[i]);
    }

  }
}

void display(int arr[], int size) {
  int i;
  for (i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}
