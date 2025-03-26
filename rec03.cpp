// Anemka Lydia Legbara
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


// Task 1: Define Account Struct

struct Account {
    string name;
    int accountNumber;
};

void task1() {
    ifstream file("accounts.txt");
    if (!file) {
        cerr << "File could not be opened" << endl;
        return;
    }

    vector<Account> accounts;
    string name;
    int accountNumber;

    while (file >> name >> accountNumber) {
        Account account;
        account.name = name;
        account.accountNumber = accountNumber;
        accounts.push_back(account);
    }
    file.close();

    for (const Account& acc : accounts) {
        cout << acc.name << "\t" << acc.accountNumber << endl;
    }

    // Task 1b: Using {} initialization
    cout << "\nTask1b:\n";
    accounts.clear();
    file.open("accounts.txt");
    while (file >> name >> accountNumber) {
        accounts.push_back(Account{name, accountNumber});
    }
    file.close();

    for (const Account& acc : accounts) {
        cout << acc.name << "\t" << acc.accountNumber << endl;
    }
}

// Task 2: Define Account Class
class AccountClass {
private:
    string name;
    int accountNumber;

public:
    AccountClass(const string& aName, int aNumber) : name(aName), accountNumber(aNumber) {}

    const string& getName() const { return name; }
    int getAccountNumber() const { return accountNumber; }

    friend ostream& operator<<(ostream& os, const AccountClass& acc) {
        os << acc.name << " " << acc.accountNumber;
        return os;
    }
};

void task2() {
    cout << "\n==============\n";

    ifstream file("accounts.txt");
    if (!file) {
        cerr << "File could not be opened" << endl;
        return;
    }

    vector<AccountClass> accounts;
    string name;
    int accountNumber;

    while (file >> name >> accountNumber) {
        accounts.push_back(AccountClass(name, accountNumber));
    }
    file.close();

    // task 2b
    for (const AccountClass& acc : accounts) {
        cout << acc.getName() << "\t" << acc.getAccountNumber() << endl;
    }

    // task 2c
    for (const AccountClass& acc : accounts) {
        cout << acc << endl;
    }

    // Using temporary objects
    accounts.clear();
    file.open("accounts.txt");
    while (file >> name >> accountNumber) {
        accounts.push_back(AccountClass(name, accountNumber));
    }
    file.close();

    // Using emplace_back
    accounts.clear();
    file.open("accounts.txt");
    while (file >> name >> accountNumber) {
        accounts.emplace_back(name, accountNumber);
    }
    file.close();
}

// Task 3: Transactions as Separate Class
class Transaction {
private:
    string type;
    int amount;

public:
    Transaction(const string& t, int a) : type(t), amount(a) {}

    friend ostream& operator<<(ostream& os, const Transaction& t) {
        os << t.type << " " << t.amount;
        return os;
    }
};

class AccountWithTransactions {
private:
    string name;
    int accountNumber;
    int balance;
    vector<Transaction> transactions;

public:
    AccountWithTransactions(const string& aName, int aNumber)
        : name(aName), accountNumber(aNumber), balance(0) {}

    void deposit(int amount) {
        balance += amount;
        transactions.push_back(Transaction("deposit", amount));
    }

    void withdraw(int amount) {
        if (amount > balance) {
            cout << accountNumber << " has only " << balance
                 << ". Insufficient for withdrawal of " << amount << "." << endl;
        } else {
            balance -= amount;
            transactions.push_back(Transaction("withdrawal", amount));
        }
    }

    int getAccountNumber() const { return accountNumber; }

    friend ostream& operator<<(ostream& os, const AccountWithTransactions& acc);
};

// Output operator for AccountWithTransactions
ostream& operator<<(ostream& os, const AccountWithTransactions& acc) {
    os << acc.name << " " << acc.accountNumber << "\n";
    for (const Transaction& t : acc.transactions) {
        os << "\t" << t << endl;
    }
    return os;
}

// Reads transactions.txt and processes deposits & withdrawals
void task3() {
    ifstream file("transactions.txt");
    if (!file) {
        cerr << "Could not open transactions.txt" << endl;
        return;
    }

    vector<AccountWithTransactions> accounts;
    string command, name;
    int accountNumber, amount;

    while (file >> command) {
        if (command == "Account") {
            file >> name >> accountNumber;
            accounts.push_back(AccountWithTransactions(name, accountNumber));
        } else if (command == "Deposit") {
            file >> accountNumber >> amount;
            for (AccountWithTransactions& acc : accounts) {
                if (acc.getAccountNumber() == accountNumber) {
                    acc.deposit(amount);
                }
            }
        } else if (command == "Withdraw") {
            file >> accountNumber >> amount;
            for (AccountWithTransactions& acc : accounts) {
                if (acc.getAccountNumber() == accountNumber) {
                    acc.withdraw(amount);
                }
            }
        }
    }

    file.close();

    // Display all accounts and transactions
    for (const AccountWithTransactions& acc : accounts) {
        cout << acc << endl;
    }
}

// task 4
class AccountNestedTransaction {
public:
    // Nested Transaction Class
    class Transaction {
    private:
        string type;
        int amount;

    public:
        Transaction(const string& t, int a) : type(t), amount(a) {}

