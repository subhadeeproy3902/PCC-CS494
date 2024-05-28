#include<stdio.h>
#include<stdbool.h>

void printBoard(int n, int board[n][n])
{
  for(int i=0; i<n; i++)
  {
    for(int j=0; j<n; j++)
    {
      if(board[i][j])
        printf("Q ");
      else
        printf(". ");
    }
    printf("\n");
  }
}

bool isSafe(int row, int col, int n, int board[n][n])
{
  int i,j;

  for(i=0; i<col; i++)
  {
    if(board[row][i])
      return false;
  }

  for(i=row,j=col; i>=0 && j>=0; i--, j--)
  {
    if(board[i][j])
      return false;
  }

  for(i=row, j=col; i<n && j>=0; i++, j--)
  {
    if(board[i][j])
      return false;
  }

  return true;
}

bool solve(int n, int board[n][n], int col)
{
  if(col >= n)
    return true;

  for(int row=0; row<n; row++)
  {
    if(isSafe(row, col, n, board))
    {
      board[row][col] = 1;
      if(solve(n, board, col+1))
        return true;
      board[row][col] = 0;
    }
  }
  return false;
}

int main () 
{
  int n;
  printf("Enter the no. of queens : \n");
  scanf("%d", &n);
  int board[n][n];
  for(int i=0; i<n; i++)
  {
    for(int j=0; j<n; j++)
    {
      board[i][j] = 0;
    }
  }
  if(solve(n,board,0) == false)
    printf("Solution does not exist");
  else
    printBoard(n,board);
  return 0;
}