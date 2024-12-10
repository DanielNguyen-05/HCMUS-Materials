#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

struct Stadium{
    string name; 
    int capacity;
    string city; 
    string club; 
    int *reno;
    int num_reno;
    int record_att;
    string record_game;
    int record_year;
    string address;

    Stadium(){
        reno = NULL;
    }
};

struct pNode{
	Stadium stadium;
	pNode* left;
	pNode* right;
	int height;
	
	pNode(Stadium s){
		stadium = s;
		left = NULL;
		right = NULL;
		height = 1;
	}
};

//Read the file
bool checkLetter(const string& str);
int safeStoi(const string& s);
void readFile(string fileName, vector<Stadium>& stadium);
string remove_delemeter(string str);
string remove_space(string str);
string remove_quote(string str);

//Create AVL tree
pNode* Create(Stadium s);
int Height(pNode* root);
int Compare(Stadium f1, Stadium f2);
int compare2(pNode* root);
pNode* Right_Rotate(pNode* n);
pNode* Left_Rotate(pNode* n);
int Balance_Factor(pNode* n);
void Insert(pNode* &root, Stadium x);

string getSecond(string s);

//P1b
pNode* createPlayerAVL(string filename);

//P1c
void visitTree(pNode* root);
void printAVL(pNode *root);

//P1d
pNode* minValueNode(pNode* node);
void Delete(pNode* &root, Stadium x);
void removeNodes(pNode *&root);


vector<vector<int>> solution(vector<vector<int>> adj);

int main (){
	string filename = "stadium.csv";
	pNode* root = createPlayerAVL(filename);
	removeNodes(root);
	printAVL(root);


	return 0;
}

string getSecond(string s) {
	string ans = "";
	for (int i = 2; i < s.size(); i++) {
		if (s[i - 2] == '-' || (s[i - 1] == '-' && s[i] != ' ')) ans += s[i];
	}
	return ans;
}

bool checkLetter(const string& str){
	for(int i = 0; i < str.size(); i ++){
		if(isalpha(str[i])) return true;
	}	
	return false;
}

int safeStoi(const string& s) {
	if(checkLetter(s)){
		return 0;
	}else{
		return stoi(s);
	}
}

int compare2(pNode* node) {
	if (node->stadium.club[0] == 'A'|| node->stadium.club[0] == 'E' || node->stadium.club[0] == 'I' || node->stadium.club[0] == 'O' || node->stadium.club[0] == 'U' || node->stadium.club[0] == 'Y') return 1;
	return 0;
}

string remove_delemeter(string str){ 
    std::string res = str;
    //Remove spaces
    int l = res.length(); 
    int c = count(res.begin(), res.end(), ' '); 
    remove(res.begin(), res.end(), ' '); 
    res.resize(l - c); 
    //Remove comma
    l = res.length();
    c = count(res.begin(), res.end(), ',');
    remove(res.begin(), res.end(), ',');
    res.resize(l - c);
    //Return quote
    l = res.length();
    c = count(res.begin(), res.end(), '\"');
    remove(res.begin(), res.end(), '\"');
    res.resize(l - c);

    return res;
}

string remove_space(string str){
    std::string res = str;
    //Remove spaces
    int l = res.length(); 
    int c = count(res.begin(), res.end(), ' '); 
    remove(res.begin(), res.end(), ' '); 
    res.resize(l - c); 
    
    return res;
}

string remove_quote(string str){
    std::string res = str;
    //Remove spaces
    int l = res.length(); 
    int c = count(res.begin(), res.end(), '\"'); 
    remove(res.begin(), res.end(), '\"'); 
    res.resize(l - c); 
    
    return res;
}

