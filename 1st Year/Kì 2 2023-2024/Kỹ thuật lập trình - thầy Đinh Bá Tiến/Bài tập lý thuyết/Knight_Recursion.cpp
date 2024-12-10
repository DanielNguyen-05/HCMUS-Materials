#include<iostream>
using namespace std;

#define N 8

void printSolution(int sol[N][N]) {
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            std::cout << "  " << sol[x][y];
        }
        std::cout << "\n";
    }
}

bool isSafe(int x, int y, int sol[N][N]) {
    return (x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1);
}

bool solveKnight(int sol[N][N], int N, int moveX[N], int moveY[N]) {
    if (move == N*N) {  

    }

    for (int i = 0; i < 8; i++) {
        int nextX = x + moveX[i];
        int nextY = y + moveY[i];
        if (isSafe(nextX, nextY, sol)) {
            sol[nextX][nextY] = move;
            solveKnight(nextX, nextY, move+1, sol, moveX, moveY);
            sol[nextX][nextY] = -1;
        }
    }
}

int main() {
    int sol[N][N];
    int moveX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int moveY[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            sol[x][y] = -1;
        }
    }

    sol[0][0] = 0;
    solveKnight(0, 0, 1, sol, moveX, moveY);
    return 0;
}