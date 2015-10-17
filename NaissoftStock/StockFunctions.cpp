#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#include "StockFunctions.h"
#include "Stock.h"

int Money, StockPrice[MAX_COMPANY], PrevStockPrice[MAX_COMPANY], Stocks, StockDeal, loanMoney;
bool ifGood[MAX_COMPANY];

char *CompanyName[MAX_COMPANY] =
{
	"Naissoft",
	"앵그리소프트웨어너드",
	"암겨농업",
	"MK Electronics",
	"폭펭군수회사",
	"CJ 제일손연재",
	"KJS공업",
	"수배자유령회사",
	"기야중공업",
};

void ChangeStockPrice()
{
	srand((int)time(NULL));

	for (int i = 0; i < MAX_COMPANY; i++)
	{
		if (ifGood[i] == true)
		{
			if ((rand() % 2) == 0)
			{
				StockPrice[i] += (rand() % 1000);
			}
			else
			{
				StockPrice[i] -= (rand() % 100);
			}
		}
		else
		{
			if ((rand() % 2) == 0)
			{
				StockPrice[i] += (rand() % 500);
			}
			else
			{
				StockPrice[i] -= (rand() % 1000);
			}
		}
		if (StockPrice[i] < 2000) StockPrice[i] = 2000;
		StockPrice[i] = StockPrice[i] / 10 * 10;
	}
}

void ShowStockPrice(int mode)
{
	if (mode == 0)
	{
		for (int i = 0; i < MAX_COMPANY; i++) PrintStockPrice(i);
		return;
	}

	int order[MAX_COMPANY], tmp;
	for (int i = 0; i < MAX_COMPANY; i++) order[i] = StockPrice[i];

	if (mode == 1)
	{
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			for (int j = 0; j < MAX_COMPANY; j++)
			{
				if (order[i] > order[j])
				{
					tmp = order[i];
					order[i] = order[j];
					order[j] = tmp;
				}
			}
		}
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			for (int j = 0; j < MAX_COMPANY; j++)
			{
				if (order[i] == StockPrice[j])
				{
					PrintStockPrice(j);
					order[i] = 0;
				}
			}
		}
	}
	if (mode == 2)
	{
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			for (int j = 0; j < MAX_COMPANY; j++)
			{
				if (order[i] < order[j])
				{
					tmp = order[i];
					order[i] = order[j];
					order[j] = tmp;
				}
			}
		}
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			for (int j = 0; j < MAX_COMPANY; j++)
			{
				if (order[i] == StockPrice[j])
				{
					PrintStockPrice(j);
					order[i] = 0;
				}
			}
		}
	}
}

void PrintStockPrice(int i)
{
	printf(" 회사 : %-20s │ 가격 : %5d원  ", CompanyName[i], StockPrice[i]);
	if (PrevStockPrice[i] < StockPrice[i])
	{
		textcolor(2);
		printf("▲%4d원 ", StockPrice[i] - PrevStockPrice[i]);
		textcolor(7);
	}
	else if (PrevStockPrice[i] > StockPrice[i])
	{
		textcolor(14);
		printf("▼%4d원 ", -1 * (StockPrice[i] - PrevStockPrice[i]));
		textcolor(7);
	}
	printf("\n");
}

void loan(int lmoney)
{
	loanMoney += lmoney;
	Money += lmoney;
}

void interest()
{
	loanMoney += (loanMoney * 0.05);
}

void payback()
{
	Money -= loanMoney;
	loanMoney = 0;
}

void buyStock(int stocknum, int company)
{
	for (int i = 0; i < stocknum; i++)
	{
		if (company <= MAX_COMPANY)
		{
			if (StockPrice[company - 1] <= Money)
			{
				system("cls");
				now = head;

				tmp.company = company - 1;
				tmp.price = StockPrice[company - 1];
				now = InsertStock(now, &tmp);

				Stocks++;
				StockDeal++;
				printf(" %d원을 주고 번째 주식을 구입하였습니다. 주식이 %d개입니다.\n", StockPrice[company - 1], Stocks);
				Money -= StockPrice[company - 1];
				printf(" 남은 돈은 %d원입니다.\n", Money);
			}
			else
			{
				printf(" 돈이 부족합니다. 주식을 살 수 없습니다.\n");
				break;
			}
		}
	}
}

void sellStock(int i)
{
	Stock *f = FindStock(i - 1);
	printf("\n 현재 %s 회사 주식의 값은 %d원이고, 팔면 %d원의 이익이 나게 됩니다.\n", CompanyName[f->company], StockPrice[f->company], StockPrice[f->company] - f->price);
	printf(" 주식을 파시겠습니까? Y / N ");
	char k;
	scanf(" %c", &k);
	if (k == 'Y')
	{
		Money += (StockPrice[f->company]);
		DeleteStock(f);
	}
}

void showStockList()
{
	system("cls");
	int j = 0;
	if (Stocks <= 0)
	{
		printf("\n 주식이 없습니다.\n");
	}
	else
	{
		titleLine("주식 목록 보기");
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			printf("\n %s 주식\n", CompanyName[i]);
			j = 1;
			for (now = head->next; now; now = now->next)
			{
				if (now->company == i)
				{
					printf("\n %d. 가격 : %d원", j, now->price);
					j++;
				}
			}
			printf("\n");
		}
	}
	printf("\n 돌아가려면 Enter를 누르세요.");
	getchar();
	system("cls");
}