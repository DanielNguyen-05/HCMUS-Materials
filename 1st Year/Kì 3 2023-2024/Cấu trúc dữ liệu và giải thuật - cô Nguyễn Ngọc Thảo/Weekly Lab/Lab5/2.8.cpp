#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>

using namespace std;

vector<vector<int>> readFile1(string filename) {
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open()) {
		cout << "Cannot open file!";
		return {};
	}
	int n;
	fin >> n;
	vector<vector<int>> res(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int tmp;
			fin >> tmp;
			res[i][j] = tmp; 
		}
	}
	fin.close();
	
	vector<vector<int>> list(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (res[i][j] == 1) list[i].push_back(j);
		}
	}
	return list;
}

vector<vector<int>> readFile2(string filename) 
{
	fstream fIn(filename, ios::in);
	if (!fIn) {
		cout << "Cannot open file\n";
		return {};
	}
	int n;
	fIn >> n;
	fIn.ignore();
	vector<vector<int>> G(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		string tmp;
		getline(fIn, tmp);
		stringstream ss(tmp);
		int u;
		while (ss >> u) {
			G[i][u] = 1;
		}
	}
	return G;
}

bool checkDirected(vector<vector<int>> matrix)
{
	int n = matrix.size();
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(matrix[i][j] != matrix[j][i])
				return true;
	return false;
}
bool Find(vector<vector<int>> v, int i, int n){
	for(int j = 0; j < v[i].size(); j++){
		if(v[i][j] == n) return true;
	}
	return false;
}
bool checkDirected2(vector<vector<int>> list)
{
	int n = list.size();
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < list[i].size(); j++)
			if(Find(list, list[i][j], i) == false)
				return true;
	return false;
}

void countVE(vector<vector<int>> matrix, int &cntEdge, int &cntVertices)
{
	cntVertices = matrix.size();
	for (int i = 0; i < cntVertices; i++)
		for (int j = 0; j < cntVertices; j++)
			if (matrix[i][j])
				cntEdge++;
	if (!checkDirected(matrix))
		cntEdge /= 2;
			
}

void countVE2(vector<vector<int>> list, int &cntEdge, int &cntVertices)
{
	cntVertices = list.size();
	for(int i = 0; i < cntVertices; i++)
	{
		cntEdge += list[i].size();
	}
	if (!checkDirected2(list))
		cntEdge /= 2;
}

vector<int> degree(vector<vector<int>> mat, int v) {
	vector<int> res;
	
	if (checkDirected(mat)) {
		int out = 0;
		for (int i = 0; i < mat[v].size(); i++) {
			if (mat[v][i]) out++;
		}
		
		int in = 0;
		for (int i = 0; i <mat.size(); i++) {
			if (mat[i][v]) in++;
		}
		
		res.push_back(in);
		res.push_back(out);
	}
	else {
		int deg = 0;
		for (int i = 0; i < mat[v].size(); i++) {
			if (mat[v][i]) deg++;
		}
		res.push_back(deg);
	}
	
	return res;
}

vector <int> degree2(vector <vector <int>> list, int v) {
	vector <int> ans;
	ans.push_back(list[v].size()); // out degree goes first
	ans.push_back(0); // get in degree 0
	for (int i = 0; i < list.size(); i ++) {
		ans.back() += Find(list, i, v); // increase if found
	}
	return ans;
}

vector<int> isolatedVerticesMatrix(vector<vector<int>> matrix) {
	vector<int> res;
	for (int i = 0; i < matrix.size(); i++) {
		vector<int> deg = degree(matrix, i);
		if (deg[0] == 0 && deg.back() == 0) res.push_back(i);
	}
	return res;
}

vector<int> isolatedVerticesMatrix2(vector<vector<int>> list) {
	vector<int> res;
	for (int i = 0; i < list.size(); i++) {
		vector<int> deg = degree2(list, i);
		if (deg[0] == 0 && deg.back() == 0) res.push_back(i);
	}
	return res;
}

vector<int> leafVerticesMatrix(vector<vector<int>> mat) {
	vector<int> res;
	for (int i = 0; i < mat.size(); i++) {
		vector<int> deg = degree(mat, i);
		if (mat[i][i])
		{
			deg[0]--;
			if (deg.size() > 1) deg.back()--;
		}
		if (deg.size() > 1)
		{
			if (deg[0] == 1 && deg.back() == 0) res.push_back(i);
		}
		else 
		{
			if (deg[0] == 1) res.push_back(i);
		}
	}
	return res;
}


