#include <stdio.h>
#include <stdbool.h>
#define N 4
void printPuzzle(int arr[N*N], int *count) {
    printf("\nIntermediate state %d\n", (*count)++);
    for (int i = 0; i < N*N; i++) {
        printf("%2d ", arr[i]);
        if ((i + 1) % N == 0)
            printf("\n");
    }
}
void solvable(int arr[])
{
    int temp = 0, count = 1;
    for (int i = 0; i < N * N - 1; i++) {
        for (int j = i + 1; j < N * N; j++) {
            if (arr[j] != 0 && arr[i] != 0 && arr[i] > arr[j])
            {
                //inv_count++;
                // Swap elements
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                // Print intermediate state
                printPuzzle(arr, &count);
            }
        }
    }
    //return inv_count;
}
int getInvCount(int arr[])
{
    int inv_count = 0;
    for (int i = 0; i < N * N - 1; i++) {
        for (int j = i + 1; j < N * N; j++) {
            if (arr[j] != 0 && arr[i] != 0 && arr[i] > arr[j])
            {
                inv_count++;
            }
        }
    }
    return inv_count;
}
int findXPosition(int puzzle[N][N])
{
    for (int i = N - 1; i >= 0; i--)
        for (int j = N - 1; j >= 0; j--)
            if (puzzle[i][j] == 0)
                return N - i;
    return -1;
}
bool isSolvable(int puzzle[N][N])
{
    int arr[N * N];
    int k = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (puzzle[i][j] != 0)
                arr[k++] = puzzle[i][j];
    while (k < N * N)
        arr[k++] = 0;
    int invCount = getInvCount(arr);
    printf("\nInversion count: %d\n",invCount);
    if (N % 2 == 1)
    {
        if (invCount % 2 == 0)
        {
            solvable(arr);
            return 1;
        }
        else
            return 0;

    }
    else
    {
        int pos = findXPosition(puzzle);
        if (pos % 2 == 0)
            //return invCount % 2 == 0;
        {
            if (invCount%2 == 0)
                return 0;
            else
            {
                solvable(arr);
                return 1;
            }
        }
        else
            //return invCount % 2 == 1;
            {
                if (invCount%2 == 0)
                {
                    solvable(arr);
                    return 1;
                }
                else
                    return 0;
            }
    }
}
int main()
{
    int puzzle[N][N] = {
       {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 11},
        {13, 14, 15, 12}
   };
//    int puzzle[N][N] = {
//         {13,2,10,3},
//         {1,12,8,4},
//         {5, 0, 9, 6},
//         {15,14,11,7},
//     };
    printf("%s\n", isSolvable(puzzle) ? "Solvable" : "Not Solvable");
    return 0;
}
