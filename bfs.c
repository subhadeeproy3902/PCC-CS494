#include<stdio.h>
#include<stdbool.h>

void bfs(int V, int graph[V][V], int s)
{
  bool visited[V];
  for(int i=0; i<V; i++)
  {
    visited[i] = false;
  }
  int queue[V];
  int front = 0, rear = 0;
  visited[s] = true;
  queue[rear++] = s;
  while(front != rear)
  {
    s = queue[front++];
    printf("%d ",s);
    for(int adjacent=0; adjacent<V; adjacent++)
    {
      if(graph[s][adjacent] && !visited[adjacent])
      {
        visited[adjacent] = true;
        queue[rear++] = adjacent;
      }
    }
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
  printf("Enter the source vertex : \n");
  scanf("%d",&source);
  printf("Required BFS is : \n");
  bfs(V, graph, source);
  return 0;
}