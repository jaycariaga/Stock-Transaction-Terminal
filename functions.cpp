//
// Created by jaymc on 4/17/2018.
//

#include <cstdlib>
#include <time.h>
#include "header.h"
#include <sysinfoapi.h>

void stockmenu(int *num) {
    int select = 0;
    cout << "\nPlease select an option\n";
    cout << "\t1. Display current price for a stock symbol"
         << "\n\t2. Buy stock"
         << "\n\t3. Sell stock"
         << "\n\t4. Display current portfolio"
         << "\n\t5. Display transactions history"
         << "\n\t6. Return to main menu" << endl;
    cout << "Your selection:\t";
    cin >> select;
    *num = select;
}

void bankmenu(int *num) {
    int select = 0;
    cout << "\nPlease select an option\n" << endl;
    cout << "\t1. View account balance"
         << "\n\t2. Deposit money"
         << "\n\t3. Withdraw money"
         << "\n\t4. Display transactions history"
         << "\n\t5. Return to previous menu" << endl;
    cout << "Your selection:\t";
    cin >> select;
    *num = select;
}

void validInput(double &a) {
    //a will be returned, after the function, as the input from the user
        string input;
        input = to_string(a);
        int termination = 0;
        while (termination == 0) {
            for (unsigned int k = 0; k < input.length(); k++) {
                if (((input)[k] > '9' || (input)[k] < '0') && (input)[k] != '.') {
                    cout << "Invalid Input.\nEnter new number:  ";
                    cin >> input;
                } else
                    termination = 1;
            }
        }
        a = stod(input);
        while (a < 0) {
            cout << "\nEnter positive number: ";
            cin >> a;
        }
}

vector<string> inputtoarray(){
    string input;
    cin.ignore(256, '\n'); //this is important if getline only sees enter as the initial input
    getline(cin, input);
    string delim = " ";
    vector<string> tokens;
    for (int i = 0; i < 3; i++) { // making 3 tokens
        if (i == 2) { // handling newline character
            input = input.substr(input.rfind(delim) + 1, string::npos);
            input.resize(input.length()); // remove newline
            tokens.push_back(input);
        }
        tokens.push_back(input.substr(0, input.find(delim)));
        input = input.substr(input.find(delim) + 1, string::npos);
    }
    return tokens;
}

void deletline(){
    cout << "NO YOUR DELETING the other lines in the txt files f YALL ";
}

//The functions pertaining to Account PARENT class
Account::Account() {
    cashBalance = 10000;
}
double Account::getBalance() {
    return cashBalance;
}
void Account::setBalance(double a) {
    cashBalance = a;
}

//functions for stockAccount derived class of Account

void stockAccount::display2bank(string action, int amount, double balance) {
    string line = "\n" + action + "\t" + to_string(amount) + "\t\t" + to_string(balance) + "\t" ;
    ofstream myfile;
    myfile.open("C:\\Users\\jaymc\\CLionProjects\\project2\\bank_transaction_history", ios_base::app);
    myfile << line;
    myfile.close();
}

stockAccount::stockAccount() {
}

void stockAccount::getstockprice() {
    srand(time(NULL));
    bool success = 0;
    //asks for input
    string sym;
    cout << "Enter stock symbol for checking price: ";
    cin >> sym;
    cout << endl;
    //converts a copy of input to start searching for match in a stock file
    string converted = "";
    for(int i= 0; i < sym.size(); i++){
        converted += toupper(sym[i]);
    }
    int num = (rand()%4) + 1;
    string name = "stock" + to_string(num) + ".txt";
    string name2 = "C:\\Users\\jaymc\\CLionProjects\\project2\\" + name;
    ifstream file(name2);
    string line;
    while (getline(file, line)) {
        string delim = "\t";
        vector <string> tokens;
        for (int i = 0; i < 3; i++) { // making 3 tokens
            if (i == 2) { // handling newline character
                line = line.substr(line.rfind(delim)+1, string::npos);
                line.resize(line.length()); // remove newline
                tokens.push_back(line);
            }
        tokens.push_back(line.substr(0, line.find(delim)));
        line = line.substr(line.find(delim)+1, string::npos);
    }
        if(tokens.at(0) == converted) {
            /*SYSTEMTIME time;
            GetLocalTime(&time);
            string Time = to_string(time.wHour) + ":" + to_string(time.wMinute) + ":" + to_string(time.wSecond);*/
            success = 1;
            cout << tokens.at(0) << "\t" << tokens.at(1) << "\t" << tokens.at(2) << "\t" << /*Time <<*/ endl;
        }
    }
    if (success == 0) {
        cout << "Symbol not found." << endl;
    }
    file.close();
}

