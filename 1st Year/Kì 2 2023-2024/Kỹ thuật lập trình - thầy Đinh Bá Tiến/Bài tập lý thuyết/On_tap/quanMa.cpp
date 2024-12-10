// #include<iostream>
// #include<stdio.h>
// #define MAX 8
// using namespace std;

// int A[MAX][MAX] = { 0 };//Khởi tạo mảng giá trị 0
// int X[8] = { -2,-2,-1,-1, 1, 1, 2, 2};
// int Y[8] = { -1, 1,-2, 2,-2, 2,-1, 1};
// int dem = 0;
// int n;

// void xuat() {
// 	for (int i = 0; i < n; i++) {
// 		for (int j = 0; j < n; j++)
// 			printf("%2d ", A[i][j]);
// 		cout << endl;
// 	}
// 	cout << endl;
// }

// void diChuyen(int x, int y) {
// 	++dem;
// 	A[x][y] = dem;
// 	for (int i = 0; i < 8; i++)	{
// 		if (dem == n * n) {
// 			cout << "Cac buoc di la: \n";
// 			xuat();
//             exit(0);
// 		}
// 		int u = x + X[i];
// 		int v = y + Y[i];
// 		if (u >= 0 && u < n&&v >= 0 && v < n&& A[u][v] == 0)
// 			diChuyen(u, v);
// 	}
// 	--dem;
// 	A[x][y] = 0;
// }
// int main() {
// 	cout << "Nhap n: ";
// 	cin >> n;
// 	int a, b;
// 	cout << "Nhap vi tri ban dau.nx: ";
// 	cin>>a;
// 	cout << "y: ";
// 	cin >> b;
// 	diChuyen(a, b);
// 	cout << "Khong tim thay duong di.";
// }

#include <iostream>
using namespace std;

void print(int n, int** a) {
    cout << "The chessboard is: \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void moveHorse (int x, int y, int k, int n, int** &a, int X[], int Y[]) {
    k++;
    a[x][y] = k;
    if (k == n * n) {
        print(n, a);
        exit(0);
    }
    for (int i = 0; i < n; i++) {
        int u = x + X[i];
        int v = y + Y[i];
        if (u >= 0 && v >= 0 && u < n && v < n && a[u][v] == 0) {
            moveHorse(u, v, k , n, a, X, Y);
        }
    }
    k--;
    a[x][y] = 0;
} 

int main() {
    int n;
    cout << "Input the size of chessboard n x n: "; cin >> n;
    int** a = new int*[n];
    for (int i = 0; i < n; i++) {
        a[i] = new int[n];
        for (int j = 0; j < n; j++) {
            a[i][j] = 0;
        }
    }
    int X[8] = { -2, -2, -1, -1, 1, 1, 2, 2 };
    int Y[8] = { -1, 1, -2, 2, -2, 2, -1, 1 };
    int x, y;
    cout << "Input the starting position x: "; cin >> x;
    cout << "Input the starting position y: "; cin >> y;
    moveHorse(x, y, 0, n, a, X, Y);

    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;
    return 0;
}