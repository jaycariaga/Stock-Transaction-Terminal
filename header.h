//
// Created by jaymc on 4/17/2018.
//

#ifndef PROJECT2_HEADER_H
#define PROJECT2_HEADER_H

#endif //PROJECT2_HEADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <stdio.h>

using namespace::std;

struct stockhistory{ //for stock_transaction_history and portfolios
    string symbol;
    string company;
    int number; //number of stocks
    double price;
    double total;
};


void stockmenu(int *a);
void bankmenu(int *a);
vector<string> inputtoarray();
bool checksearch(string x);
void validinput(double &x);
void deletline();

/*
typedef struct _SYSTEMTIME {
    double wHour;
    double wMinute;
    double wSecond;
} SYSTEMTIME;
*/
class Account {
public:
    Account();
    double getBalance();
    void setBalance(double);
private:
    double cashBalance;
};

class stockAccount : public Account{
public:
    stockAccount();
    void getstockprice();
    void buy(vector<stockhistory>& );
    void sell(vector<stockhistory>&);
    void getportfolio(vector<stockhistory>&);
    void gettransaction();
    void display2bank(string, int, double);

private:

};

class bankAccount : public Account{
private:
public:
    bankAccount();
    void deposit(vector<stockhistory>&);
    void withdraw(vector<stockhistory>&);
    void gettransaction(vector<stockhistory>&);
    void getportfolio(vector<stockhistory>&);
};