void readFile(string fileName, vector<Stadium>& stadium){
    ifstream fIn;
    fIn.open(fileName.c_str());
    std::string title;
    getline(fIn, title);
    while(!fIn.eof()){
        std::string plot;
        getline(fIn, plot);
        Stadium stad;
        istringstream ss(plot);

        //Read Stadium name
        std::string stadi;
        getline(ss, stadi, ',');
        if(stadi == "") break;
        int count_quoting = count(stadi.begin(), stadi.end(), '\"');
        if(count_quoting == 1){
            std::string addition;
            getline(ss, addition, ',');
            std::string total = remove_quote(stadi) + "," + remove_quote(addition);
            stad.name = total;
        }else{
            stad.name = stadi;
        }

        //Read capacity
        string cap;
        getline(ss, cap, ',');
        cap = remove_delemeter(cap);
        stad.capacity = safeStoi(cap);

        //Read City name
        getline(ss, stad.city, ',');

        //Read Club name
        std::string clb1;
        getline(ss, clb1, ',');
        int clb1_count = count(clb1.begin(), clb1.end(), '\"');
        if(clb1_count == 0) stad.club = clb1;
        else{
            std::string clb2;
            getline(ss, clb2, ',');
            clb2 = remove_quote(clb2);
            std::string clb = clb1 + "," + clb2;
        }

        //Read renovations
        string renovate_check;
        getline(ss, renovate_check, ',');
        if(renovate_check == ""){
            stad.num_reno = 0;
            stad.reno = NULL;
        }else{
            int renovate_check_count = count(renovate_check.begin(), renovate_check.end(), '\"');
            if(renovate_check_count == 0){
                stad.num_reno = 1;
                stad.reno = new int[stad.num_reno];
                stad.reno[0] = safeStoi(renovate_check);
            }else{
                vector<int> reno;
                reno.push_back(safeStoi(remove_delemeter(renovate_check)));
                while(true){
                    std::string reno_loop;
                    getline(ss, reno_loop, ',');
                    if(count(reno_loop.begin(), reno_loop.end(), '\"') == 1){
                        reno.push_back(safeStoi(remove_delemeter(reno_loop)));
                        break;
                    }else{
                        reno.push_back(safeStoi(reno_loop));
                    }
                }
                stad.num_reno = reno.size();
                stad.reno = new int[stad.num_reno];
                for(int i = 0; i < stad.num_reno; i ++){
                    stad.reno[i] = reno[i];
                }
            }
        } 
        //Read record attendance
        string rec;
        getline(ss, rec, ',');
        if(rec == ""){
            stad.record_att = 0;
            stad.record_game = rec;
            stad.record_year = 0;
        }else if(rec.size() == 3 || rec.size() == 2){
            string tmp;
            getline(ss, tmp, ',');
            rec = rec + "," + tmp;
            istringstream sst(rec);
            string att;
            getline(sst, att, '(');
            stad.record_att = safeStoi(remove_delemeter(att));
            std::string game;
            getline(sst, game);
            stad.record_game = game;

            std::string yr;
            getline(ss, yr, ',');
            int l = yr.length(); 
            int c = count(yr.begin(), yr.end(), ')'); 
            remove(yr.begin(), yr.end(), ')'); 
            yr.resize(l - c); 
            stad.record_year = safeStoi(remove_delemeter(yr));
        }else{
            if(count(rec.begin(), rec.end(), '\"') == 1){
                istringstream sst(rec);
                string att;
                getline(sst, att, '(');
                stad.record_att = safeStoi(remove_delemeter(att));
                std::string game;
                getline(sst, game);
                stad.record_game = game;

                std::string yr;
                getline(ss, yr, ',');
                int l = yr.length(); 
                int c = count(yr.begin(), yr.end(), ')'); 
                remove(yr.begin(), yr.end(), ')'); 
                yr.resize(l - c); 
                stad.record_year = safeStoi(remove_delemeter(yr));
            }else{
                istringstream sst(rec);
                string att;
                getline(sst, att, '(');
                stad.record_att = safeStoi(remove_delemeter(att));
                std::string game;
                getline(sst, game);
                stad.record_game = "(" + remove_quote(game);
                stad.record_year = 0;                
            }
        }

        //Read the address
        std::string add;
        getline(ss, add);
        if(add == "") stad.address = add;
        else{
            stad.address = remove_quote(add);
        }

        stadium.push_back(stad);
    }
    fIn.close();
}

pNode* Create(Stadium s){
    pNode* root = new pNode(s);
    return root;
}

//Get the height of the tree
int Height(pNode* root){
    if(root == NULL) return 0;
    else return root->height;
}

int Compare(Stadium f1, Stadium f2){
	string s1 = getSecond(f1.record_game);
	string s2 = getSecond(f2.record_game);
	if(s1 > s2) return 1;
	else if(s1 < s2) return -1;
	else{
		if(strcmp(f1.club.c_str(), f2.club.c_str()) > 0) return 1;
		else if(strcmp(f1.club.c_str(), f2.club.c_str()) < 0) return -1;
		else return 0;
	}
}

