#include "heap_sort.hpp"

void Heapify(int* arr, int n, int i){
    // Initialize largest as root
    int largest = i;

    // left = 2*i + 1
    int l = 2 * i + 1;

    // right = 2*i + 2
    int r = 2 * i + 2;

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest
    // so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively Heapify the affected
        // sub-tree
        Heapify(arr, n, largest);
    }
}

void Heapify_Count(int* arr, int n, int i, long long& count){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (++count && ++count && l < n && arr[l] > arr[largest]) largest = l;
    if (++count && ++count && r < n && arr[r] > arr[largest]) largest = r;

    if (++count && largest != i) {
        swap(arr[i], arr[largest]);
        Heapify_Count(arr, n, largest, count);
    }
}

void Hsort(int* arr, int n){
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(arr, n, i);

    // One by one extract an element
    // from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max Heapify on the reduced heap
        Heapify(arr, i, 0);
    }
}

void Hsort_Count(int* arr, int n, long long& count){
    for (int i = n / 2 - 1; ++count && i >= 0; i--)
        Heapify_Count(arr, n, i, count);
    for (int i = n - 1; ++count && i > 0; i--) {
        swap(arr[0], arr[i]);
        Heapify_Count(arr, i, 0, count);
    }
}

/*
This function is used to sort the array using heap sort
*/
void Heap_Sort(int* arr, int n){
    Hsort(arr, n);
}

/*
This function is used to sort the array using heap sort and count the number of comparisons
*/
void Heap_Sort_Count(int* arr, int n, long long& count){
    count = 0;
    Hsort_Count(arr, n, count);
}