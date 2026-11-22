// Gauteng City College - Introduction to Programming
// Banking System Assignment
// This program allows three customers to deposit, withdraw and send money.

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

const int TOTAL_USERS = 3;

// Customer information is stored in arrays.
string names[TOTAL_USERS] = {"Thando Mokoena", "Lerato Dlamini", "Sipho Nkosi"};
int accountNumbers[TOTAL_USERS] = {1001, 1002, 1003};
int pins[TOTAL_USERS] = {1234, 2345, 3456};
double balances[TOTAL_USERS] = {2500.00, 1800.00, 3200.00};

// This function clears incorrect input so the program can ask again.
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Read a whole number from the user.
int getNumber(string message) {
    int number;

    while (true) {
        cout << message;

        if (cin >> number) {
            clearInput();
            return number;
        }

        cout << "That was not a valid number. Please try again.\n";
        clearInput();
    }
}

// Read an amount and make sure it is greater than zero.
double getAmount(string message) {
    double amount;

    while (true) {
        cout << message;

        if (cin >> amount && amount > 0) {
            clearInput();
            return amount;
        }

        cout << "Please enter an amount greater than R0.00.\n";
        clearInput();
    }
}

// Find a customer's position in the arrays using their account number.
int findAccount(int accountNumber) {
    for (int i = 0; i < TOTAL_USERS; i++) {
        if (accountNumbers[i] == accountNumber) {
            return i;
        }
    }

    return -1;
}

// Check the account number and PIN before opening the banking menu.
int login() {
    cout << "=====================================\n";
    cout << "             GCC BANK\n";
    cout << "=====================================\n";

    for (int attempt = 1; attempt <= 3; attempt++) {
        int accountNumber = getNumber("Enter your account number: ");
        int pin = getNumber("Enter your PIN: ");

        int user = findAccount(accountNumber);

        if (user != -1 && pins[user] == pin) {
            cout << "\nWelcome, " << names[user] << "!\n";
            return user;
        }

        cout << "Incorrect account number or PIN. Please try again.\n";
    }

    cout << "\nToo many failed attempts. The program will close.\n";
    return -1;
}

// Show the choices available in the banking system.
void displayMenu() {
    cout << "\n========== GCC BANK MENU ==========\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Send Cash\n";
    cout << "4. Check Balance\n";
    cout << "5. Exit\n";
    cout << "===================================\n";
}

// Add money to the logged-in customer's account.
void deposit(int user) {
    double amount = getAmount("Enter the amount to deposit (R): ");
    balances[user] = balances[user] + amount;

    cout << "Deposit successful.\n";
    cout << "Your new balance is R" << fixed << setprecision(2)
         << balances[user] << "\n";
}

// Take money out, but do not allow the balance to go below zero.
void withdraw(int user) {
    double amount = getAmount("Enter the amount to withdraw (R): ");

    if (amount <= balances[user]) {
        balances[user] = balances[user] - amount;
        cout << "Withdrawal successful.\n";
        cout << "Your new balance is R" << fixed << setprecision(2)
             << balances[user] << "\n";
    } else {
        cout << "Sorry, you do not have enough money in your account.\n";
    }
}

// Send money to another customer who is registered with GCC Bank.
void sendCash(int sender) {
    int receiverAccount = getNumber("Enter the receiver's account number: ");
    int receiver = findAccount(receiverAccount);

    if (receiver == -1) {
        cout << "That account number could not be found.\n";
        return;
    }

    if (receiver == sender) {
        cout << "You cannot send money to your own account.\n";
        return;
    }

    double amount = getAmount("Enter the amount to send (R): ");

    if (amount <= balances[sender]) {
        balances[sender] = balances[sender] - amount;
        balances[receiver] = balances[receiver] + amount;

        cout << "Money sent successfully to " << names[receiver] << ".\n";
        cout << "Your new balance is R" << fixed << setprecision(2)
             << balances[sender] << "\n";
    } else {
        cout << "You do not have enough money to make this transfer.\n";
    }
}

// Display the balance of the logged-in customer.
void checkBalance(int user) {
    cout << "\nAccount holder: " << names[user] << "\n";
    cout << "Account number: " << accountNumbers[user] << "\n";
    cout << "Current balance: R" << fixed << setprecision(2)
         << balances[user] << "\n";
}

int main() {
    int currentUser = login();

    if (currentUser == -1) {
        return 0;
    }

    int choice;

    // Keep showing the menu until the customer chooses to exit.
    do {
        displayMenu();
        choice = getNumber("Enter your choice: ");

        switch (choice) {
            case 1:
                deposit(currentUser);
                break;

            case 2:
                withdraw(currentUser);
                break;

            case 3:
                sendCash(currentUser);
                break;

            case 4:
                checkBalance(currentUser);
                break;

            case 5:
                cout << "Thank you for banking with GCC Bank. Goodbye!\n";
                break;

            default:
                cout << "Invalid menu choice. Please choose a number from 1 to 5.\n";
        }

    } while (choice != 5);

    return 0;
}
