#include <stdio.h>
#include <stdlib.h>

void merge(int arr[][3], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1][3], R[n2][3];

    for (int i = 0; i < n1; i++)
        for (int j = 0; j < 3; j++)
            L[i][j] = arr[l + i][j];
    for (int i = 0; i < n2; i++)
        for (int j = 0; j < 3; j++)
            R[i][j] = arr[m + 1 + i][j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i][2] <= R[j][2]) {
            for (int t = 0; t < 3; t++)
                arr[k][t] = L[i][t];
            i++;
        } else {
            for (int t = 0; t < 3; t++)
                arr[k][t] = R[j][t];
            j++;
        }
        k++;
    }

    while (i < n1) {
        for (int t = 0; t < 3; t++)
            arr[k][t] = L[i][t];
        i++;
        k++;
    }

    while (j < n2) {
        for (int t = 0; t < 3; t++)
            arr[k][t] = R[j][t];
        j++;
        k++;
    }
}

void mergeSort(int arr[][3], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void makeSet(int parent[], int rank[], int n)
{
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findParent(int parent[], int component)
{
    if (parent[component] == component)
        return component;

    return parent[component] = findParent(parent, parent[component]);
}

void unionSet(int u, int v, int parent[], int rank[], int n)
{
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v]) {
        parent[u] = v;
    }
    else if (rank[u] > rank[v]) {
        parent[v] = u;
    }
    else {
        parent[v] = u;
        rank[u]++;
    }
}

void kruskalAlgo(int n, int edge[n][3])
{
    mergeSort(edge, 0, n - 1);

    int parent[n];
    int rank[n];

    makeSet(parent, rank, n);

    int minCost = 0;

    printf("Following are the edges in the constructed MST\n");
    for (int i = 0; i < n; i++) {
        int v1 = findParent(parent, edge[i][0]);
        int v2 = findParent(parent, edge[i][1]);
        int wt = edge[i][2];

        if (v1 != v2) {
            unionSet(v1, v2, parent, rank, n);
            minCost += wt;
            printf("%d -- %d == %d\n", edge[i][0], edge[i][1], wt);
        }
    }

    printf("Minimum Cost Spanning Tree: %d\n", minCost);
}

int main()
{
    int n;
    printf("Enter the number of edges: ");
    scanf("%d", &n);

    int edge[n][3];
    printf("Enter the edges in the format (vertex1 vertex2 weight):\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &edge[i][0], &edge[i][1], &edge[i][2]);
    }

    kruskalAlgo(n, edge);

    return 0;
}
