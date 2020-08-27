#include <iostream>
#include "header.h"

int main() {
    vector<stockhistory> stock;
    stockAccount a;
    bankAccount b;
    cout << "Welcome to the Account Management System." << endl;
    int i = 0;
    int input = 0;
    while (i != 3){
        cout << "\nPlease select an account to access \n"
             << "\t1. Stock Portfolio Account \n"
             << "\t2. Bank Account\n"
             << "\t3. Exit\n\tYour selection: \t";
        cin >> i;
        if (i == 1){
            while (input != 6){
                stockmenu(&input);
                switch (input) {
                    case (1):
                        a.getstockprice();
                        break;
                    case (2):
                        a.buy(stock);
                        b.setBalance(a.getBalance()); //bank account updates itself to match with object bank balance
                        break;
                    case (3):
                        a.sell(stock);
                        b.setBalance(a.getBalance());
                        break;
                    case (4):
                        a.getportfolio(stock);
                        break;
                    case (5):
                        a.gettransaction();
                        break;
                    case (6):
                        break;
                }
            }
        }
        else if (i == 2){
            while (input != 5){
                bankmenu(&input);
                switch (input) {
                    case (1):
                        b.getportfolio(stock);
                        break;
                    case (2):
                        b.deposit(stock);
                        a.setBalance(b.getBalance());
                        break;
                    case (3):
                        b.withdraw(stock);
                        a.setBalance(b.getBalance());
                        break;
                    case (4):
                        b.gettransaction(stock);
                        break;
                    case (5):
                        break;
                }
            }
        }
        else if (i != 3){
            cout << "\nInvalid option.\n";
        }
    }

    deletline();
    return 0;
}