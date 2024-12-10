#include "shell_sort.hpp"

void shellSort(int* arr, int n){
    // Start with a big gap, then reduce the gap
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        for (int i = gap; i < n; i++)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];

            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            //  put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }
}

void shellSort_Count(int* arr, int n, long long& count){
    for (int gap = n / 2; ++count && gap > 0; gap /= 2) {
        for (int i = gap; ++count && i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; ++count && j >= gap && ++count && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

/*
This function is used to sort the array using shell sort
*/
void Shell_Sort(int* arr, int n){
    shellSort(arr, n);
}

/*
This function is used to sort the array using shell sort and count the number of comparisons
*/
void Shell_Sort_Count(int* arr, int n, long long& count){
    count = 0;
    shellSort_Count(arr, n, count);
}