#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define MAX 100

void print(int parent[], int v, int graph[][v], char vertices[])
{
    printf("\nEdge\t\tWeight\n");
    for (int i = 1; i < v; i++)
    {
        printf("%c-%c\t\t%d\n", vertices[parent[i]], vertices[i], graph[i][parent[i]]);
    }
}

int minkey(int key[], bool mstSet[], int v)
{
    int min = INT_MAX, min_index = -1;
    for (int i = 0; i < v; i++)
    {
        if (!mstSet[i] && key[i] < min)
        {
            min = key[i];
            min_index = i;
        }
    }
    return min_index;
}

void prim(int v, int graph[][v], char vertices[])
{
    int parent[v];
    int key[v];
    bool mstSet[v];

    for (int i = 0; i < v; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    parent[0] = -1;
    key[0] = 0;

    for (int count = 0; count < v - 1; count++)
    {
        int u = minkey(key, mstSet, v);
        if (u == -1)
        {
            printf("Error: Graph is not connected.\n");
            return;
        }

        mstSet[u] = true;

        for (int i = 0; i < v; i++)
        {
            if (graph[u][i] && !mstSet[i] && graph[u][i] < key[i])
            {
                parent[i] = u;
                key[i] = graph[u][i];
            }
        }
    }

    print(parent, v, graph, vertices);
}

int main()
{
    int v;

    printf("\nEnter the number of vertices:");
    scanf("%d", &v);

    char vertices[v];
    int graph[v][v];

    printf("\nEnter the name of vertices in order (Alphabet):\n");
    getchar(); // Clear input buffer

    for (int i = 0; i < v; i++)
    {
        printf("Vertex %d: ", i);
        scanf(" %c", &vertices[i]);
    }

    printf("\nEnter the adjacency matrix:\n");
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    prim(v, graph, vertices);

    return 0;
}

