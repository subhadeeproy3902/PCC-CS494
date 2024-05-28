#include<stdio.h>

void printSolution(int n, int path[])
{
  printf("Solution exists. Following is a Hamiltonian Cycle : \n");
  for(int i=0; i<n; i++)
  {
    printf("%d  ",path[i]);
  }
  printf("%d",path[0]);
  printf("\n");
}

int isSafe(int v, int n, int graph[n][n], int path[], int pos)
{
  if(graph[path[pos-1]][v] == 0)
    return 0;

  for(int i=0; i<pos; i++)
  {
    if(path[i] == v)
      return 0;
  }

  return 1;
}

int hamcycleUtil(int n, int graph[n][n], int path[], int pos)
{
  if(pos == n)
  {
    if(graph[path[pos-1]][path[0]] == 0)
      return 0;
    else
      return 1;
  }

  for(int v=1; v<n; v++)
  {
    if(isSafe(v, n, graph, path, pos))
    {
      path[pos] = v;
      if(hamcycleUtil(n, graph, path, pos + 1) == 1)
        return 1;
      path[pos] = -1;
    }
  }
  return 0;
}

int hamcycle(int n, int graph[n][n])
{
  int path[n];
  for(int i=0; i<n; i++)
  {
    path[i] = -1;
  }
  path[0] = 0;
  if(hamcycleUtil(n, graph, path, 1) == 0)
  {
    printf("Solution does not exist\n");
    return 0;
  }
  printSolution(n, path);
  return 1;
}

int main()
{
  int n;
  printf("Enter the no. of vertices : \n");
  scanf("%d", &n);
  int graph[n][n];
  printf("Enter the Adjacency Matrix : \n");
  for(int i=0; i<n; i++)
  {
    for(int j=0; j<n; j++)
    {
      scanf("%d",&graph[i][j]);
    }
  }
  hamcycle(n, graph);
  return 0;
}