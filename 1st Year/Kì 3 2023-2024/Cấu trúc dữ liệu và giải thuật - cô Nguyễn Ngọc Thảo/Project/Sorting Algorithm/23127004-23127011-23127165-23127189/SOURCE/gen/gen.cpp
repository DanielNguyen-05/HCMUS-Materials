#include "gen.hpp"

void GenerateRandomData(int a[], int n);
void GenerateSortedData(int a[], int n);
void GenerateReverseData(int a[], int n);
void GenerateNearlySortedData(int a[], int n);

/*
    Parameters:
    +inputSize <int> - the size of the input
    +inputOrder<string>  -rand, -sorted, -rev, -nsorted
    Output: 0 if successful, -1 if failed
    File format:
        line 1: size of the input
        line 2: each element of the input is separated by a space
*/
int Gen_Data_File(int inputSize, string inputOrder, string fileName){
    string filePath;
    int* arr = new int[inputSize];

    //Random
	if(inputOrder == "-rand")
		GenerateRandomData(arr, inputSize);
	//Nearly sorted
	else if(inputOrder == "-nsorted")
		GenerateNearlySortedData(arr, inputSize);
	//Sorted
	else if(inputOrder == "-sorted")
		GenerateSortedData(arr, inputSize);
	//Reverse
	else if(inputOrder == "-rev")
		GenerateReverseData(arr, inputSize);
	else
	{
		cout << "Invalid input order" << endl;
		delete[] arr;
		return -1;
	}

	//Write to file
	filePath = fileName;
	ofstream file(filePath.c_str());
	if(file.is_open())
	{
		file << inputSize << endl;
		for(int i = 0; i < inputSize; i++)
		{
			file << arr[i] << " ";
		}
		file.close();
	}
	else
	{
		cout << "Unable to open file" << endl;
		delete[] arr;
		return -1;
	}
	return 0;
}

// Hàm phát sinh mảng dữ liệu ngẫu nhiên
void GenerateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand()%n;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void GenerateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự ngược (giảm dần)
void GenerateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void GenerateNearlySortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int) time(NULL));
	for (int i = 0; i < 10; i ++)
	{
		int r1 = rand()%n;
		int r2 = rand()%n;
		swap(a[r1], a[r2]);
	}
}