        friend ostream& operator<<(ostream& os, const AccountNestedTransaction::Transaction& t);
    };

private:
    string name;
    int accountNumber;
    int balance;
    vector<Transaction> transactions;

public:
    AccountNestedTransaction(const string& aName, int aNumber)
        : name(aName), accountNumber(aNumber), balance(0) {}

    void deposit(int amount) {
        balance += amount;
        transactions.push_back(Transaction("deposit", amount));
    }

    void withdraw(int amount) {
        if (amount > balance) {
            cout << accountNumber << " has only " << balance
                 << ". Insufficient for withdrawal of " << amount << "." << endl;
        } else {
            balance -= amount;
            transactions.push_back(Transaction("withdrawal", amount));
        }
    }

    int getAccountNumber() const { return accountNumber; }

    friend ostream& operator<<(ostream& os, const AccountNestedTransaction& acc);
};

ostream& operator<<(ostream& os, const AccountNestedTransaction::Transaction& t) {
    os << t.type << " " << t.amount;
    return os;
}

// Output operator for AccountNestedTransaction
ostream& operator<<(ostream& os, const AccountNestedTransaction& acc) {
    os << acc.name << " " << acc.accountNumber << "\n";
    for (const auto& t : acc.transactions) {
        os << "\t" << t << endl;
    }
    return os;
}

// Reads transactions.txt and processes deposits & withdrawals
void task4() {
    ifstream file("transactions.txt");
    if (!file) {
        cerr << "Error opening transactions.txt!" << endl;
        return;
    }

    vector<AccountNestedTransaction> accounts;
    string command, name;
    int accountNumber, amount;

    while (file >> command) {
        if (command == "Account") {
            file >> name >> accountNumber;
            accounts.push_back(AccountNestedTransaction(name, accountNumber));
        } else if (command == "Deposit") {
            file >> accountNumber >> amount;
            for (AccountNestedTransaction& acc : accounts) {
                if (acc.getAccountNumber() == accountNumber) {
                    acc.deposit(amount);
                }
            }
        } else if (command == "Withdraw") {
            file >> accountNumber >> amount;
            for (AccountNestedTransaction& acc : accounts) {
                if (acc.getAccountNumber() == accountNumber) {
                    acc.withdraw(amount);
                }
            }
        }
    }

    file.close();

    // Display all accounts and transactions
    for (const AccountNestedTransaction& acc : accounts) {
        cout << acc << endl;
    }
}

// task 5
class AccountPrivateTransaction {
private:
    // Private Nested Transaction Class
    class Transaction {
    private:
        string type;
        int amount;

    public:
        Transaction(const string& t, int a) : type(t), amount(a) {}

        friend ostream& operator<<(ostream& os, const AccountPrivateTransaction::Transaction& t);
    };
    friend ostream& operator<<(ostream& os, const AccountPrivateTransaction::Transaction& t);
    string name;
    int accountNumber;
    int balance;
    vector<Transaction> transactions;

public:
    AccountPrivateTransaction(const string& aName, int aNumber)
        : name(aName), accountNumber(aNumber), balance(0) {}

    void deposit(int amount) {
        balance += amount;
        transactions.push_back(Transaction("deposit", amount));
    }

    void withdraw(int amount) {
        if (amount > balance) {
            cout << accountNumber << " has only " << balance
                 << ". Insufficient for withdrawal of " << amount << "." << endl;
        } else {
            balance -= amount;
            transactions.push_back(Transaction("withdrawal", amount));
        }
    }

    int getAccountNumber() const { return accountNumber; }
    int getBalance() const { return balance; }
    const string& getName() const { return name; }

    // vector<Transaction> getTransactions() const { return transactions; }

    friend ostream& operator<<(ostream& os, const AccountPrivateTransaction& acc);
};

ostream& operator<<(ostream& os, const AccountPrivateTransaction::Transaction& t) {
    os << t.type << " " << t.amount;
    return os;
}

ostream& operator<<(ostream& os, const AccountPrivateTransaction& acc) {
    os << acc.name << " " << acc.accountNumber << " " << acc.balance << endl;

    for (const AccountPrivateTransaction::Transaction& t : acc.transactions) {
        os << "\t" << t << endl;
    }
    return os;
}

// Reads transactions.txt and processes deposits & withdrawals
void task5() {
    cout << "\n==============\nTask 5:\n";

    ifstream file("transactions.txt");
    if (!file) {
        cerr << "Error opening transactions.txt!" << endl;
        return;
    }

    vector<AccountPrivateTransaction> accounts;
    string command, name;
    int accountNumber, amount;

    while (file >> command) {
        if (command == "Account") {
            file >> name >> accountNumber;
            accounts.push_back(AccountPrivateTransaction(name, accountNumber));
        } else if (command == "Deposit") {
            file >> accountNumber >> amount;

            for (size_t i = 0; i < accounts.size(); i++) {
                if (accounts[i].getAccountNumber() == accountNumber) {
                    accounts[i].deposit(amount);
                }
            }
        } else if (command == "Withdraw") {
            file >> accountNumber >> amount;

            for (size_t i = 0; i < accounts.size(); i++) {
                if (accounts[i].getAccountNumber() == accountNumber) {
                    accounts[i].withdraw(amount);
                }
            }
        }
    }

    file.close();

    for (size_t i = 0; i < accounts.size(); i++) {
        cout << accounts[i] << endl;
    }
}

int main() {
    task1();
    task2();
    task3();
    task4();
    task5();
    return 0;
}
