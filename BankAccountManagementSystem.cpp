#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

class Account{
    
    string accNumber;
    string accHolder;
    double balance;

    public:
    Account():balance(0.0){}

    void createAccount(){
        cout << "Enter Account Number: ";
        cin >> accNumber;
        cin.ignore();
        cout << "Enter Account Holder Name: ";
        getline(cin,accHolder);
        balance = 0.0;
        cout << "Account created successfully" << endl;
    }

    void deposit(double amount){
        if(amount>0){
            balance += amount;
            cout << "Deposited: " << amount << endl;
        }
        else cout << "Invalid deposit amount." << endl;
    }

    void withdraw(double amount){
        if(amount>0 && amount<=balance){
            balance -= amount;
            cout << "Withdrew: " << amount << endl;
        }
        else cout << "Invalid or insufficient funds for withdrawal" << endl;
    }

    void display() const{
        cout << "Account Number: " << accNumber << endl;
        cout << "Account Holder: " << accHolder << endl;
        cout << "Balance: $" << balance << endl;
    }

    void saveToFile(ofstream &outFile) const{
        outFile << accNumber << endl;
        outFile << accHolder << endl;
        outFile << balance << endl;
    }

    void loadFromFile(ifstream &inFile){
        getline(inFile, accNumber);
        getline(inFile, accHolder);
        inFile >> balance;
        inFile.ignore();
    }

    string getAccountNumber() const {
        return accNumber;
    }
};

void displayMenu();
void createAccount(vector<Account> &account);
void deposit(vector<Account> &account);
void withdraw(vector<Account> &account);
void checkBalance(const vector<Account> &account);
void saveAccount(const vector<Account> &account, const string &filename);
void loadAccount(vector<Account> &account, const string &filename);

int main()
{
    vector<Account> account;
    const string filename = "accounts.txt";

    loadAccount(account, filename);

    int choice;
    do{
        displayMenu();
        cin >> choice;

        switch(choice){
            case 1:
            createAccount(account);
            break;

            case 2:
            deposit(account);
            break;

            case 3:
            withdraw(account);
            break;

            case 4:
            checkBalance(account);
            break;

            case 5:
            saveAccount(account, filename);
            break;

            default:
            cout << "Invalid choice. Please try again" << endl;

        }
    }while(choice != 5);

    return 0;
}

void displayMenu()
{
    cout << "\nBank Account Management System" << endl;
    cout << "1. CreateAccount" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice" << endl;
}

void createAccount(vector<Account> &account)
{
    Account newAccount;
    newAccount.createAccount();
    account.push_back(newAccount);
}

void deposit(vector<Account> &account)
{
    string accNumber;
    double amount;
    cout << "Enter Account Number: ";
    cin >> accNumber;
    cout << "Enter Amount to deposit: ";
    cin >> amount;

    for(auto &acc : account)
    {
        if(acc.getAccountNumber() == accNumber)
        {
            acc.deposit(amount);
            return;
        }
        
    }
    cout << "Account not found." << endl;

}

void withdraw(vector<Account> &account)
{
    string accNumber;
    double amount;
    cout << "Enter Account Number: ";
    cin >> accNumber;
    cout << "Enter Amount to Withdraw: ";
    cin >> amount;

    for(auto &acc : account)
    {
        if(acc.getAccountNumber() == accNumber)
        {
            acc.withdraw(amount);
            return;
        }
    }
    cout << "Account not found." << endl;
}

void checkBalance(const vector<Account> &account)
{
    string accNumber;
    cout << "Enter Account Number: ";
    cin >> accNumber;

    for(const auto &acc : account)
    {
        if(acc.getAccountNumber() == accNumber)
        {
            acc.display();
            return;
        }
    }
    cout << "Account not found." << endl;
}

void saveAccount(const vector<Account> &account, const string &filename)
{
    ofstream outFile(filename);
    if(outFile.is_open())
    {
        for(const auto &acc : account)
        {
            acc.saveToFile(outFile);
        }
        outFile.close();
        cout << "Accounts saved successfully." << endl;
    }
    else cout << "Unable to open file for saving." << endl;
}

void loadAccount(vector<Account> &account, const string &filename)
{
    ifstream inFile(filename);
    if(inFile.is_open())
    {
        Account acc;
        while(inFile.peek() != EOF)
        {
            acc.loadFromFile(inFile);
            account.push_back(acc);
        }
        inFile.close();
        cout << "Accounts loaded successfully." << endl;
    }
    else cout << "No existing account file found. Starting fresh." << endl;
}