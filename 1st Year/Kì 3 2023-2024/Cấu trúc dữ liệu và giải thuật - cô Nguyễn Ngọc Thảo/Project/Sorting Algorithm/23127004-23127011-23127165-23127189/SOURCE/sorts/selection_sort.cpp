#include "selection_sort.hpp"

void Ssort(int* arr, int n){
    int i, j, min_index;

    // One by one move boundary of
    // unsorted subarray
    for (i = 0; i < n - 1; i++) {

        // Find the minimum element in
        // unsorted array
        min_index = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index])
                min_index = j;
        }

        // Swap the found minimum element
        // with the first element
        if (min_index != i)
            swap(arr[min_index], arr[i]);
    }
}

void Ssort_Count(int* arr, int n, long long& count){
    int i, j, min_index;

    for (i = 0; ++count && i < n - 1; i++) {
        min_index = i;
        for (j = i + 1; ++count && j < n; j++) {
            if (++count && arr[j] < arr[min_index]) min_index = j;
        }

        if (++count && min_index != i) swap(arr[min_index], arr[i]);
    }
}

/*
This function is used to sort the array using selection sort
*/
void Selection_Sort(int* arr, int n){
    Ssort(arr, n);
}

/*
This function is used to sort the array using selection sort and count the number of comparisons
*/
void Selection_Sort_Count(int* arr, int n, long long& count){
    count = 0;
    Ssort_Count(arr, n, count);
}