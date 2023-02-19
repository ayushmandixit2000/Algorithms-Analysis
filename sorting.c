#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count = 0;

void insertion_sort(int unsorted[], int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            count++;
            if (unsorted[j] < unsorted[j-1]) {
                int temp = unsorted[j];
                unsorted[j] = unsorted[j-1];
                unsorted[j-1] = temp;
            } else {
                break;
            }
        }
    }
}

void merge(int left[], int left_size, int right[], int right_size, int sorted[]) {
    int i = 0, j = 0, k = 0;
    while (i < left_size && j < right_size) {
        count++;
        if (left[i] < right[j]) {
            sorted[k] = left[i];
            i++;
        } else {
            sorted[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < left_size) {
        sorted[k] = left[i];
        i++;
        k++;
    }
    while (j < right_size) {
        sorted[k] = right[j];
        j++;
        k++;
    }
}

void merge_sort(int unsorted[], int n, int S, int sorted[]) {
    if (n <= S) {
        insertion_sort(unsorted, n);
        for (int i = 0; i < n; i++) {
            sorted[i] = unsorted[i];
        }
    } else {
        int mid = n / 2;
        int* left = (int*) malloc(mid * sizeof(int));
        int* right = (int*) malloc((n - mid) * sizeof(int));
        for (int i = 0; i < mid; i++) {
            left[i] = unsorted[i];
        }
        for (int i = mid; i < n; i++) {
            right[i - mid] = unsorted[i];
        }
        int* sorted_left = (int*) malloc(mid * sizeof(int));
        int* sorted_right = (int*) malloc((n - mid) * sizeof(int));
        merge_sort(left, mid, S, sorted_left);
        merge_sort(right, n - mid, S, sorted_right);
        merge(sorted_left, mid, sorted_right, n - mid, sorted);
        free(left);
        free(right);
        free(sorted_left);
        free(sorted_right);
    }
}
int main() {

    int S = 1;
    int SIZE = 10000000;
    int n = SIZE;
    int *unsorted = malloc(SIZE * sizeof(int)); // dynamically allocate memory for unsorted
    int *sorted = malloc(n * sizeof(int)); // dynamically allocate memory for sorted

    double *timearray = malloc(40 * sizeof(double));
    int t = 0;

    for(S = 1; S < 2; S++){
    
    // generate random integers between 1 and 10,000,000
    
    for (int i = 0; i < SIZE; i++) {
        unsorted[i] = rand() % 10000000 + 1;
    }

    clock_t start, end;
    double cpu_time_used;
    start = clock(); // get the starting time
    srand(time(NULL));  // seed the random number generator with the current time
    
    merge_sort(unsorted, n, S, sorted);
    
    end = clock(); // get the ending time
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // calculate the time elapsed
    printf("Execution time: %f seconds\n", cpu_time_used);
    printf("\nNumber of comparisons: %d\n", count);
    timearray[t] = (cpu_time_used);
    t++;

    }
    // free dynamically allocated memory

    for (int m = 0; m < 1; m++){
        printf("\nS = %d: %f\n", m+1,timearray[m]);
    }
    return 0;
}