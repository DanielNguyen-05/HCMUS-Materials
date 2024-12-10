#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
#include <queue>

using namespace std;

vector<vector<int>> convertMatrixToList(string filename){
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open()) {
		cout << "Error open file" << endl;
		return {};
	}
	int n;
	fin >> n;
	vector<vector<int>> matrix(n, vector<int>(n, 0));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			int tmp;
			fin >> tmp;
			matrix[i][j] = tmp;
		}
	}
	fin.close();
	vector<vector<int>> list(n);
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if (matrix[i][j] == 1) {
				list[i].push_back(j);
			}
		}
	}
	return list;
}

vector<vector<int>> convertListToMatrix(string filename){
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open()) {
		cout << "Cannot open the file!";
		return {};
	}
	string temp;
	getline(fin,temp);
	int n = stoi(temp);
	vector<vector<int>> list(n);
	vector<vector<int>> res (n, vector<int>(n, 0));
	for(int i = 0; i < n;i++){
		getline(fin, temp);
		if(!temp.empty()) {
			stringstream ss(temp);
			int neighbor = 0;
			while (!ss.eof()) {
				ss >> neighbor;
				list[i].push_back(neighbor);
			}
		}
	}
	fin.close();
	for (int i = 0; i < n ;i++) {
		for (int j = 0; j<list[i].size();j++) {
			res[i][list[i][j]] = 1;
		}
	}
	return res;
}

void printList(vector<vector<int>> list){
	for(int i = 0; i < list.size(); ++i){
		for(int j = 0 ; j < list[i].size(); ++j){
			cout << list[i][j] << " ";
		}
		cout << "\n";
	}
}

bool isDirectedMatrix(vector<vector<int>> matrix)
{
	int n = matrix.size();
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(matrix[i][j] != matrix[j][i]) return true;
		}
	}
	return false;
}

bool isDirectedList(vector<vector<int>> list) {
	for (int i = 0; i < list.size(); i++) {
		for (int j = 0; j < list[i].size(); j++) {
			int num = list[i][j];
			bool check = true;
			for (int k = 0; k < list[num].size(); k++) {
				if (list[num][k] == i) return false;
			}
		}
	}
	return true;
}

int cntEdgesAndNodes(vector<vector<int>> adj, int &numberOfNodes) {
	numberOfNodes = adj.size();
	int res = 0;
	for (int i = 0; i < adj.size(); i++) {
		for (int j = 0; j < adj[i].size(); j++) {
			res += adj[i][j];
		}
	}
	if (!isDirectedMatrix(adj)) return res  / 2; 
	return res;
}

int cntEdgesAndNodes_List(vector<vector<int>> adj, int &numberOfNodes) {
	numberOfNodes = adj.size();
	int res = 0;
	for (int i = 0; i < adj.size(); i++) {
		res += adj[i].size();
	}
	if (!isDirectedList(adj)) return res / 2;
	return res;
}

vector<int> degreeMatrix(vector<vector<int>> matrix) {
	vector<int> deg(matrix.size(), 0);
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix.size(); j++) {
			if (matrix[i][j] != 0) deg[i] += matrix[i][j];
		}
	}
	return deg;
}

vector<pair<int, int>> degreeMatrixDirected(vector<vector<int>> matrix) {
    vector<pair<int, int>> deg(matrix.size(), {0, 0});
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            if (matrix[i][j] != 0) {
                deg[i].first++;  // Increment out-degree of node i
                deg[j].second++; // Increment in-degree of node j
            }
        }
    }
    return deg;
}

vector<int> degreeList(vector<vector<int>> list) {
	vector<int> deg(list.size(), 0);
	for (int i = 0; i < list.size(); i++)
		deg[i] = list[i].size();
	return deg;
}

vector<pair<int, int>> degreeListDirected(vector<vector<int>> list) {
	vector<pair<int, int>> deg(list.size(), {0, 0});
	for (int i = 0; i < list.size(); i++) {
		deg[i].first = list[i].size();
		for (int j = 0; j < list[i].size(); j++) {
			deg[list[i][j]].second++;
		}
	}
	return deg;
}

vector<int> isolatedVerticeMatrix(vector<vector<int>> matrix) {
	vector<int> res;
	if (isDirectedMatrix(matrix)) {
		vector<pair<int, int>> v = degreeMatrixDirected(matrix);
		for (int i = 0; i < v.size(); i++) {
			if (v[i].first + v[i].second == 0) res.push_back(i);
		}
	}
	else {
		vector<int> p = degreeMatrix(matrix);
		for (int i = 0; i < p.size(); i++) {
			if (p[i] == 0) res.push_back(i);
		}
	}
	return res;
}

