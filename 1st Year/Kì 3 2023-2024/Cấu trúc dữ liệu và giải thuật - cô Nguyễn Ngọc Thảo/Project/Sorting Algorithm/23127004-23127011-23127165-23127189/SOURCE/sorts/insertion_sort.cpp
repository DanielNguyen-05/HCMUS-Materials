#include "insertion_sort.hpp"

void Isort(int* arr, int n){
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1],
        // that are greater than key,
        // to one position ahead of their
        // current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void Isort_Count(int* arr, int n, long long& count){
    int i, key, j;
    for (i = 1; ++count && i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (++count && j >= 0 && ++count && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

/*
This function is used to sort the array using insertion sort
*/
void Insertion_Sort(int* arr, int n){
    Isort(arr, n);
}

/*
This function is used to sort the array using insertion sort and count the number of comparisons
*/
void Insertion_Sort_Count(int* arr, int n, long long& count){
    count = 0;
    Isort_Count(arr, n, count);
}