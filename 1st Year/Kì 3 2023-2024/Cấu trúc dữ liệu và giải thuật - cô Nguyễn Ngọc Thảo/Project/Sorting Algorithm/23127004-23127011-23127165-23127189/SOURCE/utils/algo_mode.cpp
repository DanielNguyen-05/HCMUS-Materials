#include "algo_mode.hpp"

const int TIME = 1;
const int COMP = 2;
const int BOTH = 3;

int Parse_Param(const string outputParameter) {
    if (outputParameter == "-both") return BOTH;
    if (outputParameter == "-time") return TIME;
    if (outputParameter == "-comp") return COMP;
    return 0;
}


namespace ORDER {
    /*
    Run the sorting algorithm with the given datafile and outputParameter
    */
    void Run_Sort(string datafile, string algo, string outputParameter, int printSizeOrder = 0, bool writeToFile = false) {
        const string inputPath = datafile;

        int size;
        int *arr = Load_Array(inputPath, size);
        int *copy = new int[size];

        if (printSizeOrder) {
            if (printSizeOrder & 1)
                cout << "Input size: " << size << endl;
            if (!(printSizeOrder & 2))
                cout << "-------------------------\n";
        }

        if (Parse_Param(outputParameter) & TIME) {
            Make_Copy(arr, copy, size);
            pair <double, double> time = Get_Time(algo, copy, size);
            cout << setprecision(8) << fixed;
            cout << "Running time: " << time.second << " miliseconds" << endl;
        }

        if (Parse_Param(outputParameter) & COMP) {
            Make_Copy(arr, copy, size);
            long long count = Get_Count(algo, copy, size);
            cout << "Comparisons: " << count << endl;
        }

        if (writeToFile) {
            ofstream out("output.txt");
            if (!out.is_open()) {
                cout << "Error opening file" << endl;
                return;
            }

            out << size << '\n';
            for (int i = 0; i < size; i++) {
                out << copy[i] << ' ';
            }
            out.close();
        }

        delete[] arr;
        delete[] copy;
    }

    void Randomize(int inputSize, string outputParam, string algo, bool writeToFile = false, string inputPath = "input.txt") {
        const string filename = inputPath;

        cout << "Input order: Randomize" << endl;
        cout << "-------------------------" << endl;

        // gen the file
        int err = Gen_Data_File(inputSize, "-rand", filename);
        if (err == -1) {
            cout << "error occured while generating!!";
            return;
        }
        Run_Sort(filename, algo, outputParam, 0, writeToFile);
    }

    void Nearly_Sorted(int inputSize, string outputParam, string algo, bool writeToFile = false, string inputPath = "input.txt") {
        const string filename = inputPath;

        cout << "Input order: Nearly Sorted" << endl;
        cout << "-------------------------" << endl;

        // gen the file
        int err = Gen_Data_File(inputSize, "-nsorted", filename);
        if (err == -1) {
            cout << "error occured while generating!!";
            return;
        }
        Run_Sort(filename, algo, outputParam, 0, writeToFile);
    }

    void Sorted(int inputSize, string outputParam, string algo, bool writeToFile = false, string inputPath = "input.txt") {
        const string filename = inputPath;

        cout << "Input order: Sorted" << endl;
        cout << "-------------------------" << endl;

        // gen the file
        int err = Gen_Data_File(inputSize, "-sorted", filename);
        if (err == -1) {
            cout << "error occured while generating!!";
            return;
        }
        Run_Sort(filename, algo, outputParam, 0, writeToFile);
    }

    void Reverse(int inputSize, string outputParam, string algo, bool writeToFile = false, string inputPath = "input.txt") {
        const string filename = inputPath;

        cout << "Input order: Reverse" << endl;
        cout << "-------------------------" << endl;

        // gen the file
        int err = Gen_Data_File(inputSize, "-rev", filename);
        if (err == -1) {
            cout << "error occured while generating!!";
            return;
        }
        Run_Sort(filename, algo, outputParam, 0, writeToFile);
    }
}

void Handle_Command_1(string algo, string givenInput, string outputParameter) {
    cout << "Algorithm: " << algo << endl;
    cout << "Input file: " << givenInput << endl;
    ORDER::Run_Sort(givenInput, algo, outputParameter, 1, true);
}

void Handle_Command_2(string algo, int inputtSize, string inputOrder, string outputParameter) {
    cout << "Algorithm: " << algo << endl;
    cout << "Input size: " << inputtSize << endl;
    if (inputOrder == "-rand") {
        ORDER::Randomize(inputtSize, outputParameter, algo, true);
    } else if (inputOrder == "-nsorted") {
        ORDER::Nearly_Sorted(inputtSize, outputParameter, algo, true);
    } else if (inputOrder == "-sorted") {
        ORDER::Sorted(inputtSize, outputParameter, algo, true);
    } else if (inputOrder == "-rev") {
        ORDER::Reverse(inputtSize, outputParameter, algo, true);
    } else {
        cout << "Invalid input order" << endl;
    }
}

// namespace

void Handle_Command_3(string algo, int inputtSize, string outputParameter) {
    cout << "Algorithm: " << algo << endl;
    cout << "Input size: " << inputtSize << endl;

    cout << "\n";
    ORDER::Randomize(inputtSize, outputParameter, algo, false, "input_1.txt");
    cout << "\n";
    ORDER::Nearly_Sorted(inputtSize, outputParameter, algo, false, "input_2.txt");
    cout << "\n";
    ORDER::Sorted(inputtSize, outputParameter, algo, false, "input_3.txt");
    cout << "\n";
    ORDER::Reverse(inputtSize, outputParameter, algo, false, "input_4.txt");
}
