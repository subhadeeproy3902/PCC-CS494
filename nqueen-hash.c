#include<stdio.h>
#include<stdlib.h>

void print(int n,int board[][n],int *count)
{
    int i,j;
    printf("\n\nSolution %d :\n\n",++(*count));
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if (board[i][j]==1)
                printf("\tQ");
            else
                printf("\t-");
        }
        printf("\n");
    }
}

void solve(int col,int n,int board[][n], int leftrow[],int upperdiag[],int lowerdiag[],int *count)
{
    if(col==n)
    {
        print(n,board,count);
        return;
    }

    for(int row=0;row<n;row++)
    {
        if(leftrow[row]==0 && lowerdiag[row+col]==0 && upperdiag[n-1 + col-row]==0)
        {
            leftrow[row]=1;
            lowerdiag[row+col]=1;
            upperdiag[n-1+col-row]=1;
            board[row][col]=1;
            solve(col+1,n,board,leftrow,upperdiag,lowerdiag,count);
            leftrow[row]=0;
            lowerdiag[row+col]=0;
            upperdiag[n-1+col-row]=0;
            board[row][col]=-1;
        }
    }
}

void main()
{
    int n,i,j;
    int count=0;
    printf("\nEnter the size of board: ");
    scanf("%d",&n);
    int board[n][n];
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            board[i][j]=-1;
    int leftrow[n],upperdiag[2*n - 1],lowerdiag[2*n - 1];
    for(i=0;i<n;i++)
    {
        leftrow[i]=0;
    }
    for(i=0;i<2*n-1;i++)
    {
        upperdiag[i]=0;
        lowerdiag[i]=0;
    }
    solve(0,n,board,leftrow,upperdiag,lowerdiag,&count);
}
