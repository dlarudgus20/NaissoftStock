#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Lib.h"
#include "Stock.h"

#define DEF_STOCK 9000
#define DEF_MONEY 50000
#define DELAY 100

#define MAX_COMPANY 9
#define MAX_TIP 4
#define MAX_NEWS 4

extern int Money, StockMoney[MAX_COMPANY], PrevStockMoney[MAX_COMPANY], Stocks, StockDeal, loanMoney;
extern bool ifGood[MAX_COMPANY];
extern FILE input, output;
extern int month, day, hour;
extern char *CompanyName[MAX_COMPANY], *Tips[MAX_TIP], *GoodNews[MAX_NEWS], *BadNews[MAX_NEWS];
extern Stock *head, *now, tmp;

void init();

void ShowMain();

void ChangeStockMoney();

void load();

void save();

void ShowStockPrice();

void loan(int);

void interest();

void payback();