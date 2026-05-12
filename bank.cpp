#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    char name[50];
    float balance;

public:
    void createAccount();
    void showAccount() const;
    void modifyAccount();
    void deposit(float);
    void withdraw(float);
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

void BankAccount::showAccount() const {
    cout << "\nAccount Number : " << accountNumber;
    cout << "\nAccount Holder : " << name;
    cout << "\nBalance         : " << balance << endl;
}

void BankAccount::modifyAccount() {
    cout << "\nModify Account Holder Name: ";
    cin.ignore();
    cin.getline(name, 50);

    cout << "Modify Balance: ";
    cin >> balance;

    cout << "\nAccount Updated Successfully!\n";
}

void BankAccount::deposit(float amount) {
    balance += amount;
}

void BankAccount::withdraw(float amount) {
    balance -= amount;
}

int BankAccount::getAccountNumber() const {
    return accountNumber;
}

float BankAccount::getBalance() const {
    return balance;
}

void writeAccount();
void displayAccount(int);
void modifyAccountRecord(int);
void deleteAccountRecord(int);
void displayAllAccounts();
void depositWithdraw(int, int);

int main() {
    int choice;
    int number;

    do {
        cout << "\n======================================";
        cout << "\n BANK ACCOUNT MANAGEMENT SYSTEM";
        cout << "\n======================================";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Amount";
        cout << "\n3. Withdraw Amount";
        cout << "\n4. Display Account";
        cout << "\n5. Display All Accounts";
        cout << "\n6. Modify Account";
        cout << "\n7. Delete Account";
        cout << "\n8. Exit";
        cout << "\n======================================";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                writeAccount();
                break;

            case 2:
                cout << "\nEnter Account Number: ";
                cin >> number;
                depositWithdraw(number, 1);
                break;

            case 3:
                cout << "\nEnter Account Number: ";
                cin >> number;
                depositWithdraw(number, 2);
                break;

            case 4:
                cout << "\nEnter Account Number: ";
                cin >> number;
                displayAccount(number);
                break;

            case 5:
                displayAllAccounts();
                break;

            case 6:
                cout << "\nEnter Account Number: ";
                cin >> number;
                modifyAccountRecord(number);
                break;

            case 7:
                cout << "\nEnter Account Number: ";
                cin >> number;
                deleteAccountRecord(number);
                break;

            case 8:
                cout << "\nThank You! Exiting Program...\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 8);

    return 0;
}

void writeAccount() {
    BankAccount account;

    ofstream outFile;
    outFile.open("accounts.dat", ios::binary | ios::app);

    account.createAccount();

    outFile.write(reinterpret_cast<char*>(&account),
                  sizeof(BankAccount));

    outFile.close();
}

void displayAccount(int number) {
    BankAccount account;
    bool found = false;

    ifstream inFile;
    inFile.open("accounts.dat", ios::binary);

    if(!inFile) {
        cout << "\nFile could not be opened!\n";
        return;
    }

    while(inFile.read(reinterpret_cast<char*>(&account),
                      sizeof(BankAccount))) {

        if(account.getAccountNumber() == number) {
            account.showAccount();
            found = true;
        }
    }

    inFile.close();

    if(!found)
        cout << "\nAccount Not Found!\n";
}

void displayAllAccounts() {
    BankAccount account;

    ifstream inFile;
    inFile.open("accounts.dat", ios::binary);

    if(!inFile) {
        cout << "\nFile could not be opened!\n";
        return;
    }

    cout << "\n========== ACCOUNT HOLDER LIST ==========";

    while(inFile.read(reinterpret_cast<char*>(&account),
                      sizeof(BankAccount))) {

        account.showAccount();
        cout << "\n-------------------------------------";
    }

    inFile.close();
}

void modifyAccountRecord(int number) {
    bool found = false;

    BankAccount account;

    fstream file;
    file.open("accounts.dat",
              ios::binary | ios::in | ios::out);

    while(!file.eof() && !found) {

        file.read(reinterpret_cast<char*>(&account),
                  sizeof(BankAccount));

        if(account.getAccountNumber() == number) {

            account.showAccount();

            cout << "\nEnter New Details\n";
            account.modifyAccount();

            int position =
                (-1) * static_cast<int>(sizeof(BankAccount));

            file.seekp(position, ios::cur);

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

void deleteAccountRecord(int number) {
    BankAccount account;

    ifstream inFile;
    ofstream outFile;

    inFile.open("accounts.dat", ios::binary);

    if(!inFile) {
        cout << "\nFile could not be opened!\n";
        return;
    }

    outFile.open("temp.dat", ios::binary);

    inFile.seekg(0, ios::beg);

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

    cout << "\nRecord Deleted Successfully!\n";
}

void depositWithdraw(int number, int option) {

    float amount;
    bool found = false;

    BankAccount account;

    fstream file;
    file.open("accounts.dat",
              ios::binary | ios::in | ios::out);

    if(!file) {
        cout << "\nFile could not be opened!\n";
        return;
    }

    while(!file.eof() && !found) {

        file.read(reinterpret_cast<char*>(&account),
                  sizeof(BankAccount));

        if(account.getAccountNumber() == number) {

            account.showAccount();

            if(option == 1) {

                cout << "\nEnter Amount to Deposit: ";
                cin >> amount;

                account.deposit(amount);
            }
            else {

                cout << "\nEnter Amount to Withdraw: ";
                cin >> amount;

                if(amount <= account.getBalance()) {
                    account.withdraw(amount);
                }
                else {
                    cout << "\nInsufficient Balance!\n";
                }
            }

            int position =
                (-1) * static_cast<int>(sizeof(BankAccount));

            file.seekp(position, ios::cur);

            file.write(reinterpret_cast<char*>(&account),
                       sizeof(BankAccount));

            cout << "\nTransaction Successful!\n";

            found = true;
        }
    }

    file.close();

    if(!found)
        cout << "\nRecord Not Found!\n";
}