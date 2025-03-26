#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

struct Expense {
    string category;
    float amount;
    string date;
};

vector<Expense> expenses;

void saveExpenses() {
    ofstream file("expenses.txt");
    if (!file) {
        cout << "Error saving data!\n";
        return;
    }
    for (const auto &e : expenses) {
        file << e.category << "," << e.amount << "," << e.date << "\n";
    }
    file.close();
}

void loadExpenses() {
    ifstream file("expenses.txt");
    if (!file) return;

    Expense e;
    while (file >> e.category >> e.amount >> e.date) {
        expenses.push_back(e);
    }
    file.close();
}

void addExpense() {
    Expense e;
    cout << "Enter Expense Category: ";
    cin >> e.category;
    cout << "Enter Amount: ";
    cin >> e.amount;
    cout << "Enter Date (YYYY-MM-DD): ";
    cin >> e.date;

    expenses.push_back(e);
    saveExpenses();
    cout << "Expense added successfully!\n";
}

void displayExpenses() {
    if (expenses.empty()) {
        cout << "No expenses recorded!\n";
        return;
    }

    cout << "\nRecorded Expenses:\n";
    cout << setw(15) << left << "Category" << setw(10) << "Amount"
         << setw(12) << "Date" << endl;
    cout << string(40, '-') << endl;

    for (const auto &e : expenses) {
        cout << setw(15) << left << e.category
             << setw(10) << e.amount
             << setw(12) << e.date << endl;
    }
}

void generateReport() {
    if (expenses.empty()) {
        cout << "No expenses recorded to generate a report!\n";
        return;
    }

    float total = 0;
    for (const auto &e : expenses) {
        total += e.amount;
    }

    cout << "\n Financial Report:\n";
    cout << "Total Expenses: $" << fixed << setprecision(2) << total << endl;
}

int main() {
    loadExpenses();
    int choice;

    while (true) {
        cout << "\n1. Add Expense\n2. Display Expenses\n3. Generate Report\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addExpense(); break;
            case 2: displayExpenses(); break;
            case 3: generateReport(); break;
            case 4: return 0;
            default: cout << "Invalid choice! Try again.\n";
        }
    }
}