vector<int> leafVerticesList(vector<vector<int>> list) {
	vector<int> res;
	for (int i = 0; i < list.size(); i++) {
		vector<int> deg = degree2(list, i);
		for (int v: list[i]) 
			if (v == i) {
				deg[0]--;
				if (deg.size() > 1) deg.back()--;
			}
		if (checkDirected2(list)) 
		{
			if (deg[0] == 0 && deg.back() == 1) res.push_back(i);
		}
		else {
			if (deg[0] == 1) res.push_back(i);
		}
	}
	return res;
}
bool isCircular(vector<vector<int>> matrix){
	int n = matrix.size();
	for(int i = 0; i < n; i++){
		int cnt = 0;
		for(int j = 0; j < n; j++){
			if(i != j) cnt += matrix[i][j];
			else if(matrix[i][j]) return false;
			
		}
		if(cnt != 2) return false;
		
	}
	return true;
}

bool isCircular2(vector<vector<int>> list){
	int n = list.size();
	for(int i = 0; i < n; i++){
		vector<int> deg = degree2(list, i);
		if (deg[0] != 2) return false;
	}
	return true;
}


bool isBigraph(vector<vector<int> m)
{
	int n = m.size();
	vector<int> color(n, -1);
	for(int i = 0; i < n; i++)
	{
		queue<int> q;
		q.push(i);
		color[i] = 1;
		while(q.empty() == false)
		{
			int top = q.front();
			q.pop();
			for(int j = 0; j < n; j++)
			{
				if(m[top][j] == 1)
				{
					if(color[top] == color[j])
						return false;
					color[j] = 1 - color[top];
				}

			}
		}
	}
	return true;
}
bool isBigraph2(vector<vector<int> list)
{
	int n = m.size();
	vector<int> color(n, -1);
	for(int i = 0; i < n; i++)
	{
		queue<int> q;
		q.push(i);
		color[i] = 1;
		while(q.empty() == false)
		{
			int top = q.front();
			q.pop();
			for(int j : list[top])
			{
				
				if(color[top] == color[j])
					return false;
				color[j] = 1 - color[top];
			}
		}
	}
	return true;
}


bool isCompleteBigraph1(vector<vector<int> m)
{
	if (!isBigraph(m)) return false;
	int n = m.size();
	vector<int> color(n, -1);
	for(int i = 0; i < n; i++)
	{
		queue<int> q;
		q.push(i);
		color[i] = 1;
		while(q.empty() == false)
		{
			int top = q.front();
			q.pop();
			for(int j = 0; j < n; j++)
			{
				if(m[top][j] == 1)
				{
					if(color[top] == color[j])
						return false;
					color[j] = 1 - color[top];
				}

			}
		}
	}
	
	int n = m.size();
	int c1 = 0, c2 = 0;
	for (int i = 0; i < n; i ++) {
		if (color[i] == 1) c1 ++;
		if (color[i] == 0) c2 ++;
	}
	
	for (int i = 0; i < n; i ++) {
		int cnt = 0;
		for (int j = 0; j < n; j ++)
			if (m[i][j] && color[i] != color[j])
				cnt ++;
		if (color[i] == 0 && cnt != c1) return false;
		if (color[i] == 1 && cnt != c2) return false;
	}
	
	return true;
	
	return true;
}

bool isCompleteBigraph2(vector<vector<int> list)
{
	if (!isBigraph2(list)) return false;
	int n = m.size();
	vector<int> color(n, -1);
	for(int i = 0; i < n; i++)
	{
		queue<int> q;
		q.push(i);
		color[i] = 1;
		while(q.empty() == false)
		{
			int top = q.front();
			q.pop();
			for(int j : list[top])
			{
				
				if(color[top] == color[j])
					return false;
				color[j] = 1 - color[top];
			}
		}
	}
	
	int c1 = 0, c2 = 0;
	for (int i = 0; i < n; i ++) {
		if (color[i] == 1) c1 ++;
		if (color[i] == 0) c2 ++;
	}
	
	for (int i = 0; i < n; i ++) {
		int cnt = 0;
		for (int j: list[i])
			if (color[i] != color[j])
				cnt ++;
		if (color[i] == 0 && cnt != c1) return false;
		if (color[i] == 1 && cnt != c2) return false;
	}
	
	return true;
}


int main () {
	string filename1 = "graph2.txt";
	vector<vector<int>> list = readFile2(filename1);
	
	cout << list.size() << "\n";
	for (int i = 0; i < list.size(); i++) {
		for (int j = 0; j < list[i].size(); j++) {
			cout << list[i][j] << " ";
		}
		cout << "\n";
	}
//	int cntE= 0, cntV = 0;
//	countVE2(list, cntE, cntV);
//	cout << cntE << " " << cntV;
//	
	cout << endl;
	
	vector<int> a = leafVerticesList(list);
	for(auto i : a)
	{
		cout << i << " ";
	}
	cout << isCircular(list);
}
