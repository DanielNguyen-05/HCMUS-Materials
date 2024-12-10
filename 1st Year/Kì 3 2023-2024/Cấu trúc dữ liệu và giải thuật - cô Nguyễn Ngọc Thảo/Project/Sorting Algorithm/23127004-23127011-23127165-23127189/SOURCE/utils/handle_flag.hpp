#pragma once
#include "comp_mode.hpp"
#include "algo_mode.hpp"
#include <iostream>
#include <string>

using namespace std;

/*

This file is used to handle the flags passed to the program.

There are 5 options, separated by two modes: Compare and Algorithm.
- Compare: 2 options -> these two can be distinguished by the number of arguments
- algorithm: 3 options -> we can used the number of arguments to distinguish the the option 2 with option 1 and 3;
option 1, 3 need to be distinguished by the [input size] and [given input] -> one is number, and other is string
so we need to have a function to check if the input is a number or a string.

*/

/*
In this mode, you have to run TWO specified sorting algorithms on the input data, which is either given or generated automatically and presents the resulting running times and/or numbers of comparisons.
*/
void Compare_Mode(int argc, char* argv[]);

/*
In this mode, you are asked to run a specified sorting algorithm on the input data, which is either given or generated automatically and presents the resulting running time and/or number of comparisons.
*/
void Algorithm_Mode(int argc, char* argv[]);