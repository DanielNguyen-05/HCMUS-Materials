#include <iostream>
#include <stack>
#include <string>

int calculate(int a, int b, char op) {
    if (op == '+') return a + b;
    else if (op == '-') return a - b;
    else if (op == '*') return a * b;
    else return a / b;
    return 0;
}

int evaluateExpression(std::string expr) {
    std::stack<int> values;
    std::stack<char> ops;

    for (int i = 0; i < expr.length(); i++) {
        if (isdigit(expr[i])) {
            int value = 0;
            while (i < expr.length() && isdigit(expr[i])) {
                value = (value * 10) + (expr[i] - '0');
                i++;
            }
            values.push(value);
            i--;
        } 
        else if (expr[i] == ' ') continue;
        else {
            while (!ops.empty() && ((ops.top() == '*' || ops.top() == '/') || (expr[i] == '+' || expr[i] == '-'))) {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(calculate(val1, val2, op));
            }
            ops.push(expr[i]);
        }
    }

    while (!ops.empty()) {
        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(calculate(val1, val2, op));
    }
    return values.top();
}

void generateExpressions(int* a, int n, int k, std::string expression, int target) {
    if (k == n) {
        if (evaluateExpression(expression) == target) {
            std::cout << expression << " = " << target << std::endl;
        }
        return;
    }

    generateExpressions(a, n, k + 1, expression + " + " + std::to_string(a[k]), target);
    generateExpressions(a, n, k + 1, expression + " - " + std::to_string(a[k]), target);
    generateExpressions(a, n, k + 1, expression + " * " + std::to_string(a[k]), target);
    if (a[k] != 0) generateExpressions(a, n, k + 1, expression + " / " + std::to_string(a[k]), target);
}

int main() {
    int n, x;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;

    int* a = new int[n];
    std::cout << "Enter the numbers: ";
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::cout << "Enter a number X: ";
    std::cin >> x;

    generateExpressions(a, n, 1, std::to_string(a[0]), x);

    delete[] a;
    return 0;
}