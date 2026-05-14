# Bank Account Management System

A simple console-based banking application developed using C++ that performs basic banking operations like account creation, deposit, withdrawal, search, modification, and deletion of accounts using file handling.

---

# Project Information

- Project Title: Bank Account Management System
- Department: Computer Science and Engineering
- Academic Year: 2025–26
- Technology Used: C++
- Type: Console Application

---

# Features

- Create New Account
- Deposit Money
- Withdraw Money
- Search Account
- Display All Accounts
- Modify Account Details
- Delete Account
- File Handling for Permanent Storage
- Menu Driven Interface

---

# Project Type
Console-based application developed using C++.

---

# Technologies Used

- C++
- Object Oriented Programming
- File Handling
- Functions
- Binary Files

---

# Software Requirements

- GCC Compiler / CodeBlocks / VS Code
- Windows/Linux/MacOS

---

# How to Run

## Step 1
Save the source code as:

```bash
bank.cpp
```

## Step 2
Compile the code:

```bash
g++ bank.cpp -o bank
```

## Step 3
Run the program:

```bash
./bank
```
## Full Source Code

```cpp
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    char name[50];
    float balance;

public:
    void createAccount();
    void displayAccount() const;
    void modifyAccount();
    void depositMoney(float amount);
    void withdrawMoney(float amount);
    int getAccountNumber() const;
    float getBalance() const;
};

void BankAccount::createAccount() {
    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    cin.ignore();

    cout << "Enter Account Holder Name: ";
    cin.getline(name, 50);

    cout << "Enter Initial Balance: ";
    cin >> balance;

    cout << "\nAccount Created Successfully!\n";
}

void BankAccount::displayAccount() const {
    cout << "\n--------------------------------";
    cout << "\nAccount Number : " << accountNumber;
    cout << "\nAccount Holder : " << name;
    cout << "\nBalance        : " << balance;
    cout << "\n--------------------------------\n";
}

void BankAccount::modifyAccount() {
    cin.ignore();

    cout << "\nEnter New Name: ";
    cin.getline(name, 50);

    cout << "Enter New Balance: ";
    cin >> balance;

    cout << "\nAccount Updated Successfully!\n";
}

void BankAccount::depositMoney(float amount) {
    balance += amount;
}

void BankAccount::withdrawMoney(float amount) {
    balance -= amount;
}

int BankAccount::getAccountNumber() const {
    return accountNumber;
}

float BankAccount::getBalance() const {
    return balance;
}

void createNewAccount();
void displayAllAccounts();
void searchAccount(int);
void modifyExistingAccount(int);
void deleteExistingAccount(int);
void depositOrWithdraw(int, int);

int main() {
    int choice;
    int accountNo;

    do {
        cout << "\n======================================";
        cout << "\n BANK ACCOUNT MANAGEMENT SYSTEM";
        cout << "\n======================================";
        cout << "\n1. Create New Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Search Account";
        cout << "\n5. Display All Accounts";
        cout << "\n6. Modify Account";
        cout << "\n7. Delete Account";
        cout << "\n8. Exit";
        cout << "\n======================================";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                createNewAccount();
                break;

            case 2:
                cout << "\nEnter Account Number: ";
                cin >> accountNo;
                depositOrWithdraw(accountNo, 1);
                break;

            case 3:
                cout << "\nEnter Account Number: ";
                cin >> accountNo;
                depositOrWithdraw(accountNo, 2);
                break;

            case 4:
                cout << "\nEnter Account Number: ";
                cin >> accountNo;
                searchAccount(accountNo);
                break;

            case 5:
                displayAllAccounts();
                break;

            case 6:
                cout << "\nEnter Account Number: ";
                cin >> accountNo;
                modifyExistingAccount(accountNo);
                break;

            case 7:
                cout << "\nEnter Account Number: ";
                cin >> accountNo;
                deleteExistingAccount(accountNo);
                break;

            case 8:
                cout << "\nThank You! Program Exited.\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 8);

    return 0;
}

void createNewAccount() {
    BankAccount account;

    ofstream outFile("accounts.dat", ios::binary | ios::app);

    account.createAccount();

    outFile.write(reinterpret_cast<char*>(&account),
                  sizeof(BankAccount));

    outFile.close();
}

void displayAllAccounts() {
    BankAccount account;

    ifstream inFile("accounts.dat", ios::binary);

    if(!inFile) {
        cout << "\nFile Not Found!\n";
        return;
    }

    cout << "\n========== ALL ACCOUNT DETAILS ==========\n";

    while(inFile.read(reinterpret_cast<char*>(&account),
                      sizeof(BankAccount))) {

        account.displayAccount();
    }

    inFile.close();
}

void searchAccount(int number) {
    BankAccount account;
    bool found = false;

    ifstream inFile("accounts.dat", ios::binary);

    while(inFile.read(reinterpret_cast<char*>(&account),
                      sizeof(BankAccount))) {

        if(account.getAccountNumber() == number) {
            account.displayAccount();
            found = true;
        }
    }

    inFile.close();

    if(!found)
        cout << "\nAccount Not Found!\n";
}

void modifyExistingAccount(int number) {
    BankAccount account;
    bool found = false;

    fstream file("accounts.dat",
                 ios::binary | ios::in | ios::out);

    while(file.read(reinterpret_cast<char*>(&account),
                    sizeof(BankAccount)) && !found) {

        if(account.getAccountNumber() == number) {

            cout << "\nCurrent Account Details:\n";
            account.displayAccount();

            account.modifyAccount();

            int pos = (-1) * static_cast<int>(sizeof(BankAccount));

            file.seekp(pos, ios::cur);

            file.write(reinterpret_cast<char*>(&account),
                       sizeof(BankAccount));

            cout << "\nRecord Updated Successfully!\n";

            found = true;
        }
    }

    file.close();

    if(!found)
        cout << "\nRecord Not Found!\n";
}

void deleteExistingAccount(int number) {
    BankAccount account;

    ifstream inFile("accounts.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);

    while(inFile.read(reinterpret_cast<char*>(&account),
                      sizeof(BankAccount))) {

        if(account.getAccountNumber() != number) {

            outFile.write(reinterpret_cast<char*>(&account),
                          sizeof(BankAccount));
        }
    }

    inFile.close();
    outFile.close();

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    cout << "\nAccount Deleted Successfully!\n";
}

void depositOrWithdraw(int number, int choice) {
    BankAccount account;
    bool found = false;
    float amount;

    fstream file("accounts.dat",
                 ios::binary | ios::in | ios::out);

    while(file.read(reinterpret_cast<char*>(&account),
                    sizeof(BankAccount)) && !found) {

        if(account.getAccountNumber() == number) {

            account.displayAccount();

            if(choice == 1) {

                cout << "\nEnter Amount to Deposit: ";
                cin >> amount;

                account.depositMoney(amount);

                cout << "\nAmount Deposited Successfully!\n";
            }
            else {

                cout << "\nEnter Amount to Withdraw: ";
                cin >> amount;

                if(amount <= account.getBalance()) {

                    account.withdrawMoney(amount);

                    cout << "\nAmount Withdrawn Successfully!\n";
                }
                else {
                    cout << "\nInsufficient Balance!\n";
                }
            }

            int pos = (-1) * static_cast<int>(sizeof(BankAccount));

            file.seekp(pos, ios::cur);

            file.write(reinterpret_cast<char*>(&account),
                       sizeof(BankAccount));

            found = true;
        }
    }

    file.close();

    if(!found)
        cout << "\nRecord Not Found!\n";
}
```

## Project Modules
1. Account Creation
Creates a new account with:
Account Number
Account Holder Name
Initial Balance
2. Deposit Module
Deposits money into the account.
3. Withdrawal Module
Withdraws money after balance verification.
4. Search Module
Searches account using account number.
5. Display Module
Displays all stored accounts.
6. Modify Module
Updates account details.
7. Delete Module
Deletes account records permanently.

## Concepts Used
- Classes and Objects
- Encapsulation
- File Handling
- Functions
- Loops
- Conditional Statements

## Future Enhancements
- Password Protection
- GUI Interface
- Database Connectivity
- ATM Simulation
- Transaction History
- Online Banking Features

## Advantages
- Easy to use
- Permanent data storage
- Real-world banking simulation
- Beginner friendly project
- Improves OOP knowledge

## Team Members
- Chigirintha Snikith Reddy
- Kalki Umesh Chandra Prasad
- Mohammed Ayan Hassain
- Papani Kavya
- Parne Nikhilesh Reddy

## Conclusion
The Bank Account Management System is a simple and efficient C++ application that demonstrates banking operations using object oriented programming and file handling concepts.
