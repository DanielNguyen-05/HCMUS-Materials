#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>

using namespace std;

void matrixToList(string filename1) {
    ifstream fin;
    fin.open(filename1);
    if (!fin.is_open()) {
        cout << "Cannot open thm film!";
        return;
    }
    int m;
    fin >> m;
    int** graph = new int*[m + 1];
    for (int i = 1; i <= m; i++) {
        graph[i] = new int[m + 1];
        for (int j = 1; j <= m; j++)
            fin >> graph[i][j];
    }
    fin.close();
    
    vector<vector<int> > v(m + 1);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            if (graph[i][j] == 1) // if the graph is undirected, we must have condition: i < j
                v[i].push_back(j);
        }
    }

    for (int i = 0; i <= m; i++) {
        delete[] graph[i];
    }
    delete[] graph;

    ofstream fout;
    fout.open("output1.txt");
    fout << m << "\n";
    for (int i = 1; i <= m; i++) {
        fout << i << ": ";
        for (int x : v[i]) 
            fout << x << " ";
        fout << "\n";
    }
    fout.close();
}

void listToMatrix (string filename2) {
    ifstream fin;
    int m; 
    fin >> m;
    
}

int main() {
    string filename1 = "graph1.txt";
    string filename2 = "graph2.txt";
    // matrixToList(filename1);
    listToMatrix(filename2);
    return 0;
}