#include <iostream>
#include <queue>

struct Cell {
	int rows;
	int cols;
	int distance;
};

bool isValid (int cur_row, int cur_col, int** a, int n, int m, bool** check) {
	return (cur_row >= 0 && cur_row < n && cur_col >= 0 && cur_col < m && a[cur_row][cur_col] == 0 && check[cur_row][cur_col] == false);
}

int findPath (int** a, int n, int m, int start_row, int start_col, int target_row, int target_col, bool** check, int move_row[], int move_col[]) {
	std::queue<Cell> q;
	Cell start_cell = {start_row, start_col, 0};
	q.push(start_cell);

	while (!q.empty()) {
        Cell cur = q.front();
        check[cur.rows][cur.cols] = true;
        q.pop();

        if (cur.rows == target_row && cur.cols == target_col) return cur.distance;

        for (int i = 0; i < 4; i++) {
            int new_row = cur.rows + move_row[i];
            int new_col = cur.cols + move_col[i];

            if (!isValid(new_row, new_col, a, n, m, check)) continue;

            Cell new_cell = {new_row, new_col, cur.distance + 1};
            q.push(new_cell);
        }
    }
    return -1;
}

int main() {
	int n, m;
	std::cout << "Input the size of the n x m array: ";
	std:: cin >> n >> m;

	int** a = new int*[n];
	std::cout << "Input the 2D array: " << "\n";
	for (int i = 0; i < n; i++) {
		a[i] = new int[m];
		for (int j = 0; j < m; j++) {
			std::cin >> a[i][j];
		}
	}

	int start_row, start_col, target_row, target_col;
	std::cout << "Input the starting point: ";
	std::cin >> start_row >> start_col;
	std::cout << "Input the target point: ";
	std::cin >> target_row >> target_col;
	
	bool** check = new bool*[n];
	for (int i = 0; i < n; i++) {
		check[i] = new bool[m];
		for (int j = 0; j < m; j++) {
			check[i][j] = false;
		}
	}

	int move_row[] = {0, 0, 1 ,-1};
	int move_col[] = {-1, 1, 0, 0};

    int shortest_path = findPath (a, n, m, start_row, start_col, target_row, target_col, check, move_row, move_col);
    std::cout << "The number of steps is: " << shortest_path;

	for (int i = 0; i < n; i++) {
		delete[] a[i];
		delete[] check[i];
	}
	delete[] a;
	delete[] check;

    return 0;
}