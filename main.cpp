 //
//  main.cpp
//  Expences ( File handling )
//
//  Created by Nipuna Lakruwan
//

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

struct Expense {
    string description;
    double amount;
    time_t date;
    string category;
};

const string EXPENSES_FILE = "expenses.txt";

void saveExpenses(const vector<Expense>& expenses) {
    ofstream outFile(EXPENSES_FILE);

    if (!outFile.is_open()) {
        cerr << "Error opening expenses file for writing." << endl;
        return;
    }

    for (const auto& expense : expenses) {
        outFile << expense.description << "," << expense.amount << "," << expense.date << "," << expense.category << endl;
    }

    outFile.close();
}

vector<Expense> loadExpenses() {
    vector<Expense> expenses;
    ifstream inFile(EXPENSES_FILE);

    if (!inFile.is_open()) {
        cerr << "No existing expenses file found." << endl;
        return expenses;
    }

    while (!inFile.eof()) {
        Expense expense;
        getline(inFile, expense.description, ',');
        inFile >> expense.amount;
        inFile.ignore(); // Consume comma
        inFile >> expense.date;
        inFile.ignore(); // Consume comma
        getline(inFile, expense.category);

        // Ignore empty lines
        if (!expense.description.empty()) {
            expenses.push_back(expense);
        }
    }

    inFile.close();
    return expenses;
}

void printExpense(const Expense& expense) {
    tm* timeInfo = localtime(&expense.date);
    cout << "Description: " << expense.description << endl;
    cout << "Amount: Rs. " << fixed << setprecision(2) << expense.amount << endl;
    cout << "Date: " << put_time(timeInfo, "%Y-%m-%d %H:%M:%S") << endl;
    cout << "Category: " << expense.category << endl;
    cout << "-----------------------------------" << endl;
}

void displayExpenses(const vector<Expense>& expenses) {
    cout << "Expenses:" << endl;
    for (const auto& expense : expenses) {
        printExpense(expense);
    }
}

void addExpense(vector<Expense>& expenses) {
    Expense newExpense;
    cout << "Enter expense description: ";
    getline(cin, newExpense.description);

    cout << "Enter expense amount: $";
    cin >> newExpense.amount;

    cout << "Enter expense category: ";
    cin.ignore(); // Consume newline
    getline(cin, newExpense.category);

    newExpense.date = time(nullptr);

    expenses.push_back(newExpense);
    saveExpenses(expenses);

    cout << "Expense added successfully." << endl;
}

int main() {
    vector<Expense> expenses = loadExpenses();

    int choice;
    do {
        cout << "Expense Tracker Menu:" << endl;
        cout << "1. Display Expenses" << endl;
        cout << "2. Add Expense" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Consume newline

        switch (choice) {
            case 1:
                displayExpenses(expenses);
                break;
            case 2:
                addExpense(expenses);
                break;
            case 3:
                cout << "Exiting Expense Tracker." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 3);

    return 0;
}

