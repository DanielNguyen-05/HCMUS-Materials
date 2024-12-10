#include "quick_sort.hpp"

void Qsort(int* arr, int l, int r) {
    int pivot = arr[1ll * rand() * rand() * rand() % (r - l + 1) + l]; // Choose a random pivot
    int left = l, right = r; // Initialize left and right pointers
    while (left <= right) { // Partition the array
        while (arr[left] < pivot) ++left; // Move left pointer until an element >= pivot is found
        while (pivot < arr[right]) --right; // Move right pointer until an element <= pivot is found
        if (left <= right) { // If pointers have not crossed
            swap(arr[left], arr[right]); // Swap elements at left and right pointers
            ++left; // Move left pointer right
            --right; // Move right pointer left
        }
    }
    if (left < r) Qsort(arr, left, r); // Recursively sort the right partition
    if (l < right) Qsort(arr, l, right); // Recursively sort the left partition
}

void Qsort_Count(int* arr, int l, int r, long long& count){
    int pivot = arr[1ll * rand() * rand() * rand() % (r - l + 1) + l];
    int left = l, right = r;
    while (++count && left <= right) {
        while (++count && arr[left] < pivot) ++left;
        while (++count && pivot < arr[right]) --right;
        if (++count && left <= right) {
            swap(arr[left], arr[right]);
            ++left;
            --right;
        }
    }
    if (++count && left < r) Qsort_Count(arr, left, r, count);
    if (++count && l < right) Qsort_Count(arr, l, right, count);
}

/*
This function is used to sort the array using quick sort
*/
void Quick_Sort(int* arr, int n){
    srand(time(0));
    Qsort(arr, 0, n - 1);
}

/*
This function is used to sort the array using quick sort and count the number of comparisons
*/
void Quick_Sort_Count(int* arr, int n, long long& count){
    count = 0;
    srand(time(0));
    Qsort_Count(arr, 0, n - 1, count);
}
