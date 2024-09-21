#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
using namespace std;

class ATM {
    int check_acc, current_user;
    string check_pin;
    vector<int> acc;
    vector<string> pin;
    vector<int> balance;
    vector<string> transactions;

public:
    ATM(int a, string p) {
        check_acc = a;
        check_pin = p;
    }

    bool loadData() {
        ifstream infile("atm.txt");
        if (!infile) {
            cout << "Could not open file." << endl;
            return false;
        }

        int a, b;
        string p;

        while (infile >> a >> p >> b) {
            acc.push_back(a);
            pin.push_back(p);
            balance.push_back(b);
        }
        infile.close();
        return true;
    }

    bool saveData() {
        ofstream outfile("atm.txt");
        if (!outfile) {
            cout << "Could not open file." << endl;
            return false;
        }

        for (size_t i = 0; i < acc.size(); ++i) {
            outfile << acc[i] << " " << pin[i] << " " << balance[i] << endl;
        }

        outfile.close();
        return true;
    }

    bool check() {
        for (size_t i = 0; i < acc.size(); ++i) {
            if (check_acc == acc[i] && check_pin == pin[i]) {
                current_user = i;
                return true;
            }
        }
        return false;
    }

    void addTransaction(string type, int amount) {
        if (transactions.size() == 5)
            transactions.erase(transactions.begin());
        transactions.push_back(type + " " + to_string(amount));
    }

    void printLastTransactions() {
        cout << "Last 5 transactions:" << endl;
        for (const auto &trans : transactions) {
            cout << trans << endl;
        }
    }

    void withdraw(int amount) {
        system("cls");
        if (amount > balance[current_user]) {
            cout << "Insufficient balance" << endl;
        }
        else if (amount == 0) {
            cout << "Zero cannot be withdrawn.\nAmount is already null";
        }
        else {
            balance[current_user] -= amount;
            cout << "Withdrawal successful.\nNew balance: " << balance[current_user] << endl;
            saveData();
            addTransaction("Withdraw", amount);
        }
    }

    void deposit(int amount) {
        balance[current_user] += amount;
        cout << "Deposit successful.\nNew balance: " << balance[current_user] << endl;
        saveData();
        addTransaction("Deposit", amount);
    }

    void check_balance() {
        cout << "Current balance: " << balance[current_user] << endl;
    }

    void exit_atm() {
        system("cls");
        cout << "Thank you for using our ATM!\nHave a great day" << endl;
        exit(0);
    }

    bool createAccount(int new_acc, string new_pin, int initial_balance) {
        for (const auto &a : acc) {
            if (a == new_acc) {
                cout << "Account already exists." << endl;
                return false;
            }
        }
        acc.push_back(new_acc);
        pin.push_back(new_pin);
        balance.push_back(initial_balance);
        saveData();
        cout << "Account created successfully." << endl;
        return true;
    }
};

int main() {
    char option;
    do {
        int acc, amount;
        string pass, password;
        char ch;
        cout << "Enter account number = ";
        cin >> acc;
        cout << "Enter password: ";

        while (true) {
            ch = getch();
            if (ch == '\r') {
                break;
            }
            else if (ch == ' ') {
                continue;
            }
            else if (ch == '\b') {
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                password.push_back(ch);
                cout << '*';
            }
        }
        pass = password;

        system("cls");
        Sleep(2000);

        ATM atm(acc, pass);
        if (!atm.loadData()) {
            cout << "Failed to load data." << endl;
            return 0;
        }

        if (atm.check()) {
            while (true) {
                int choice;
                cout << "ATM Menu:" << endl;
                cout << "1. Withdraw" << endl;
                cout << "2. Deposit" << endl;
                cout << "3. Balance" << endl;
                cout << "4. Print Last 5 Transactions" << endl;
                cout << "5. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                system("cls");
                switch (choice) {
                    case 1:
                        cout << "Enter amount to withdraw: ";
                        cin >> amount;
                        atm.withdraw(amount);
                        break;

                    case 2:
                        cout << "Enter amount to deposit: ";
                        cin >> amount;
                        atm.deposit(amount);
                        break;

                    case 3:
                        atm.check_balance();
                        break;

                    case 4:
                        atm.printLastTransactions();
                        break;

                    case 5:
                        atm.exit_atm();
                        break;

                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
                Sleep(2000);
                system("cls");
            }
        }
        else {
            cout << "Wrong account number or pin code!\nTry Again.";

            Sleep(1000);
            system("cls");

            cout << "Want to create a new account? (y/n) = ";
            cin >> ch;
            if (ch == 'y' || ch == 'Y') {
                int new_acc, initial_balance;
                string new_pin;
                cout << "Enter new account number: ";
                cin >> new_acc;
                cout << "Enter new password: ";
                cin >> new_pin;
                cout << "Enter initial balance: ";
                cin >> initial_balance;
                atm.createAccount(new_acc, new_pin, initial_balance);
            }
        }
        cout << "Want to try again? (y/n) = ";
        cin >> option;
        system("cls");
    } while (option == 'y' || option == 'Y');

    return 0;
}
