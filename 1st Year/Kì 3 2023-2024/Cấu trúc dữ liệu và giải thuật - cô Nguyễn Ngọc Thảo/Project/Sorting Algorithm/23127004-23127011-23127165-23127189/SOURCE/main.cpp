#include "./utils/handle_flag.hpp"
// #include "sorting/quick_sort.hpp"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {

    char mode = argv[1][1];
    switch (mode)
    {
        case 'c':
            Compare_Mode(argc, argv);
            break;
        case 'a':
            Algorithm_Mode(argc, argv);
            break;
        default:
            break;
    }

    return 0;
}