void stockAccount::getportfolio(vector<stockhistory>& stock) {
    double portval = getBalance();
    cout << "Cash Balance = $" << getBalance() << endl;
    cout << "\nSymbol   Company     Number  Price   Total\n";
    for(int i = 0; i < stock.size(); i++){
        cout << stock[i].symbol << "\t" << stock[i].company
             << "\t\t" << stock[i].number << "\t" << stock[i].price
             << "\t" << stock[i].total << endl;
        portval += stock[i].total;
    }
    cout << "\nTotal Portfolio Value: $" << portval << endl;
}


void stockAccount::buy(vector<stockhistory>& stock) {  //fully works so f ya'll
    cout << "Enter buy options\n(FORMAT: symbol number-of-stocks price-to-pay-per) : ";
    vector<string> input = inputtoarray();
    //this begins the search to see if symbol matches with text file
    //input deconstructed into a vector with 3 entities in this order: symbol, shares, and price to buy with
    srand(time(NULL));
    cout << endl;
    string sym = input.at(0);
    //sym converts a copy of input to start searching for match in a stock file
    string converted = "";
    for(int i= 0; i < sym.size(); i++){
        converted += toupper(sym[i]);
    }
    int num = (rand()%4) + 1;
    string name = "stock" + to_string(num) + ".txt";
    string name2 = "C:\\Users\\jaymc\\CLionProjects\\project2\\" + name;
    ifstream file(name2);
    string line;
    bool success = 0;
    while (getline(file, line)) {
        string delim = "\t";
        vector <string> tokens;
        for (int i = 0; i < 3; i++) { // making 3 tokens
            if (i == 2) { // handling newline character
                line = line.substr(line.rfind(delim)+1, string::npos);
                line.resize(line.length()); // remove newline
                tokens.push_back(line);
            }
            tokens.push_back(line.substr(0, line.find(delim)));
            line = line.substr(line.find(delim)+1, string::npos);
        }
        if(tokens.at(0) == converted) { //for the conditional of when symbol matches. carries out rest of function
            success = 1;
            int shares = stoi(input.at(1));
            double amount = stod(input.at(2));
            if (amount >= stod(tokens.at(2))){
                if(shares*amount <= getBalance()){
                    setBalance (getBalance() - (shares*amount)); //ONLY updates balance for stock object
                    cout << "Success";
                    //code below will our stock transaction and bank transaction history
                    string line = "\nBUY\t\t" + input.at(0) + "\t\t" + input.at(1) + "\t\t" + input.at(2);
                    ofstream myfile;
                    myfile.open("C:\\Users\\jaymc\\CLionProjects\\project2\\stock_transaction_history.txt", ios_base::app);
                    myfile << line;
                    myfile.close();
                    //setting a vector record for transactions
                    display2bank("BUY", stoi(input.at(1)), getBalance());
                    int i = stock.size();
                    for(int j = 0; j <= i; j++) { //meant for the portfolio values and updating shares
                        if(i == 0){
                            stock.push_back(stockhistory());
                            stock[j].symbol = input.at(0);
                            stock[j].company = tokens.at(1);
                            stock[j].number = stoi(input.at(1));
                            stock[j].price = stod(tokens.at(2));
                            stock[j].total = stock[j].number * stock[j].price;
                            break;
                        }
                        else if(stock[j].symbol == input.at(0)){
                            stock[j].number += stoi(input.at(1));
                            stock[j].total = stock[j].number * stock[j].price;
                            break;
                        }
                        else if(j == i-1 & stock[j].symbol != input.at(0)){
                            stock.push_back(stockhistory());
                            stock[i].symbol = input.at(0);
                        stock[i].company = tokens.at(1);
                        stock[i].number = stoi(input.at(1));
                        stock[i].price = stod(tokens.at(2));
                        stock[i].total = stock[i].number * stock[i].price;
                            break;
                        }
                    }
                } else
                    cout << "Cannot process transaction.";
            } else
                cout << "Cannot process transaction.";
        }
    }
    if (success == 0) {
        cout << "Symbol not found." << endl;
    }
    file.close();
}

