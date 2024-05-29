#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to print the numbers that match the criteria
void printNumbers(char* s, int n, int k, int idx, int tight, int nonZero, char* current) {
    if (idx == n) {
        if (nonZero == k) {
            current[idx] = '\0';
            printf("%s\n", current);
        }
        return;
    }

    int limit = tight ? s[idx] - '0' : 9;
    for (int digit = 0; digit <= limit; ++digit) {
        current[idx] = digit + '0';
        printNumbers(s, n, k, idx + 1, tight && (digit == limit), nonZero + (digit > 0), current);
    }
}

// Function to find number less than N having k non-zero digits and also print those numbers
int k_nonzero_numbers(int num, int k) {
    // Convert number to string
    char s[20];
    sprintf(s, "%d", num);
    int n = strlen(s);

    // Store the memorised values
    int dp[20][2][20] = {{{0}}};

    // Base
    dp[0][0][0] = 1;

    // Calculate all states
    // For every state, from numbers 1 to N,
    // the count of numbers which contain exactly j
    // non zero digits is being computed and updated
    // in the dp array.
    for (int i = 0; i < n; ++i) {
        for (int sm = 0; sm < 2; ++sm) {
            for (int j = 0; j <= k; ++j) {
                for (int x = 0; x <= (sm ? 9 : s[i] - '0'); ++x) {
                    dp[i + 1][sm || (x < (s[i] - '0'))][j + (x > 0)] += dp[i][sm][j];
                }
            }
        }
    }

    // Print the valid numbers
    char* current = (char*)malloc((n + 1) * sizeof(char));
    printNumbers(s, n, k, 0, 1, 0, current);
    free(current);

    // Return the required answer
    return dp[n][0][k] + dp[n][1][k];
}

int main() {
    int num;
    int k;
    printf("Enter the number N: ");
    scanf("%d", &num);
    printf("Enter the value of k: ");
    scanf("%d", &k);
    int result = k_nonzero_numbers(num, k);
    printf("Total count: %d\n", result);
    return 0;
}