// optional
vector<int> isolatedVerMatrix(vector<vector<int>> matrix) {
	vector<int> res;
	for (int i = 0; i < matrix.size(); i++) {
		int degree = 0;
		for (int j = 0; j < matrix.size(); j++) {
			degree += matrix[i][j];
		}
		if (degree == 0) res.push_back(i);
	}
	return res;
}

vector<int> isolatedVerticeList(vector<vector<int>> list) {
	vector<int> res;
	if (isDirectedList(list)) {
		vector<pair<int, int>> v = degreeListDirected(list);
		for (int i = 0; i < v.size(); i++) {
			if (v[i].second + v[i].first == 0) res.push_back(i);
		}
	}
	else {
		vector<int> p = degreeList(list);
		for (int i = 0; i < p.size(); i++) {
			if (p[i] == 0) res.push_back(i);
		}
	}
	return res;
}

vector<int> isolatedLeafMatrix(vector<vector<int>> matrix) {
    vector<int> res;
    if (isDirectedMatrix(matrix)) {
        vector<pair<int, int>> degrees = degreeListDirected(matrix);
        for (int i = 0; i < degrees.size(); ++i) {
            if (degrees[i].first == 0 && degrees[i].second == 1 || degrees[i].first == 1 && degrees[i].second == 0)	
				res.push_back(i);
        }
	}
	else {
        vector<int> degrees = degreeMatrix(matrix);
        for (int i = 0; i < degrees.size(); ++i) {
            if (degrees[i] == 1) res.push_back(i);
        }
    }
    return res;
}

vector<int> isolatedLeafList(vector<vector<int>> list) {
    vector<int> res;
    if (isDirectedList(list)) {
        vector<pair<int, int>> degrees = degreeListDirected(list);
        for (int i = 0; i < degrees.size(); ++i) {
            if (degrees[i].first == 0 && degrees[i].second == 1 || degrees[i].first == 1 && degrees[i].second == 0)	
				res.push_back(i);
        }
	}
    else {
        vector<int> degrees = degreeList(list);
        for (int i = 0; i < degrees.size(); ++i) {
            if (degrees[i] == 1) res.push_back(i);
        }
    }
    return res;
}

bool isCompleteGraph(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        if (count(matrix[i].begin(), matrix[i].end(), 1) != n - 1) {
            return false;
        }
    }
    int expectedEdges = (n * (n - 1)) / 2;
    int actualEdges = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (matrix[i][j] == 1) {
                ++actualEdges;
            }
        }
    }
    return expectedEdges == actualEdges;
}

bool isCircularGraph(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        if (count(matrix[i].begin(), matrix[i].end(), 1) != 2) {
            return false;
        }
    }
    return true;
}

bool isBipartite(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<int> color(n, -1);
    
    for (int i = 0; i < n; ++i) {
        if (color[i] == -1) {
            queue<int> q;
            q.push(i);
            color[i] = 0;
            while (!q.empty()) {
                int node = q.front();
                q.pop();
                for (int j = 0; j < n; ++j) {
                    if (matrix[node][j] == 1) {
                        if (color[j] == -1) {
                            color[j] = 1 - color[node];
                            q.push(j);
                        } else if (color[j] == color[node]) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool isCompleteBipartiteGraph(const vector<vector<int>>& matrix) {
    if (!isBipartite(matrix)) {
        return false;
    }
    
    int n = matrix.size();
    vector<int> color(n, -1);
    vector<int> setSize(2, 0);
    
    for (int i = 0; i < n; ++i) {
        if (color[i] == -1) {
            queue<int> q;
            q.push(i);
            color[i] = 0;
            setSize[0]++;
            while (!q.empty()) {
                int node = q.front();
                q.pop();
                for (int j = 0; j < n; ++j) {
                    if (matrix[node][j] == 1) {
                        if (color[j] == -1) {
                            color[j] = 1 - color[node];
                            setSize[color[j]]++;
                            q.push(j);
                        }
                    }
                }
            }
        }
    }
    
    int m = setSize[0];
    int n = setSize[1];
    int expectedEdges = m * n;
    int actualEdges = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (matrix[i][j] == 1) {
                ++actualEdges;
            }
        }
    }
    return expectedEdges == actualEdges;
}

vector <vector <int>> matToAdj(vector <vector <int>> mat) {
	int n = mat.size();
	vector <vector <int>> ans(n);
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < n; j ++)
			if (mat[i][j])
				ans[i].push_back(j);
	return ans;
}

// int numberComponents(const vector <vector <int>> adj) {
// 	int n = adj.size();
// 	vector <> vis(n, false);
// 	auto dfs = [&](int p, int u) {

// 	}
// }