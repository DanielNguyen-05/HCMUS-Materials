#include "merge_sort.hpp"

void Merge(int* arr, int const left, int const mid, int const right){
    int const sub1 = mid - left + 1;
    int const sub2 = right - mid;

    // Create temp arrays
    int *left_arr = new int[sub1];
    int *right_arr = new int[sub2];

    // Copy data to temp arrays left_arr[] and right_arr[]
    for (int i = 0; i < sub1; i++)
        left_arr[i] = arr[left + i];
    for (int j = 0; j < sub2; j++)
        right_arr[j] = arr[mid + 1 + j];

    int index1 = 0, index2 = 0;
    int index = left;

    // Merge the temp arrays back into arr[left..right]
    while (index1 < sub1 && index2 < sub2) {
        if (left_arr[index1] <= right_arr[index2]) {
            arr[index] = left_arr[index1];
            index1++;
        }
        else {
            arr[index] = right_arr[index2];
            index2++;
        }
        index++;
    }

    // Copy the remaining elements of
    // left[], if there are any
    while (index1 < sub1) {
        arr[index] = left_arr[index1];
        index1++;
        index++;
    }

    // Copy the remaining elements of
    // right[], if there are any
    while (index2 < sub2) {
        arr[index] = right_arr[index2];
        index2++;
        index++;
    }

    // free the memory
    delete[] left_arr;
    delete[] right_arr;
}

void Merge_Count(int* arr, int const left, int const mid, int const right, long long& count){
    int const sub1 = mid - left + 1;
    int const sub2 = right - mid;

    int *left_arr = new int[sub1];
    int *right_arr = new int[sub2];

    for (int i = 0; ++count && i < sub1; i++)
        left_arr[i] = arr[left + i];
    for (int j = 0; ++count && j < sub2; j++)
        right_arr[j] = arr[mid + 1 + j];

    int index1 = 0, index2 = 0;
    int index = left;

    while (++count && index1 < sub1 && ++count && index2 < sub2) {
        if (++count && left_arr[index1] <= right_arr[index2]) {
            arr[index] = left_arr[index1];
            index1++;
        }
        else {
            arr[index] = right_arr[index2];
            index2++;
        }
        index++;
    }

    while (++count && index1 < sub1) {
        arr[index] = left_arr[index1];
        index1++;
        index++;
    }

    while (++count && index2 < sub2) {
        arr[index] = right_arr[index2];
        index2++;
        index++;
    }

    delete[] left_arr;
    delete[] right_arr;
}

void Msort(int* arr, int const begin, int const end){
    if (begin >= end) return;

    int mid = begin + (end - begin) / 2;
    Msort(arr, begin, mid);
    Msort(arr, mid + 1, end);
    Merge(arr, begin, mid, end);
}

void Msort_Count(int* arr, int const begin, int const end, long long& count){
    if (++count && begin >= end) return;

    int mid = begin + (end - begin) / 2;
    Msort_Count(arr, begin, mid, count);
    Msort_Count(arr, mid + 1, end, count);
    Merge_Count(arr, begin, mid, end, count);
}

/*
This function is used to sort the array using merge sort

*/
void Merge_Sort(int* arr, int n){
    Msort(arr, 0, n - 1);
}

/*
This function is used to sort the array using merge sort and count the number of comparisons
*/
void Merge_Sort_Count(int* arr, int n, long long& count){
    count = 0;
    Msort_Count(arr, 0, n - 1, count);
}