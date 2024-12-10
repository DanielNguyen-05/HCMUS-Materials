#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include "timer.hpp"
#include "../gen/gen.hpp"
#include "../sorts/quick_sort.hpp"
#include "../sorts/bubble_sort.hpp"
#include "../sorts/counting_sort.hpp"
#include "../sorts/flash_sort.hpp"
#include "../sorts/heap_sort.hpp"
#include "../sorts/insertion_sort.hpp"
#include "../sorts/merge_sort.hpp"
#include "../sorts/radix_sort.hpp"
#include "../sorts/selection_sort.hpp"
#include "../sorts/shaker_sort.hpp"
#include "../sorts/shell_sort.hpp"

// #include "./sorting/quick_sort.hpp"

/*
This header will be uses to call out sorting algo
*/

using namespace std;


/*
This function will call the sorting function
*/
void Call_Sort(const string name, int* arr, int n);


/*
- This function will call the sorting function with counting
- will first set count = 0
*/
void Call_Sort_Counting(const string name, int* arr, int n, long long& cntComp);

/*
This function is used to load the array from the path, then return then array in form of pointer and change the size
*/
int *Load_Array(string inputPath, int &size);

/*
Write the array to outputPath
*/
void Dump_Array(string outputPath, int *arr, int size);

/*
copy 'array' to 'copy'
*/
void Make_Copy(int* arr, int *copy, int size);

/*
    return a pair of <seconds, milliseconds>
*/
pair<double, double> Get_Time(const string& algo, int *arr, int size);


/*
    return the number of comparisons
*/
long long Get_Count(const string& algo, int *arr, int size);