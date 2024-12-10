#include <iostream>
#include <string>

// if the first operator is */ and the second operator is +- => do the first
// if the first operator is +- and the second operator is */ => do the second
// if the first operator is */ and the second operator is */ => do the first
// the same for the second operator is +- and the first operator is +- => do the first

void placingOperators(int* a, int n, int x, int result, int index, std::string expression) {
    if (index == n) {
        if (result == x) std::cout << "\n" << expression << " = " << x;
        return;
    }

    placingOperators(a, n, x, result + a[index], index + 1, expression + " + " + std::to_string(a[index]));

    placingOperators(a, n, x, result - a[index], index + 1, expression + " - " + std::to_string(a[index]));

    placingOperators(a, n, x, result * a[index], index + 1, expression + " * " + std::to_string(a[index]));

    if (a[index] != 0) placingOperators(a, n, x, result / a[index], index + 1, expression + " / " + std::to_string(a[index]));
}

int main() {
    int n;
    std::cout << "Enter the number of elements in the array: ";
    std::cin >> n;

    int* a = new int[n];
    std::cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    int x;
    std::cout << "Enter the target number: ";
    std::cin >> x;

    std::cout << "Possible expressions to obtain " << x << ": " << "";
    placingOperators(a, n, x, a[0], 1, std::to_string(a[0]));

    delete[] a;

    return 0;
}