void stockAccount::sell(vector<stockhistory>& stock){
    cout << "Enter selling options\n(FORMAT: symbol number-of-stocks price-to-pay-per) : ";
    vector<string> input = inputtoarray();
    //this begins the search to see if symbol matches with text file
    //input deconstructed into a vector with 3 entities in this order: symbol, shares, and price to buy with
    srand(time(NULL));
    cout << endl;
    string sym = input.at(0);
    //sym converts a copy of input to start searching for match in a stock file
    string converted = "";
    for(int i= 0; i < sym.size(); i++){
        converted += toupper(sym[i]);
    }
    int num = (rand()%4) + 1;
    string name = "stock" + to_string(num) + ".txt";
    string name2 = "C:\\Users\\jaymc\\CLionProjects\\project2\\" + name;
    ifstream file(name2);
    string line;
    bool success = 0;
    while (getline(file, line)) {
        string delim = "\t";
        vector <string> tokens;
        for (int i = 0; i < 3; i++) { // making 3 tokens with order repr. the order of stock txt's
            if (i == 2) { // handling newline character
                line = line.substr(line.rfind(delim)+1, string::npos);
                line.resize(line.length()); // remove newline
                tokens.push_back(line);
            }
            tokens.push_back(line.substr(0, line.find(delim)));
            line = line.substr(line.find(delim)+1, string::npos);
        }
        if(tokens.at(0) == converted) { //for the conditional of when symbol matches. carries out rest of function
            //check to see if it matches anything from the portfolio vector:
            success = 1;
            for(int i = 0; i < stock.size(); i++){
                if(input.at(0) == stock[i].symbol & stoi(input.at(1)) <= stock[i].number){ //checks if symbol also matches with a symbol of portfolio
                    int shares = stoi(input.at(1));
                    double amount = stod(input.at(2));
                    if (amount <= stod(tokens.at(2))){
                        setBalance (getBalance() + (shares*amount)); //ONLY updates balance for stock object
                        cout << "Success";
                        //code below will our stock transaction and bank transaction history
                        string line = "\nSELL\t" + input.at(0) + "\t" + input.at(1) + "\t" + input.at(2);
                        ofstream myfile;
                        myfile.open("C:\\Users\\jaymc\\CLionProjects\\project2\\stock_transaction_history.txt", ios_base::app);
                        myfile << line;
                        myfile.close();
                        //setting a vector record for transactions
                        display2bank("SELL", stoi(input.at(1)), getBalance());
                        stock[i].number -= stoi(input.at(1));
                        stock[i].price = stod(tokens.at(2));
                        stock[i].total = stock[i].number * stock[i].price;
                    } else
                        cout << "Cannot process transaction.";
                } else
                    cout << "Cannot process transaction";
            }
        }
    }
    if(success == 0)
        cout << "Symbol not found";
    file.close();
}

void stockAccount::gettransaction() {
    ifstream file("C:\\Users\\jaymc\\CLionProjects\\project2\\stock_transaction_history.txt");
    string line;
    while (getline(file, line))
        cout << line << endl;
    file.close();
}


//functions for bankAccount, a derived class for Account
bankAccount::bankAccount() {
}

void bankAccount::gettransaction(vector<stockhistory>& stock) {
    ifstream file("C:\\Users\\jaymc\\CLionProjects\\project2\\bank_transaction_history");
    string line;
    while (getline(file, line))
        cout << line << endl;
    file.close();
}

void bankAccount::deposit(vector<stockhistory>& stock) {
    double value;
    cout << "Enter your deposit amount:\t";
    cin >> value;
    validInput(value);
    cout << "Depositing $" << value << " to bank account." << endl;
    double newBal = getBalance() + value;
    setBalance(newBal);
    getportfolio(stock);
}

void bankAccount::withdraw(vector<stockhistory>& stock) {
    double value;
    cout << "Enter your deposit amount:\t";
    cin >> value;
    validInput(value);
    cout << "Withdrawing $" << value << " to bank account." << endl;
    double newBal = getBalance() - value;
    setBalance(newBal);
    getportfolio(stock);
}

void bankAccount::getportfolio(vector<stockhistory>& stock) {
    double portval = getBalance();
    cout << "Cash Balance = $" << getBalance() << endl;
    cout << "\nSymbol   Company     Number  Price   Total\n";
    for(int i = 0; i < stock.size(); i++){
        cout << stock[i].symbol << "\t" << stock[i].company
             << "\t\t" << stock[i].number << "\t" << stock[i].price
             << "\t" << stock[i].total << endl;
        portval += stock[i].total;
    }
    cout << "\nTotal Portfolio Value: $" << portval << endl;
}

