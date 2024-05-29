#include<stdio.h>
#include<stdbool.h>

void dfs(int V, int graph[V][V], bool visited[], int s)
{
  visited[s] = true;
  printf("%d ",s);
  for(int adjacent=0; adjacent<V; adjacent++)
  {
    if(graph[s][adjacent] && !visited[adjacent])
      dfs(V, graph, visited, adjacent);
  }
}

int main()
{
  int V, source;
  printf("Enter the no. of vertices : \n");
  scanf("%d",&V);
  int graph[V][V];
  printf("Enter the Adjacency Matrix : \n");
  for(int i=0; i<V; i++)
  {
    for(int j=0; j<V; j++)
    {
      scanf("%d",&graph[i][j]);
    }
  }
  bool visited[V];
  for(int i=0; i<V; i++)
  {
    visited[i] = false;
  }
  printf("Enter the source vertex : \n");
  scanf("%d",&source);
  printf("Required DFS is : \n");
  dfs(V, graph, visited, source);
  return 0;
}