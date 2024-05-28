#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

int minKey(int key[], bool mstSet[], int n)
{
  int min = INT_MAX, min_index;
  for(int v=0; v<n; v++)
  {
    if(!mstSet[v] && key[v] < min)
    {
      min = key[v];
      min_index = v;
    }
  }
  return min_index;
}

void printMST(int parent[], int n, int graph[n][n])
{
  int cost = 0;
  printf("Edge\tWeight\t\n");
  for(int i=1; i<n; i++)
  {
    printf("%d - %d\t%d",parent[i], i, graph[i][parent[i]]);
    printf("\n");
    cost = cost + graph[i][parent[i]];
  }
  printf("Min. cost is %d", cost);

}

void primMST(int n, int graph[n][n])
{
  int parent[n], key[n];
  bool mstSet[n];
  for(int i=0; i<n; i++)
  {
    key[i] = INT_MAX;
    mstSet[i] = false;
  }
  key[0] = 0;
  parent[0] = -1;

  for(int count = 0; count <n-1; count++)
  {
    int u = minKey(key, mstSet, n);
    mstSet[u] = true;

    for(int v=0; v<n; v++)
    {
      if(graph[u][v] && !mstSet[v] && graph[u][v] < key[v])
      {
        key[v] = graph[u][v];
        parent[v] = u;
      }
    }
  }
  printMST(parent, n, graph);
}

int main()
{
  int n;
  printf("Enter the no. of vertices : \n");
  scanf("%d",&n);
  int graph[n][n];
  printf("Enter the Adjacency Matrix : \n");
  for(int i=0; i<n; i++)
  {
    for(int j=0; j<n; j++)
    {
      scanf("%d",&graph[i][j]);
    }
  }
  primMST(n, graph);
  return 0;
}