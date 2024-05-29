#include <stdio.h>
#include <limits.h>

// Function to find the maximum sub-array sum crossing the midpoint
int maxCrossingSum(int arr[], int left, int mid, int right, int *cross_start, int *cross_end) {
    int sum = 0;
    int left_sum = INT_MIN;
    int max_left = mid;

    for (int i = mid; i >= left; i--) {
        sum += arr[i];
        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }

    sum = 0;
    int right_sum = INT_MIN;
    int max_right = mid + 1;

    for (int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        if (sum > right_sum) {
            right_sum = sum;
            max_right = i;
        }
    }

    *cross_start = max_left;
    *cross_end = max_right;
    return left_sum + right_sum;
}

// Function to find the maximum sub-array sum using divide and conquer
int maxSubArraySum(int arr[], int left, int right, int *start, int *end) {
    if (left == right) {
        *start = *end = left;
        return arr[left];
    }
          
    int mid = (left + right) / 2;

    int left_start, left_end, right_start, right_end, cross_start, cross_end;

    int left_sum = maxSubArraySum(arr, left, mid, &left_start, &left_end);
    int right_sum = maxSubArraySum(arr, mid + 1, right, &right_start, &right_end);
    int cross_sum = maxCrossingSum(arr, left, mid, right, &cross_start, &cross_end);

    if (left_sum >= right_sum && left_sum >= cross_sum) {
        *start = left_start;
        *end = left_end;
        return left_sum;
    } else if (right_sum >= left_sum && right_sum >= cross_sum) {
        *start = right_start;
        *end = right_end;
        return right_sum;
    } else {
        *start = cross_start;
        *end = cross_end;
        return cross_sum;
    }
}

// Function to print the sub-array with maximum sum
void printSubArray(int arr[], int start, int end) {
    printf("Maximum Sub-array: [");
    for (int i = start; i <= end; i++) {
        printf("%d", arr[i]);
        if (i < end) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    int arr[] = {12, -13, -5, 25, -20, 30, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int start, end;

    int max_sum = maxSubArraySum(arr, 0, n - 1, &start, &end);

    printf("Maximum Sub-array Sum: %d\n", max_sum);
    printSubArray(arr, start, end);

    return 0;
}
