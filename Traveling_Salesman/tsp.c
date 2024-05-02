#include <stdio.h>
#include <limits.h>
#define V 4 

int min(int a, int b) {
    return (a < b) ? a : b;
}

int tsp(int graph[V][V], int mask, int pos, int dp[V][1 << V]) {
    if (mask == (1 << V) - 1) {
        return graph[pos][0]; 
    }
    if (dp[pos][mask] != -1) {
        return dp[pos][mask];
    }
    int min_cost = INT_MAX;
    for (int city = 0; city < V; city++) {
        if (!(mask & (1 << city)) && graph[pos][city]) {
            int new_cost = graph[pos][city] + tsp(graph, mask | (1 << city), city, dp);
            min_cost = min(min_cost, new_cost);
        }
    }
    return dp[pos][mask] = min_cost;
}

void printPath(int graph[V][V], int dp[V][1 << V]) {
    int start = 0;
    int mask = 1;
    printf("Optimal Path: %d ", start + 1);
    while (mask != (1 << V) - 1) {
        int min_cost = INT_MAX;
        int next;
        for (int city = 0; city < V; city++) {
            if (!(mask & (1 << city)) && graph[start][city]) {
                int new_cost = graph[start][city] + dp[city][mask | (1 << city)];
                if (new_cost < min_cost) {
                    min_cost = new_cost;
                    next = city;
                }
            }
        }
        printf("-> %d ", next + 1);
        mask |= (1 << next);
        start = next;
    }
    printf("-> %d\n", 1); 
}

int main() {
    int graph[V][V] = {
        {0, 10, 15, 20},
        {5, 0, 9, 10},
        {6, 13, 0, 12},
        {8, 8, 9, 0}
    };   
    int dp[V][1 << V];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < (1 << V); j++) {
            dp[i][j] = -1;
        }
    }
    int min_distance = tsp(graph, 1, 0, dp);
    printf("Minimum Distance: %d\n", min_distance);
    printPath(graph, dp);
    return 0;
}
