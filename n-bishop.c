#include <stdio.h>
#include <stdlib.h>

int isSafeBishop(int x, int y, int m, int n, int board[][n]) {
    for (int i = 1; i < m; i++) {
        if (x + i < m && y + i < n && board[x + i][y + i] == 1)
            return 0; // Not safe, as there is already a bishop on the same diagonal.
        if (x - i >= 0 && y + i < n && board[x - i][y + i] == 1)
            return 0;
        if (x + i < m && y - i >= 0 && board[x + i][y - i] == 1)
            return 0;
        if (x - i >= 0 && y - i >= 0 && board[x - i][y - i] == 1)
            return 0;
    }
    return 1; // Safe to place a bishop at this position.
}

void printBishop(int m, int n, int board[][n], int *count) {
    printf("\n\nSolution %d :\n\n", ++(*count));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 1)
                printf("\tB");
            else
                printf("\t-");
        }
        printf("\n");
    }
}

void solveBishop(int k, int row, int col, int m, int n, int board[][n], int *count) {
    if (k == 0) {
        printBishop(m, n, board, count);
        return;
    }

    for (int i = row; i < m; i++) {
        for (int j = (i == row) ? col : 0; j < n; j++) {
            if (board[i][j] == -1 && isSafeBishop(i, j, m, n, board)) {
                board[i][j] = 1;
                solveBishop(k - 1, i, j, m, n, board, count);
                board[i][j] = -1;
            }
        }
    }
}

int main() {
    int m, n, k, count = 0;
    printf("Enter the size of the board (m n): ");
    scanf("%d %d", &m, &n);
    printf("Enter the number of bishops (K): ");
    scanf("%d", &k);

    int board[m][n];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = -1;

    solveBishop(k, 0, 0, m, n, board, &count);
    return 0;
}