//Right Rotate
pNode* Right_Rotate(pNode* n){
    pNode* New = n->left;
    pNode* Temp = New->right;

    New->right = n;
    n->left = Temp;

    if(Height(n->left) >= Height(n->right)) n->height = 1 + Height(n->left);
    else n->height = 1 + Height(n->right);

    if(Height(New->left) >= Height(New->right)) New->height = 1 + Height(New->left);
    else New->height = 1 + Height(New->right);

    return New;
}

//Left Rotate
pNode* Left_Rotate(pNode* n){
    pNode* New = n->right;
    pNode* Temp = New->left;

    New->left = n;
    n->right = Temp;

    if(Height(n->left) >= Height(n->right)) n->height = 1 + Height(n->left);
    else n->height = 1 + Height(n->right);

    if(Height(New->left) >= Height(New->right)) New->height = 1 + Height(New->left);
    else New->height = 1 + Height(New->right);

    return New;
}

//Get balance factor
int Balance_Factor(pNode* n){
    if(n == NULL) return 0;
    return (Height(n->left) - Height(n->right));
}

//Insert
void Insert(pNode* &root, Stadium x){
    //Root is empty
    if(root == NULL){
        root = Create(x);
        return;
    }

    if(Compare(root->stadium, x) == 1) Insert(root->left, x);
    else if(Compare(root->stadium, x) == -1) Insert(root->right, x);
    else return;

    if(Height(root->left) >= Height(root->right)) root->height = Height(root->left) + 1;
    else root->height = Height(root->right) + 1;

    int factor = Balance_Factor(root);

    //Left heavy
    if(factor > 1){
        if(Compare(x, root->left->stadium) == -1) root = Right_Rotate(root);
        else{
            root->left = Left_Rotate(root->left);
            root = Right_Rotate(root);
        }
    }
    //Right heavy
    if(factor < -1){
        if(Compare(x, root->right->stadium) == 1) root = Left_Rotate(root);
        else{
            root->right = Right_Rotate(root->right);
            root = Left_Rotate(root);
        }
    }
}

pNode* createPlayerAVL(string fileName){
	pNode* root = NULL;
	vector<Stadium> stadium;
	readFile(fileName, stadium);
	for(int i = 0; i < stadium.size(); i ++){
		Insert(root, stadium[i]);
	}
	return root;
}

void visitTree(pNode* root) {
    cout << root->stadium.name << ", " << root->stadium.record_att << " (" << root->stadium.record_game << "), " << root->stadium.club << "\n";
}

// LNR
void printAVL(pNode* root) {
    if (root != NULL) {
        printAVL(root->left);
        visitTree(root);
        printAVL(root->right);
    }
}


pNode* minValueNode(pNode* node) {
    pNode* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

void Delete(pNode* &root){
    if(root == NULL) return;
    if(compare2(root) == 1){
        Delete(root->left);
    }else if (compare2(root) == 0){
        Delete(root->right);
    }


    // If the tree had only one node then return
    if (root == NULL) return;

    // Update the height of the current node
    root->height = 1 + std::max(Height(root->left), Height(root->right));

    // Get the balance factor of this node
    int factor = Balance_Factor(root);

    // Left heavy
    if (factor > 1) {
        if (Balance_Factor(root->left) >= 0) {
            root = Right_Rotate(root); // Left-Left (LL) case
        } else {
            root->left = Left_Rotate(root->left); // Left-Right (LR) case
            root = Right_Rotate(root);
        }
    }
    // Right heavy
    if (factor < -1) {
        if (Balance_Factor(root->right) <= 0) {
            root = Left_Rotate(root); // Right-Right (RR) case
        } else {
            root->right = Right_Rotate(root->right); // Right-Left (RL) case
            root = Left_Rotate(root);
        }
    }
}


void removeNodes(pNode* &root){
    if(root == NULL) return;
    // Process the left subtree first
    removeNodes(root->left);
    // Process the right subtree
    removeNodes(root->right);
	
}

vector<vector<int>> solution(vector<vector<int>> adj) {
	vector<vector<int>> ans = adj;
	for (int i = 0; i < ans.size() - 1; i++) {
		if(ans[i][i + 1] == 1) {
			ans.erase(ans.begin() + i);
			for (int j = i; j < ans.size(); j++) {
				ans[j].erase(ans[j].begin() + i);
			}
		}
	}
	return ans;
}





