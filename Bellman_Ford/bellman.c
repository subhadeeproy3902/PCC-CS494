#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100

int vertices, edges;

void bellmanFord(int graph[edges][3], int edges, int distance[], int predecessor[], int source)
{
    distance[source] = 0;
    int count;
    for (count = 1; count < vertices; count++)
    {
        int i, u, v, wt;
        for (i = 0; i < edges; i++)
        {
            u = graph[i][0];
            v = graph[i][1];
            wt = graph[i][2];
            if (distance[u] != INT_MAX && (distance[u] + wt) < distance[v])
            {
                distance[v] = distance[u] + wt;
                predecessor[v] = u; // Store predecessor of v
            }
        }
    }
}

void printPath(int predecessor[], int vertex, int source)
{
    if (vertex == source)
    {
        printf("%d", vertex);
        return;
    }
    printPath(predecessor, predecessor[vertex], source);
    printf(" -> %d", vertex);
}

void printDistance(int distance[], int predecessor[], int source)
{
    int i;
    printf("\nThe Shortest Paths from Source %d are : \n", source);
    printf("Vertex\tDistance\tPath\n");
    for (i = 0; i < vertices; i++)
    {
        if (i == source)
            continue;
        printf("%d     \t%d\t\t", i, distance[i]);
        printPath(predecessor, i, source);
        printf("\n");
    }
}

int main()
{
    printf("Enter the no. of Vertices : ");
    scanf("%d", &vertices);
    int distance[MAX_VERTICES];
    int predecessor[MAX_VERTICES];
    int source, i;
    printf("Enter no. of Edges : ");
    scanf("%d", &edges);
    int graph[edges][3];
    printf("Enter the Adjacency List (Source, Destination and Cost) : \n");
    for (i = 0; i < edges; i++)
        scanf("%d %d %d", &graph[i][0], &graph[i][1], &graph[i][2]);
    for (i = 0; i < vertices; i++)
    {
        distance[i] = INT_MAX;
        predecessor[i] = -1; // Initialize predecessor array
    }
    printf("Enter the Source vertex : ");
    scanf("%d", &source);
    bellmanFord(graph, edges, distance, predecessor, source);
    printDistance(distance, predecessor, source);
    return 0;
} 