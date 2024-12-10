#include <iostream>
#include <algorithm>

using namespace std;

int* addElement (int* a, int n, int data) {
    int* tmp = new int [n + 1];

    for (int i = 0; i < n; i++) {
        tmp[i] = a[i];
    }

    tmp[n] = data;
    delete []a;

    return tmp;
}

int findDif(int** a, int n, int* b) {
    int min = 0;
    int max = 0;

    for (int i = 0; i < b[0]; i++) {
        min += a[0][i];
        max += a[0][i];
    }

    for (int i = 1; i < n; i++) {
        int tmax = 0;
        int tmin = 0;
        for (int j = 0; j < b[i]; j++) {
            tmax += a[i][j];
            tmin += a[i][j];
        }

        if (tmin < min) min = tmin;
        if (tmax > max) max = tmax;
    }
    return max - min;
}

int** copyMatrix (int** a, int m, int* num) {
    int** tmp = new int* [m];

    for (int i = 0; i < m; i++) {
        tmp[i] = new int [num[i]];
        for (int j = 0; j < num[i]; j++) {
            tmp[i][j] = a[i][j];
        }
    }
    return tmp;
}

void deallocateMatrix(int** &a, int m) {
    for (int i = 0; i < m; i++) {
        delete []a[i];
    }

    delete []a;
}

void copyArray (int* a, int* b, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = b[i];
    }
}

// lấy từng tờ tiền chia cho từng ngưởi một cho tới khi hết
void solve (int miners, int notes[], int nNote, int index, int &dif, int** tmp, int* num, int** &result, int* &ans) {
    if (index == nNote) {
        int tdif = findDif(tmp, miners, num);
        if (tdif < dif) {
            dif = tdif;
            deallocateMatrix(result, miners);
            result = tmp;
            copyArray(ans, num, miners);
        } else {
            deallocateMatrix(tmp, miners);
        }

        return;
    }

    for (int i = 0; i < miners; i++) {
        int** tem = copyMatrix(tmp, miners, num);
        tem[i] = addElement(tem[i], num[i], notes[index]);
        num[i]++;
        solve(miners, notes, nNote, index + 1, dif, tem, num, result, ans);
        num[i]--;
    }

    deallocateMatrix(tmp, miners);
}

// mang chua sl note moi miner, mang chua tong tien moi miner

int main() {
    // int miners = 2;
    // int notes[] = {3, 6, 15, 16, 21};
    // int nNote = 5;
    // int dif = 61;
    // int** tmp = new int* [miners];
    // int* num = new int [miners];
    // int** result = new int* [miners];
    // // for (int i = 0; i < miners; i++){
    // //     tmp[i] = nullptr;
    // //     result[i] = nullptr;
    // // }
    // std::fill_n(num, miners, 0);
    // int* ans = new int [miners];
    // solve(miners, notes, nNote, 0, dif, tmp, num, result, ans);

    // for (int i = 0; i < miners; i++) {
    //     cout << "Miner " << i + 1 << ": ";
    //     for (int j = 0; j < ans[i]; j++) {
    //         cout << result[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "Difference: " << dif << endl;
    //int** a = new int* [10];
    int* b;
    delete b;
    return 0;
}













































// #include <iostream>
// using namespace std;
// const int MAX = 15;

// void solve(int a[], int n, int k, int &distance, int x[], int MAX_MONEY, int *ans){
//     int money[k + 1] = {0}, Max = 0, Min = 1e9;
//     for (int i = 0; i < n; i++) money[a[i]] += x[i];
//     // tìm xem người nhiều nhất và ít nhất là bao nhiều tiền
//     for (int i = 1; i <= k; i++) {
//         if (money[i] < Min) Min = money[i];
//         if (money[i] > Max) Max = money[i];
//     }
//     //kiểm tra độ chênh lệch có thỏa điều kiện hay không
//     if (distance > Max - Min) {
//         for (int i = 0; i < n; i++) ans[i] = a[i];
//         distance = Max - Min;
//     }
// }
// void find(int n, int k, int a[], int j, int &distance, int x[], int MAX_MONEY, int *ans){
//     if (j >= n) solve(a, n, k, distance, x, MAX_MONEY, ans);
//     else {
//         for (int i = 1; i <= k; i++) {
//             a[j] = i;
//             // nếu đã sinh đủ số lượng thì đi kiểm tra xem điều kiện
//             if (j == n - 1) solve(a, n, k, distance, x, MAX_MONEY, ans);
//             // nếu chưa đủ số lượng yêu cầu thì tìm tiếp kiểm tra
//             else find(n, k, a, j + 1, distance, x, MAX_MONEY, ans);
//         }
//     }
// }
// int main()
// {
//     int MAX_MONEY = 0, n, k, x[MAX], a[MAX], ans[MAX];
//     cin >> n >> k;
//     for (int i = 0; i < n; i++) {
//         cin >> x[i]; MAX_MONEY += x[i];
//     }
//     int distance = MAX_MONEY;
//     //tìm kiếm xem số cách chia tiền từ đó kiểm tra điều kiện cần thỏa đề bài
//     find(n, k, a, 0, distance, x, MAX_MONEY, ans);
//     // in ra số tiền của mỗi người có thể chia
//     for (int i = 1; i <= k; i++){
//         cout << "Miner " << i << " : ";
//         for (int j = 0; j < n; j++)
//             if (ans[j] == i) cout << x[j] << " ";
//         cout << endl;
//     }
//     // in ra khoảng cách giữa người cao nhất và ít nhất
//     cout <<  distance;
// }