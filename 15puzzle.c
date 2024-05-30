#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define N 4
#define INF INT_MAX

// Directions arrays for moving the blank space
int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };

// Structure to represent a node in the search tree
typedef struct Node {
    int puzzle[N][N];
    int x, y;
    int cost;
    int level;
    struct Node* parent;
} Node;

// Function to allocate a new node
Node* newNode(int puzzle[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->parent = parent;
    node->level = level;
    node->cost = INF;
    memcpy(node->puzzle, puzzle, sizeof(node->puzzle));
    node->puzzle[x][y] = node->puzzle[newX][newY];
    node->puzzle[newX][newY] = 0;
    node->x = newX;
    node->y = newY;
    return node;
}

// Function to calculate the Manhattan distance
int calculateCost(int initial[N][N], int final[N][N]) {
    int cost = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (initial[i][j] && initial[i][j] != final[i][j]) {
                int value = initial[i][j];
                int goalX = (value - 1) / N;
                int goalY = (value - 1) % N;
                cost += abs(i - goalX) + abs(j - goalY);
            }
        }
    }
    return cost;
}

// Function to print the puzzle
void printPuzzle(int puzzle[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", puzzle[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to check if the coordinates are valid
int isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// A utility function to check if a given state is solvable
int isSolvable(int puzzle[N][N]) {
    int invCount = 0;
    int arr[N*N];
    int k = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[k++] = puzzle[i][j];
        }
    }
    for (int i = 0; i < N * N - 1; i++) {
        for (int j = i + 1; j < N * N; j++) {
            if (arr[i] && arr[j] && arr[i] > arr[j]) {
                invCount++;
            }
        }
    }
    return (invCount % 2 == 0);
}

// Function to solve the 15 puzzle problem
void solve(int initial[N][N], int x, int y, int final[N][N]) {
    if (!isSolvable(initial)) {
        printf("The given puzzle is unsolvable.\n");
        return;
    }

    // Create a priority queue to store live nodes of the search tree
    Node* pq[10000];
    int size = 0;

    Node* root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(initial, final);

    pq[size++] = root;

    while (size) {
        // Find the node with the least cost
        int min = 0;
        for (int i = 1; i < size; i++) {
            if (pq[i]->cost + pq[i]->level < pq[min]->cost + pq[min]->level) {
                min = i;
            }
        }

        // Get the node with the least cost
        Node* minNode = pq[min];

        // Remove the node from the priority queue
        for (int i = min; i < size - 1; i++) {
            pq[i] = pq[i + 1];
        }
        size--;

        // If the node is the goal node, print the path
        if (minNode->cost == 0) {
            printf("Solution found at level %d\n", minNode->level);
            Node* path = minNode;
            while (path) {
                printPuzzle(path->puzzle);
                path = path->parent;
            }
            return;
        }

        // Generate the child nodes
        for (int i = 0; i < 4; i++) {
            if (isSafe(minNode->x + row[i], minNode->y + col[i])) {
                Node* child = newNode(minNode->puzzle, minNode->x, minNode->y, minNode->x + row[i], minNode->y + col[i], minNode->level + 1, minNode);
                child->cost = calculateCost(child->puzzle, final);
                pq[size++] = child;
            }
        }
    }

    printf("No solution found.\n");
}

int main() {
    // Solvable example
    int initialSolvable[N][N] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 },
        { 13, 14, 0, 15 }
    };

    // Unsolvable example
    int initialUnsolvable[N][N] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 },
        { 13, 15, 14, 0 }
    };

    int final[N][N] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 },
        { 13, 14, 15, 0 }
    };

    solve(initialSolvable, 3, 2, final);

    solve(initialUnsolvable, 3, 3, final);

    return 0;
}
