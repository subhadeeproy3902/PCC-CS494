#include<stdio.h>
#include<stdlib.h>

int isSafe(int x, int y, int m, int n, int board[][n]) {
    int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && ny >= 0 && nx < m && ny < n && board[nx][ny] == 1)
            return 0; // Not safe, as there is already a knight at this position.
    }
    return 1; // Safe to place a knight at this position.
}

void print(int m, int n, int board[][n], int *count) {
    printf("\n\nSolution %d :\n\n", ++(*count));
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if (board[i][j] == 1)
                printf("\tK");
            else
                printf("\t-");
        }
        printf("\n");
    }
} 

void solve(int k, int row, int col, int m, int n, int board[][n], int *count) {
    if (k == 0) {
        print(m, n, board, count);
        return;
    }

    for (int i = row; i < m; i++) {
        for (int j = (i == row) ? col : 0; j < n; j++) {
            if (board[i][j] == -1 && isSafe(i, j, m, n, board)) {
                board[i][j] = 1;
                solve(k - 1, i, j, m, n, board, count);
                board[i][j] = -1;
            }
        }
    }
}

int main() {
    int m, n, k, count = 0;
    printf("Enter the size of the board (m n): ");
    scanf("%d %d", &m, &n);
    printf("Enter the number of knights (K): ");
    scanf("%d", &k);

    int board[m][n];
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            board[i][j] = -1;

    solve(k, 0, 0, m, n, board, &count);
    return 0;
}
