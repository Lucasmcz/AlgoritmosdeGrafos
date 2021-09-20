//Ford - Fulkerson algorith in C
//steps
/*
1-Inicialize o fluxo em todas os vertices para 0.
2-Enquanto há  um caminho de aumento entre a origem e o coletor, adicione esse caminho ao fluxo.
3-Aumente o grafo residual


*/
#include <stdio.h>

#define MAX_NODES 1000
#define O 1000000000

int n;
int e;
int capacity[MAX_NODES][MAX_NODES];
int flow[MAX_NODES][MAX_NODES];
int color[MAX_NODES];
int pred[MAX_NODES];

int min(int x, int y) //Minimo entre 2 inteiros
{
  return x < y ? x : y;
}

int head, tail;
int q[MAX_NODES + 2];

void enqueue(int x) {
  q[tail] = x;
  tail++;
  color[x] = 1;
}

int dequeue() {
  int x = q[head];
  head++;
  color[x] = 2;
  return x;
}

//Usando BFS como um algoritmo de busca
int bfs(int start, int target) {
  int u, v;
  for (u = 0; u < n; u++) {
    color[u] = 0;
  }
  head = tail = 0;
  enqueue(start);
  pred[start] = -1;
  while (head != tail) {
    u = dequeue();
    for (v = 0; v < n; v++) {
      if (color[v] == 0 && capacity[u][v] - flow[u][v] > 0) {
        enqueue(v);
        pred[v] = u;
      }
    }
  }
  return color[target] == 2;
}

// Aplicando algoritmo fordfulkerson
int fordFulkerson(int source, int sink) {
  int i, j, u;
  int max_flow = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      flow[i][j] = 0;
    }
  }

  // Atualizando os valores residuais das arestas
  while (bfs(source, sink)) {
    int increment = O;
    for (u = n - 1; pred[u] >= 0; u = pred[u]) {
      increment = min(increment, capacity[pred[u]][u] - flow[pred[u]][u]);
    }
    for (u = n - 1; pred[u] >= 0; u = pred[u]) {
      flow[pred[u]][u] += increment;
      flow[u][pred[u]] -= increment;
    }
    // Adicionando os fluxos de caminho
    max_flow += increment;
  }
  return max_flow;
}


int main()
{
  FILE *arq;
  int vertices;
  int arestas;
  arq = fopen("entrada.txt","r+");
  if(arq == NULL)
  {
    printf("Erro");
  }
  else
  {
    puts("Arquivo aberto com sucesso");
    fscanf(arq,"%d %d",&vertices,&arestas);
    printf("\nArestas:%d Vertices:%d",arestas,vertices);
    n = vertices;
    e = arestas;
    int s = 0, t = n-1;
    //printf("\nArestas:%d Vertices:%d",arestas,vertices);
    int grafos_completo[arestas][arestas];


    //printf("\n%d %d",arestas,vertices);---Vai
    for(int i = 0;i < vertices;i++)
    {
      for(int j = 0;j < vertices;i++)
      {
        grafos_completo[i][j] = 0;
      }
    }

    for(int i = 0;i < arestas;i++)
    {
      int primeiro,segundo,weight;
      fscanf(arq,"%d %d %d",&primeiro,&segundo,&weight);
      grafos_completo[primeiro][segundo] = weight;
      capacity[primeiro][segundo] = weight;
      printf("\n[%d][%d] = %d",primeiro,segundo,capacity[primeiro][segundo]);
    }



  printf("\nMax Flow: %d\n", fordFulkerson(s,t));
}
}
