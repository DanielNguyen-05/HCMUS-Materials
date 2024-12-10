#include "handle_flag.hpp"

/*
write down the sorted array to the output.txt file
*/
void Command_1(string algo1, string givenInput, string outputParameter);

/*
- write down the sorted array to the output.txt file
- write down the generated input to the input.txt file
*/
void Command_2(string algo1, int inputtSize, string inputOrder, string outputParameter);

/*
- "input_1.txt": random order data
- "input_2.txt": nearly sorted data
- "input_3.txt": sorted data
- "input_4.txt": reversed data
*/

void Command_3(string algo1, int inputtSize, string outputParameter);

void Command_4(string algo1, string algo2, string givenInput);

void Command_5(string algo1, string algo2, int size, string inputOrder);


void Compare_Mode(int argc, char* argv[]) {
    cout << "COMPARE MODE\n";
    switch (argc)
    {
        case 5:
            Command_4(argv[2], argv[3], argv[4]);
            break;
        case 6:
            Command_5(argv[2], argv[3], stoi(argv[4]), argv[5]);
            break;
        default:
            break;
    }
}

bool is_number(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

void Algorithm_Mode(int argc, char* argv[]) {
    cout << "ALGORITHM MODE\n";
    if (argc == 5) {
        if (is_number(argv[3])) {
            Command_3(argv[2], stoi(argv[3]), argv[4]);
        } else {
            Command_1(argv[2], argv[3], argv[4]);
        }
    } else if (argc == 6) {
        Command_2(argv[2], stoi(argv[3]), argv[4], argv[5]);
    }
}

void Command_1(string algo1, string givenInput, string outputParameter) {
    // cout << "Hello from Command_1\n";
    // cout << algo1 << ' ' << givenInput << ' ' << outputParameter << '\n';
    Handle_Command_1(algo1, givenInput, outputParameter);
}

void Command_2(string algo1, int inputtSize, string inputOrder, string outputParameter) {
    // cout << "Hello from Command_2\n";
    // cout << algo1 << ' ' << inputtSize << ' ' << inputOrder << ' ' << outputParameter << '\n';
    Handle_Command_2(algo1, inputtSize, inputOrder, outputParameter);
}

void Command_3(string algo1, int inputtSize, string outputParameter) {
    // cout << "Hello from Command_3\n";
    // cout << algo1 << ' ' << inputtSize << ' ' << outputParameter << '\n';
    Handle_Command_3(algo1, inputtSize, outputParameter);
}

void Command_4(string algo1, string algo2, string givenInput) {
    // cout << "Hello from Command_4\n";
    // cout << algo1 << ' ' << algo2 << ' ' << givenInput << '\n';
    Handle_Command_4(algo1, algo2, givenInput);

}

void Command_5(string algo1, string algo2, int size, string inputOrder) {
    // cout << "Hello from Command_5\n";
    // cout << algo1 << ' ' << algo2 << ' ' << size << ' ' << inputOrder << '\n';
    Handle_Command_5(algo1, algo2, size, inputOrder);
}