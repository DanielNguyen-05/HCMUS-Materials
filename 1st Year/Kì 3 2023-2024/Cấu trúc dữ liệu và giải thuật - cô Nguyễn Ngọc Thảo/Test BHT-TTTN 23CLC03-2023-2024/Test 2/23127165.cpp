#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
using namespace std;

// cau 1
struct Stadium {
    string name;
    int capacity;
    string city;
    string club;
    int* reno;
    int num_reno;
    int record_att;
    string record_game;
    int record_year;
    string address;
};

struct pNode {
    Stadium data;
    pNode* left;
    pNode* right;
};

// Cau 2
void splitCSVLine(const string& csvLine, string outputFields[], int numFields);
void fixRecordAttendance(Stadium& stadium, string record_attendance);
void fixRenovation(Stadium& stadium, string renovation);
int fixCapacity(string capacity);
Stadium* readCSV(const string& filename, int& stadium_count);
void insertCity(pNode* &root, Stadium data);
pNode* makeTree(Stadium* stadiums, int stadium_count);
pNode* createBST(string filename);

// Cau 3
void visitTree(pNode* root);
void printBST(pNode* root);

// Cau 4
int recursive(pNode* root, int& count);
int countSubtree(pNode* root);

int main () {
	string filename = "stadium.csv";
	pNode* root = createBST(filename);
	int count = countSubTree(root);
	cout << count;
}

void splitCSVLine(const string& csvLine, string outputFields[], int numFields) {
    int index = 0;
    bool inQuotes = false;
    string currentField;

    for (size_t i = 0; i < csvLine.length(); ++i) {
        char c = csvLine[i];

        if (c == '"') {
            if (inQuotes && i + 1 < csvLine.length() && csvLine[i + 1] == '"') {
                // Escaped quote, add it to the field and skip the next quote
                currentField += '"';
                ++i;
            } else {
                inQuotes = !inQuotes;
            }
        } else if (c == ',' && !inQuotes) {
            if (index < numFields) outputFields[index++] = currentField;
            currentField.clear();
        } else {
            currentField += c;
        }
    }

    if (index < numFields) outputFields[index++] = currentField;

    // Clear any remaining fields
    while (index < numFields) {
        outputFields[index++] = "";
    }
}

void fixRecordAttendance(Stadium& stadium, string record_attendance) {
    if (record_attendance.empty()) return;
    int pos = 0;

    while (!isdigit(record_attendance[pos]))
        pos++;

    string input = record_attendance.substr(pos);
    pos = 0;
    
    string NumRecord;
    
    while (input[pos] != '(')
    	NumRecord += input[pos++];

	// fix number of attendance
	int pos1 = 0;
	for (int i = 0; i < NumRecord.size(); i++)
		if (NumRecord[i] != ' ' && NumRecord[i] != ',') NumRecord[pos1++] = NumRecord[i];
	NumRecord = NumRecord.substr(0, pos1);
    stadium.record_att = stoi(NumRecord);

    // fix game
    int endGame = input.size() - 2;
    while (isdigit(input[endGame])) 
    	endGame--;
    if (pos >= input.size()) return;
    pos++;
    string game;
    while (pos < endGame) {
		game += input[pos];
		pos++;
	}

    int len_game = game.size();
	if (game[len_game - 1] == ',') {
		game = game.substr(0, len_game - 1);
	}
    stadium.record_game = game;
	    
    // fix year
    string year;
    while (input[pos] != ')') {
		if (input[pos] != ' ') year += input[pos];
		pos++;
	}
    if (year.size() > 2) stadium.record_year = stoi(year);
    else {
        stadium.record_year = 0;
        stadium.record_game += ' ' + year;
    }
}

void fixRenovation(Stadium& stadium, string renovation) {
    if (renovation.size() == 0) return;
    int pos = 0;
    for (int i = 0; i < renovation.size(); i++)
        if (renovation[i] == ',') stadium.num_reno++;
    pos = 0;
    stadium.num_reno++;
    stadium.reno = new int[stadium.num_reno];
    string temp;
    for (int i = 0; i < renovation.size(); i++) {
        if (renovation[i] == ',') {
			stadium.reno[pos] = stoi(temp);
			temp.clear();
			pos++;
		}
        else temp += renovation[i];
	}
	stadium.reno[pos] = stoi(temp);
}

int fixCapacity(string capacity) {
	string result;
    for (int i = 0; i < capacity.size(); i++)
		if (capacity[i] != ' ') result += capacity[i];
	return stoi(result);
}

Stadium* readCSV(const string& filename, int& stadium_count) {
    Stadium* stadiums = new Stadium[125];
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Cannot open the file!" << "\n";
        return 0;
    }
    string line;
    getline(file, line); 
    int i = 0;
    while (getline(file, line)) {
        string fields[7];
        splitCSVLine(line, fields, 7);
        if (fields[0].empty()) continue;
        Stadium stadium;
        stadium.name = fields[0];
        stadium.capacity = fixCapacity(fields[1]);
        stadium.city = fields[2];
        stadium.club = fields[3];
        stadium.reno = NULL;
        stadium.num_reno = 0;
        stadium.record_att = 0;
        stadium.record_game = "";
        stadium.record_year = 0;
        fixRenovation(stadium, fields[4]);
        fixRecordAttendance(stadium, fields[5]);
        stadium.address = fields[6];
        stadiums[i++] = stadium;
    }
    file.close();
    stadium_count = i;

    return stadiums;
}

pNode* createpNode(Stadium data) {
    pNode* new_pNode = new pNode;
    new_pNode->data = data;
    new_pNode->left = NULL;
    new_pNode->right = NULL;
    return new_pNode;
}

void insertCity(pNode* &root, Stadium data) {
    pNode* new_pNode = createpNode(data);
    if (root == NULL) {
        root = new_pNode;
        return;
    }
    else if (data.city < root->data.city) insertCity(root->left, data);
    else if (data.city > root->data.city) insertCity(root->right, data);
	else {
		if (data.name < root->data.name) insertCity(root->left, data);
		else insertCity(root->right, data);
	}				    
}

pNode* makeTree(Stadium* stadiums, int stadium_count) {
    pNode* root = NULL;
    for (int i = 0; i < stadium_count; i++) {
        insertCity(root, stadiums[i]);
    }
    return root;
}

pNode* createBST(string filename) {
    int stadium_count = 0;
    Stadium* stadiums = readCSV(filename, stadium_count);
    pNode* root = makeTree(stadiums, stadium_count);
    return root;
}

void visitTree(pNode* root) {
	cout << root->data.name << ", " << root->data.city << ", " << root->data.address << "\n";
}

void printBST(pNode* root) {
    if (root == NULL) return;
    queue<pNode*> q;
    q.push(root);
    while (!q.empty()) {
        pNode* cur = q.front();
        q.pop();
        visitTree(cur);
        if (cur->left != NULL) q.push(cur->left);
        if (cur->right != NULL) q.push(cur->right);
    }
}

int recursive(pNode* root, int& count) {
    if (root == NULL) return 0;
    if (root->left != NULL && root->right != NULL) {
		if (root->data.city == root->left->data.city && root->left->data.city == root->right->data.city) count++;
	}
	return recursive(root->left, count) + recursive(root->right, count);
}

int countSubtree(pNode* root) {
    int count = 0;
    recursive(root, count);
    return count;
}

