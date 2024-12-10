#include "shaker_sort.hpp"

void shakerSort(int* arr, int n){
    int left = 0;       // Initialize the left boundary of the unsorted section
    int right = n - 1;  // Initialize the right boundary of the unsorted section
    int k = 0;          // Variable to track the last swap position

    // Continue sorting until the left and right boundaries meet
    while (left < right) {
        // Forward pass: move the largest element to the end of the unsorted section
        for (int i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {  // Compare adjacent elements
                swap(arr[i], arr[i + 1]);  // Swap if they are in the wrong order
                k = i;  // Update the position of the last swap
            }
        }
        right = k;  // Update the right boundary to the last swap position

        // Backward pass: move the smallest element to the beginning of the unsorted section
        for (int i = right; i > left; i--) {
            if (arr[i] < arr[i - 1]) {  // Compare adjacent elements
                swap(arr[i], arr[i - 1]);  // Swap if they are in the wrong order
                k = i;  // Update the position of the last swap
            }
        }
        left = k;  // Update the left boundary to the last swap position
    }
}

void shakerSort_Count(int* arr, int n, long long& count){
    int left = 0;
    int right = n - 1;
    int k = 0;

    while (++count && left < right) {
        for (int i = left; ++count && i < right; i++) {
            if (++count && arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                k = i;
            }
        }
        right = k;
        for (int i = right; ++count && i > left; i--) {
            if (++count && arr[i] < arr[i - 1]) {
                swap(arr[i], arr[i - 1]);
                k = i;
            }
        }
        left = k;
    }
}

/*
This function is used to sort the array using shaker sort
*/
void Shaker_Sort(int* arr, int n){
    shakerSort(arr, n);
}

/*
This function is used to sort the array using shaker sort and count the number of comparisons
*/
void Shaker_Sort_Count(int* arr, int n, long long& count){
    count = 0;
    shakerSort_Count(arr, n, count);
}