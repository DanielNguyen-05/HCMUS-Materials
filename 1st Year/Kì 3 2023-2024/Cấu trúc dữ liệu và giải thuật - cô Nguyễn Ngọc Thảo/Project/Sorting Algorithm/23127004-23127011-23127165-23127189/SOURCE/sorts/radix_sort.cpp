#include "radix_sort.hpp"

// A utility function to get maximum value in arr[]
int Get_Max(int* arr, int n){
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[] according to the digit represented by exp.
void Count_Sort(int* arr, int n, int exp){
    // Output array
    int* output = new int [n];
    int i, cnt[10] = { 0 };

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        cnt[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual position of this digit in output[]
    for (i = 1; i < 10; i++)
        cnt[i] += cnt[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[cnt[(arr[i] / exp) % 10] - 1] = arr[i];
        cnt[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];

    delete [] output;
}


void Rsort(int* arr, int n){
    // Find the maximum number to know number of digits
    int m = Get_Max(arr, n);

    // Do counting sort for every digit.
    // Note that instead of passing digit number, exp is passed. exp is 10^i where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        Count_Sort(arr, n, exp);
}

int Get_Max_Count(int* arr, int n, long long& count){
    int mx = arr[0];
    for (int i = 1; ++count && i < n; i++)
        if (++count && arr[i] > mx)
            mx = arr[i];
    return mx;
}

void Count_Sort_Count(int* arr, int n, int exp, long long& count){
    int* output = new int[n];
    int i, cnt[10] = { 0 };

    for (i = 0; ++count && i < n; i++)
        cnt[(arr[i] / exp) % 10]++;

    for (i = 1; ++count && i < 10; i++)
        cnt[i] += cnt[i - 1];

    // Build the output array
    for (i = n - 1; ++count && i >= 0; i--) {
        output[cnt[(arr[i] / exp) % 10] - 1] = arr[i];
        cnt[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now contains sorted numbers according to current digit
    for (i = 0; ++count && i < n; i++)
        arr[i] = output[i];

    delete [] output;
}

void Rsort_Count(int* arr, int n, long long& count){
    int m = Get_Max_Count(arr, n, count);
    for (int exp = 1; ++count && m / exp > 0; exp *= 10)
        Count_Sort_Count(arr, n, exp, count);
}

/*
This function is used to sort the array using radix sort
*/
void Radix_Sort(int* arr, int n){
    Rsort(arr, n);
}

/*
This function is used to sort the array using radix sort and count the number of comparisons
*/
void Radix_Sort_Count(int* arr, int n, long long& count){
    count = 0;
    Rsort_Count(arr, n, count);
}