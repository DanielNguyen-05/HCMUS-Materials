#include "counting_sort.hpp"

void Csort(int* arr, int n){
    // find the max value of the array
    int max = arr[0];
    for (int i = 0; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }

    // create a new array to store the count of each element
    int* cnt = new int[max + 1];
    for (int i = 0; i <= max; i++) cnt[i] = 0;

    // count of each element
    for (int i = 0; i < n; i++) cnt[arr[i]]++;

    // calculate the position of each element
    for (int i = 1; i <= max; i++) cnt[i] += cnt[i - 1];

    // create a new array to store the sorted array
    int* res = new int[n];
    for (int i = n - 1; i >= 0; i--) {
        res[cnt[arr[i]] - 1] = arr[i];
        cnt[arr[i]]--;
    }
    for (int i = 0; i < n; i++) arr[i] = res[i];

    // free the memory
    delete[] cnt;
    delete[] res;
}

void Csort_Count(int* arr, int n, long long& count){
    int max = arr[0];
    for (int i = 0; ++count && i < n; i++) {
        if (++count && arr[i] > max) max = arr[i];
    }

    int* cnt = new int[max + 1];
    for (int i = 0; ++count && i <= max; i++) cnt[i] = 0;

    for (int i = 0; ++count && i < n; i++) cnt[arr[i]]++;
    for (int i = 1; ++count && i <= max; i++) cnt[i] += cnt[i - 1];

    int* res = new int[n];
    for (int i = n - 1; ++count && i >= 0; i--) {
        res[cnt[arr[i]] - 1] = arr[i];
        cnt[arr[i]]--;
    }
    for (int i = 0; ++count && i < n; i++) arr[i] = res[i];

    delete[] cnt;
    delete[] res;
}

/*
This function is used to sort the array using counting sort
*/
void Counting_Sort(int* arr, int n){
    Csort(arr, n);
}

/*
This function is used to sort the array using counting sort and count the number of comparisons
*/
void Counting_Sort_Count(int* arr, int n, long long& count){
    count = 0;
    Csort_Count(arr, n, count);
}