#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

vector<vector<int>> readFile1(string filename)
{
	vector<vector<int>> adjList;
	ifstream ifs(filename);
	if(!ifs.is_open())
	{
		cout << "file error";
		return adjList;
	}
	int n;
	ifs >> n;
	for(int i = 0; i < n; i++)
	{
		vector<int> tmp;
		for(int j = 0; j < n; j++)
		{
			int num;
			ifs >> num;
			if(num) tmp.push_back(j);
		}
		adjList.push_back(tmp);
	}
	return adjList;
}

void printMatrix(vector<vector<int>> matrix)
{
	for(int i = 0; i < matrix.size(); i++)
	{
		for(int j = 0; j < matrix[i].size(); j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

vector<vector<int>> readFile2(string filename)
{
	vector<vector<int>> res;
	ifstream ifs(filename);
	if(!ifs.is_open())
	{
		cout << "file error";
		return res;
	}
	
	string tmp;
	getline(ifs, tmp);
	int n = atoi(tmp.c_str());
	for(int i = 0; i < n; i++)
	{
		vector<int> row (n, 0);
		
		getline(ifs, tmp);
		stringstream s(tmp);
		while (s >> tmp) {
            row[atoi(tmp.c_str())] = 1;
        }
		
		res.push_back(row);
	}
	return res;
}

bool isDirected(vector<vector<int>> matrix)
{
	int size = matrix.size();
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(matrix[i][j] != matrix[j][i]) return true;
		}
	}
	return false;
}

int edgesNumber(vector<std::vector<int>> matrix)
{
	int size = matrix.size();
	int cnt = 0;
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(matrix[i][j]) cnt++;
		}
	}
	return cnt;
}

int verticesNumber(vector<std::vector<int>> matrix)
{
	int size = matrix.size();
	int cnt = 0;
	
	vector<int> occur(size);

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(matrix[i][j]) 
			{
				occur[i] = occur[j] = 1;
			}
		}
	}
	for (int i = 0; i < size;i ++)
		cnt += occur[i];
	return cnt;
}

void undirectDegree(vector<vector<int>> matrix)
{
	int size = matrix.size();
	vector<int> degree(size, 0);
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(matrix[i][j]) degree[j]++;
		}
	}
	
	for(int i = 0; i < size; i++)
		cout << "Degree of the vertice " << i << " :" << degree[i] << endl;
}

void directDegree(vector<vector<int>> matrix)
{
	int size = matrix.size();
	vector<int> in(size, 0);
	vector<int> out(size, 0);
	
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(matrix[i][j])
			{
				in[j]++;
				out[i]++;
			}
		}
	}
	
	for(int i = 0; i < size; i++)
		cout << "Degree of the vertice " << i <<
		 " (in|out): " << in[i] << "|" << out[i] << endl;
}

void printIsolated(vector<vector<int>> adjMatrix)
{
    int size = adjMatrix.size();
    for(int i = 0; i < size; i++)
    {
        bool isolated = true;
        for(int j = 0; j < size; j++)
        {
            if(adjMatrix[i][j] || adjMatrix[j][i])
            {
            	isolated = false;
                break;
			}
        }
        if(isolated) cout << i << " is isolated vertices" << endl;
    }
}

void printLeaf(vector<vector<int>> matrix)
{
	int size = matrix.size();
	vector<int> out(size, 0);
	
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(matrix[i][j])
			{
				out[i]++;
			}
		}
	}
	
	for(int i = 0; i < size; i++)
	{
		if(!out[i]) cout << i << " is leaf vertices\n";
	}
}

bool isCyclicUntil(int cur, vector<vector<int>> matrix, vector<int> visited, vector<int> stack)
{
	if(!visited[cur])
	{
		stack[cur] = 1;
		visited[cur] = 1;
	}
	
	for(int i = 0; i < matrix[cur].size(); i++)
	{
		if(!visited[i] && isCyclicUntil(i, matrix, visited, stack))
			return true;
		if(stack[i]) return true;
	}
	return false;
}

bool isCyclic(vector<vector<int>> matrix)
{
	int size = matrix.size();
	vector<int> stack(size, 0);
	vector<int> visited(size, 0);
	
	for(int i = 0; i < size; i++)
	{
		if(!visited[i] && isCyclicUntil(i, matrix, visited, stack))
			return true;
	}
	return false;
}

bool isComplete(vector<vector<int>> matrix)
{
	int size = matrix.size();
	int cnt = 0;
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(matrix[i][j] && matrix[j][i]) cnt++;
			else return false;
		}
	}
	int expected = (size * (size + 1)) / 2;
	return expected == cnt;
}

int main()
{
	std::vector<std::vector<int>> undirected = {
        {0, 0, 1, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 0, 0},
        {1, 0, 0, 1, 1, 0, 0, 1, 0},
        {0, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 0}
    };
	//vector<vector<int>> adjList = readFile1("graph1.txt");
	vector<vector<int>> adjMatrix = readFile2("graph2.txt");
	if(isDirected(undirected)) cout << "directed\n";
	else cout << "no\n";
	cout << verticesNumber(adjMatrix) << " "
	<< verticesNumber(undirected) << endl;
	undirectDegree(undirected);
	directDegree(adjMatrix);
	printIsolated(adjMatrix);
	printLeaf(adjMatrix);
	if(isCyclic(adjMatrix)) cout << "cyclic graph\n";
	if(isComplete(adjMatrix)) cout << "complete\n";
	else cout << "not complete\n";
	//if(isBigraph(adjMatrix)) cout << "bigraph\n";
	//printMatrix(undirected);
	return 0;	
}
