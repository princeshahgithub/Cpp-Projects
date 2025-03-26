#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Calculation {
    string expression;
    double result;
};

vector<Calculation> history;

void saveHistory(const string &exp, double res) {
    history.push_back({exp, res});
}

double basicOperations(double num1, char op, double num2) {
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num2 != 0 ? num1 / num2 : NAN;
        default: return NAN;
    }
}

double scientificOperations(int choice, double num) {
    switch (choice) {
        case 1: return sqrt(num);
        case 2: return log(num);
        case 3: return exp(num);
        case 4: return sin(num);
        case 5: return cos(num);
        case 6: return tan(num);
        default: return NAN;
    }
}

void equationSolver() {
    double num1, num2, result;
    char op;

    cout << "Enter expression (e.g., 5 + 3): ";
    cin >> num1 >> op >> num2;

    auto start = high_resolution_clock::now();
    result = basicOperations(num1, op, num2);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    
    if (!isnan(result)) {
        cout << "Result: " << result << " (Computed in " << duration.count() << " microseconds)\n";
        saveHistory(to_string(num1) + " " + op + " " + to_string(num2), result);
    } else {
        cout << "Invalid calculation!\n";
    }
}

void scientificMenu() {
    int choice;
    double num, result;

    cout << "\n1. Square Root\n2. Logarithm\n3. Exponential\n4. Sine\n5. Cosine\n6. Tangent\n";
    cout << "Enter choice: ";
    cin >> choice;
    cout << "Enter number: ";
    cin >> num;

    auto start = high_resolution_clock::now();
    result = scientificOperations(choice, num);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);

    if (!isnan(result)) {
        cout << "Result: " << result << " (Computed in " << duration.count() << " microseconds)\n";
        saveHistory("Scientific Op: " + to_string(num), result);
    } else {
        cout << "Invalid operation!\n";
    }
}

void viewHistory() {
    if (history.empty()) {
        cout << "No history available!\n";
        return;
    }

    cout << "\nCalculation History:\n";
    for (const auto &h : history) {
        cout << h.expression << " = " << h.result << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n1. Solve Basic Equation\n2. Scientific Operations\n3. View History\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: equationSolver(); break;
            case 2: scientificMenu(); break;
            case 3: viewHistory(); break;
            case 4: return 0;
            default: cout << "Invalid choice! Try again.\n";
        }
    }
}
