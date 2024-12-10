#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstring> // For students who use char str[]

using namespace std;

// Struct declearation
struct Phone
{
    int ID;
    int version;
    int year;
};


// Problem 1-----------------------------------------------------------
void RemovePhone(Phone listPhone[], int &nPhone, int curYear)
{
    // TODO: YOUR CODE HERE

}


// Problem 2-----------------------------------------------------------
// 2.a
void ReadMap(int map[][100], int &m, int &n)
{
    // NOTE: DO NOT REMOVE THE FOLLOWING LINES
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            map[i][j] = 0;

    // TODO: YOUR CODE HERE

}

// 2.b
void Bomb(int map[][100], int m, int n, int r, int c, int v)
{
    // TODO: YOUR CODE HERE

}


// Problem 3-----------------------------------------------------------
// 3.a
void FindExt(string paths[], int nPath, string extName, string results[], int &nRes)
{
    // NOTE: Uncomment the following lines to convert std::string to cstring (char str[])
    //          Remove them if you just use std::string
    // char pathsChar[100][100];
    // char extNameChar[100];
    // char resultsChar[100][100];

    // for (int i = 0; i < nPath; i++)
    //     strcpy(pathsChar[i], paths[i].c_str());

    // strcpy(extNameChar, extName.c_str());



    // TODO: YOUR CODE HERE



    // NOTE: Convert cstring to std:string for the results
    // for (int i = 0; i < nRes; i++)
    //     results[i] = string(resultsChar[i]);
}

// 3.b
void Find(string paths[], int nPath, string curDir, string results[], int &nRes)
{
    // NOTE: Uncomment the following lines to convert std::string to cstring (char str[])
    //          Remove them if you just use std::string
    // char pathsChar[100][100];
    // char curDirChar[100];
    // char resultsChar[100][100];

    // for (int i = 0; i < nPath; i++)
    //     strcpy(pathsChar[i], paths[i].c_str());

    // strcpy(curDirChar, curDir.c_str());



    // TODO: YOUR CODE HERE



    // NOTE: Convert cstring to std:string for the results
    // for (int i = 0; i < nRes; i++)
    //     results[i] = string(resultsChar[i]);
}


int main()
{
    // Problem 1 ---------------------------------
    cout << "Problem 1:" << endl;
    Phone listPhone[100] = {{10, 9, 2019}, {20, 10, 2020}, {21, 11, 2021}, {22, 12, 2022}, {9, 8, 2018}};
    int nPhone = 5;
    int curYear = 2024;

    RemovePhone(listPhone, nPhone, curYear);
    
    cout << "List of phone's ID after removing: ";
    for (int i = 0; i < nPhone; i++)
        cout << listPhone[i].ID << " ";
    cout << endl;


    // Problem 2 ---------------------------------
    cout << endl << endl << "Problem 2:" << endl;
    int map[100][100] = {{0, 1, 2, 3, 4, 5},
                         {17, 18, 19, 20, 21, 6},
                         {16, 27, 28, 29, 22, 7},
                         {15, 26, 25, 24, 23, 8},
                         {14, 13, 12, 11, 10, 9}};
    int m = 5, n = 6;
    int r = 4, c = 0, v = 5;

    // 2.a. Read map from file
    // ReadMap(map, m, n); // You MUST UNCOMMENT this line if you implemented the function ReadMap.

    // 2.b. Bomb
    Bomb(map, m, n, r, c, v);

    cout << "The map after being bombed: " << endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            cout << map[i][j] << " ";
        cout << endl;
    }


    // Problem 3 ---------------------------------
    cout << endl << endl << "Problem 3:" << endl;
    string paths[100] = {"D:/Others/us/b.pdf", "C:/Users/c.txt", "C:/Users/adm/a.txt", "E:/temp/d.exe"};
    int nPath = 4;

    // 3.a. Find files with extension name
    string extName = "txt";
    string aResults[100];
    int anRes = 0;

    FindExt(paths, nPath, extName, aResults, anRes);

    cout << "The paths to files with extension name " << extName << ": ";
    for (int i = 0; i < anRes; i++)
        cout << aResults[i] << " ";

    // 3.b. Find folders and files in current directory
    string curDir = "C:/Users";
    string bResults[100];
    int bnRes = 0;

    Find(paths, nPath, curDir, bResults, bnRes);

    cout << endl << "The folders and files in " << curDir << " (alphabet order): ";
    for (int i = 0; i < bnRes; i++)
        cout << bResults[i] << " ";

    return 0;
}