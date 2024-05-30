#include <stdio.h>
#include <stdbool.h>

void print(int board[9][9]) {
    int i, j;
    printf("\n\nSolution:\n\n");
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%d\t", board[i][j]);
        }
        printf("\n");
    }
}

bool isValid(int board[9][9], int row, int col, int num) {
    for (int x = 0; x < 9; x++) {
        if (board[row][x] == num || board[x][col] == num || board[3 * (row / 3) + x / 3][3 * (col / 3) + x % 3] == num) {
            return false;
        }
    }
    return true;
}

bool solve(int board[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == -1) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(board, i, j, num)) {
                        board[i][j] = num;
                        if (solve(board)) {
                            return true;
                        } else {
                            board[i][j] = -1;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

int main() {
    int board[9][9];
    printf("\nEnter the values and put -1 where blank:\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    if (solve(board)) {
        print(board);
    } else {
        printf("No solution exists\n");
    }

    return 0;
}
