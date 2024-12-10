#include <iostream>
#include <string>
#include <fstream>
#include <stack>
using namespace std;

bool isExpressionBalanced(string input) {
    char x;
    stack<char> s;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '(' || input[i] == '[' || input[i] == '{') {
            s.push(input[i]);
            continue;
        }
        if (s.empty()) return false;
        switch (input[i]) {
            case ')':
                x = s.top();
                s.pop();
                if (x == '[' || x == '{') return false;
                break;
            case ']':
                x = s.top();
                s.pop();
                if (x == '(' || x == '{') return false;
                break;
            case '}':
                x = s.top();
                s.pop();
                if (x == '(' || x == '[') return false;
                break;
        }
    }
    if (s.empty()) return true;
    return false;
}

int main() {
    string s;
    cout << "Input the poly: ";
    getline(cin, s);
    if (isExpressionBalanced(s)) cout << "Yes";
    else cout << "No";
    return 0;
}
