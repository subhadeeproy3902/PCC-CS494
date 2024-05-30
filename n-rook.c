#include <stdio.h>
#include <stdlib.h>

int isSafeRook(int x, int y, int m, int n, int board[][n]) {
    for (int i = 0; i < m; i++) {
        if (board[x][i] == 1 || board[i][y] == 1) {
            return 0; // Not safe, as there is already a rook in the same row or column.
        }
    }
    return 1; // Safe to place a rook at this position.
}

void printRook(int m, int n, int board[][n], int *count) {
    printf("\n\nSolution %d :\n\n", ++(*count));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 1)
                printf("\tR");
            else
                printf("\t-");
        }
        printf("\n");
    }
}

void solveRook(int k, int row, int m, int n, int board[][n], int *count) {
    if (k == 0) {
        printRook(m, n, board, count);
        return;
    }

    for (int i = row; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == -1 && isSafeRook(i, j, m, n, board)) {
                board[i][j] = 1;
                solveRook(k - 1, i + 1, m, n, board, count); // move to the next row
                board[i][j] = -1;
            }
        }
    }
}

int main() {
    int m, n, k, count = 0;
    printf("Enter the size of the board (m n): ");
    scanf("%d %d", &m, &n);
    printf("Enter the number of rooks (K): ");
    scanf("%d", &k);

    int board[m][n];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = -1;

    solveRook(k, 0, m, n, board, &count);
    return 0;
}
