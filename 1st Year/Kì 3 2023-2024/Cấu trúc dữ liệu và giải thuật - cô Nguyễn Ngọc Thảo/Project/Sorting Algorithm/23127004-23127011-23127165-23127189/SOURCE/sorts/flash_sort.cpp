#include "flash_sort.hpp"

void Fsort(int* arr, int n) {
    // Step 1: Find the minimum and maximum values
    int minVal = arr[0], maxVal = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] < minVal) minVal = arr[i];
        else if (arr[i] > maxVal) maxVal = arr[i];
    }

    // Step 2: Calculate the bucket width
    const int numBuckets = 100000; // Specify the number of buckets (value of m)
    double c = (double)(numBuckets - 1) / (maxVal - minVal);

    // Step 3: Count the number of elements in each bucket
    int* bucketCounts = new int[numBuckets]();
    for (int i = 0; i < n; ++i) {
        int bucketIndex = int(c * (arr[i] - minVal));
        ++bucketCounts[bucketIndex];
    }

    // Step 4: Calculate the prefix sum for buckets
    int* prefixSum = new int[numBuckets]();
    for (int i = 1; i < numBuckets; ++i) {
        prefixSum[i] = prefixSum[i - 1] + bucketCounts[i - 1];
    }

    // Step 5: Place elements into buckets
    int* sortedArr = new int[n];
    for (int i = 0; i < n; ++i) {
        int bucketIndex = int(c * (arr[i] - minVal));
        sortedArr[prefixSum[bucketIndex]] = arr[i];
        ++prefixSum[bucketIndex];
    }

    // Step 6: Sort each bucket using insertion sort
    for (int i = 0; i < numBuckets; ++i) {
        int start;
        if (i == 0) start = 0;
        else start = prefixSum[i - 1];
        int end = prefixSum[i];

        // Insertion sort within the bucket
        for (int j = start + 1; j < end; ++j) {
            int key = sortedArr[j];
            int k = j - 1;
            while (k >= start && sortedArr[k] > key) {
                sortedArr[k + 1] = sortedArr[k];
                k--;
            }
            sortedArr[k + 1] = key;
        }
    }

    // Copy sorted result back to the original array
    for (int i = 0; i < n; ++i) {
        arr[i] = sortedArr[i];
    }

    // Free allocated memory
    delete[] bucketCounts;
    delete[] prefixSum;
    delete[] sortedArr;
}

void Fsort_Count(int* arr, int n, long long& count){
    // Step 1: Find the minimum and maximum values
    int minVal = arr[0], maxVal = arr[0];
    for (int i = 1; ++count && i < n; ++i) {
        if (++count && arr[i] < minVal) minVal = arr[i];
        else if (++count && arr[i] > maxVal) maxVal = arr[i];
    }

    // Step 2: Calculate the bucket width
    const int numBuckets = 100000; // Specify the number of buckets (value of m)
    double c = (double)(numBuckets - 1) / (maxVal - minVal);

    // Step 3: Count the number of elements in each bucket
    int* bucketCounts = new int[numBuckets]();
    for (int i = 0; ++count && i < n; ++i) {
        int bucketIndex = int(c * (arr[i] - minVal));
        ++bucketCounts[bucketIndex];
    }

    // Step 4: Calculate the prefix sum for buckets
    int* prefixSum = new int[numBuckets]();
    for (int i = 1; ++count && i < numBuckets; ++i) {
        prefixSum[i] = prefixSum[i - 1] + bucketCounts[i - 1];
    }

    // Step 5: Place elements into buckets
    int* sortedArr = new int[n];
    for (int i = 0; ++count && i < n; ++i) {
        int bucketIndex = int(c * (arr[i] - minVal));
        sortedArr[prefixSum[bucketIndex]] = arr[i];
        ++prefixSum[bucketIndex];
    }

    // Step 6: Sort each bucket using insertion sort
    for (int i = 0; ++count && i < numBuckets; ++i) {
        int start;
        if (++count && i == 0) start = 0;
        else start = prefixSum[i - 1];
        int end = prefixSum[i];

        // Insertion sort within the bucket
        for (int j = start + 1; ++count && j < end; ++j) {
            int key = sortedArr[j];
            int k = j - 1;
            while (++count && k >= start && ++count && sortedArr[k] > key) {
                sortedArr[k + 1] = sortedArr[k];
                k--;
            }
            sortedArr[k + 1] = key;
        }
    }

    // Copy sorted result back to the original array
    for (int i = 0; ++count && i < n; ++i) {
        arr[i] = sortedArr[i];
    }

    // Free allocated memory
    delete[] bucketCounts;
    delete[] prefixSum;
    delete[] sortedArr;
}

/*
This function is used to sort the array using flash sort
*/
void Flash_Sort(int* arr, int n){
    Fsort(arr, n);
}

/*
This function is used to sort the array using flash sort and count the number of comparisons
*/
void Flash_Sort_Count(int* arr, int n, long long& count){
    count = 0;
    Fsort_Count(arr, n, count);
}