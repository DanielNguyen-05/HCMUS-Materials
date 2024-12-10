#include "bubble_sort.hpp"

void Bsort(int* arr, int n){
    for(int i = 1; i < n; i++){
        for(int j = 0; j < n - i; j++){
            if(arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
        }
    }
}

void Bsort_Count(int* arr, int n, long long& count){
    for(int i = 1; ++count && i < n; i++){
        for(int j = 0; ++count && j < n - i; j++){
            if(++count && arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
        }
    }
}

/*
This function is used to sort the array using bubble sort
*/
void Bubble_Sort(int* arr, int n){
    Bsort(arr, n);
}

/*
This function is used to sort the array using bubble sort and count the number of comparisons
*/
void Bubble_Sort_Count(int* arr, int n, long long& count){
    count = 0;
    Bsort_Count(arr, n, count);
}