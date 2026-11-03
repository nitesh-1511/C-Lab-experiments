
#include <iostream>
#include <string>
#include <vector>
#include <exception>
using namespace std;

// 1. Base custom exception
class BankException : public exception {
protected:
    string message;

public:
    BankException(string msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// 2. Insufficient funds exception
class InsufficientFundsException : public BankException {
public:
    InsufficientFundsException()
        : BankException("Insufficient balance for withdrawal.") {}
};

// 3. Invalid amount exception
class InvalidAmountException : public BankException {
public:
    InvalidAmountException()
        : BankException("Amount must be greater than zero.") {}
};

// 4. Minimum balance exception
class MinimumBalanceException : public BankException {
public:
    MinimumBalanceException()
        : BankException("Minimum balance of Rs. 1000 must be maintained.") {}
};

// 5. Bank account class
class BankAccount {
private:
    string name;
    double balance;
    double totalDeposited = 0;
    double totalWithdrawn = 0;
    int transactions = 0;
    vector<string> history;

public:
    BankAccount(string n, double b) : name(n), balance(b) {}

    void deposit(double amount) {
        if (amount <= 0)
            throw InvalidAmountException();

        balance += amount;
        totalDeposited += amount;
        transactions++;

        history.push_back("Deposited Rs. " + to_string(amount));
    }

    void withdraw(double amount) {
        if (amount <= 0)
            throw InvalidAmountException();

        if (amount > balance)
            throw InsufficientFundsException();

        if (balance - amount < 1000)
            throw MinimumBalanceException();

        balance -= amount;
        totalWithdrawn += amount;
        transactions++;

        history.push_back("Withdrew Rs. " + to_string(amount));
    }

    void display() {
        cout << "Account Holder: " << name << endl;
        cout << "Balance: Rs. " << balance << endl;
    }

    void showSummary() {
        cout << "\n--- Account Summary ---" << endl;
        cout << "Account Holder: " << name << endl;
        cout << "Current Balance: Rs. " << balance << endl;
        cout << "Total Deposited: Rs. " << totalDeposited << endl;
        cout << "Total Withdrawn: Rs. " << totalWithdrawn << endl;
        cout << "Successful Transactions: " << transactions << endl;

        cout << "\n--- Transaction History ---" << endl;
        for (const string& entry : history) {
            cout << entry << endl;
        }
    }
};

// 6. Main function
int main() {
    BankAccount account("Nitesh", 7000);

    cout << "Initial Account Details:" << endl;
    account.display();

    try {
        account.deposit(1000);
        cout << "Deposit successful: Rs. 2000" << endl;

        account.withdraw(500);
        cout << "Withdrawal successful: Rs. 1500" << endl;

        cout << "\nTrying to withdraw Rs. 7000..." << endl;
        account.withdraw(7000);
    }
    catch (const BankException& e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        cout << "\nTrying to withdraw Rs. 6000..." << endl;
        account.withdraw(6000);
    }
    catch (const BankException& e) {
        cout << "Error: " << e.what() << endl;
    }

    account.showSummary();

    return 0;
}