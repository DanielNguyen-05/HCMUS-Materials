#include "function_call.hpp"
// #include ".gitignore"/s


string algoList[] = {
    "selection-sort",
    "insertion-sort",
    "bubble-sort",
    "shaker-sort",
    "shell-sort",
    "heap-sort",
    "merge-sort",
    "quick-sort",
    "counting-sort",
    "radix-sort",
    "flash-sort"
};

void Call_Sort(const string name, int* arr, int n) {

    if (name == "selection-sort") {
        Selection_Sort(arr, n);
    } else if (name == "insertion-sort") {
        Insertion_Sort(arr, n);
    } else if (name == "bubble-sort") {
        Bubble_Sort(arr, n);
    } else if (name == "shaker-sort") {
        Shaker_Sort(arr, n);
    } else if (name == "shell-sort") {
        Shell_Sort(arr, n);
    } else if (name == "heap-sort") {
        Heap_Sort(arr, n);
    } else if (name == "merge-sort") {
        Merge_Sort(arr, n);
    } else if (name == "quick-sort") {
        Quick_Sort(arr, n);
    } else if (name == "counting-sort") {
        Counting_Sort(arr, n);
    } else if (name == "radix-sort") {
        Radix_Sort(arr, n);
    } else if (name == "flash-sort") {
        Flash_Sort(arr, n);
    }  else {
        cout << "np sorting algo found!";
    }

    // if (name == "quick-sort") {
    //     Quick_Sort(arr, n);
    // } else {
    //     cout << "no sorting algo found!";
    // }
}

void Call_Sort_Counting(const string name, int* arr, int n, long long& cntComp) {
  if (name == "selection-sort") {
        Selection_Sort_Count(arr, n, cntComp);
    } else if (name == "insertion-sort") {
        Insertion_Sort_Count(arr, n, cntComp);
    } else if (name == "bubble-sort") {
        Bubble_Sort_Count(arr, n, cntComp);
    } else if (name == "shaker-sort") {
        Shaker_Sort_Count(arr, n, cntComp);
    } else if (name == "shell-sort") {
        Shell_Sort_Count(arr, n, cntComp);
    } else if (name == "heap-sort") {
        Heap_Sort_Count(arr, n, cntComp);
    } else if (name == "merge-sort") {
        Merge_Sort_Count(arr, n, cntComp);
    } else if (name == "quick-sort") {
        Quick_Sort_Count(arr, n, cntComp);
    } else if (name == "counting-sort") {
        Counting_Sort_Count(arr, n, cntComp);
    } else if (name == "radix-sort") {
        Radix_Sort_Count(arr, n, cntComp);
    } else if (name == "flash-sort") {
        Flash_Sort_Count(arr, n, cntComp);
    } else {
        cout << "np sorting algo found!";
    }
    // if (name == "quick-sort") {
    //     Quick_Sort_Count(arr, n, cntComp);
    // } else {
    //     cout << "no sorting algo found!";
    // }
}


int *Load_Array(string inputPath, int &size) {
    ifstream file(inputPath);
    file >> size;
    int *arr = new int[size];

    for (int i = 0; i < size; i++) {
        file >> arr[i];
    }

    file.close();
    return arr;
}

void Dump_Array(string outputPath, int *arr, int size) {
    ofstream file(outputPath);
    file << size << endl;
    for (int i = 0; i < size; i++) {
        file << arr[i] << " ";
    }
    file.close();
}

void Make_Copy(int* arr, int *copy, int size) {
    for (int i = 0; i < size; i++) {
        copy[i] = arr[i];
    }
}

long long Get_Count(const string& algo, int *arr, int size) {
    long long count = 0;
    Call_Sort_Counting(algo, arr, size, count);
    return count;
}


pair<double, double> Get_Time(const string& algo, int *arr, int size) {
    Timer timer;
    timer.start();
    Call_Sort(algo, arr, size);
    timer.stop();

    return pair<double, double>(timer.elapsedSeconds(), timer.elapsedMilliseconds());
}
