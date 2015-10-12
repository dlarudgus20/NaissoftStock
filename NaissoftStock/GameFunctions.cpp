#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#include "GameFunctions.h"

int Money, StockMoney[MAX_COMPANY], PrevStockMoney[MAX_COMPANY], Stocks, StockDeal, loanMoney;
bool ifGood[MAX_COMPANY];
int month, day, hour;
FILE input, output;

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

char *Tips[MAX_TIP] =
{
	"주가가 쌀 때 매수하고 비쌀 때 매도해서 이익을 내세요!",
	"전략을 세워 투자 왕이 되어보세요!",
	"1달마다 세금을 냅니다. 계속 기다리다간 파산할 수 있으니 조심하세요!",
	"여러 회사의 주식을 살 수 있습니다. 회사 목록을 확인하세요!",
};

char *GoodNews[MAX_NEWS] =
{
	"의 새 상품, 인기몰이 중",
	"의 발전을 이끈 새 CEO의 경영철학...",
	", 환율 급등으로 주가 폭등",
	"에 외국인의 대규모 투자로 호재"
};

char *BadNews[MAX_NEWS] =
{
	"의 새 상품 대 실패... CEO 해임 위기",
	", 지금 추세로는 위험하다 - 전문가 분석",
	", 환율로 인한 심각한 피해",
	" 주식 팔자.. 외국인 대규모 매도에 주가 급락"
};

void init()
{
	Money = DEF_MONEY;
	for (int i = 0; i < MAX_COMPANY; i++) StockMoney[i] = 9000;
	for (int i = 0; i < MAX_COMPANY; i++) ifGood[i] = true;
	Stocks = StockDeal = 0;
	loanMoney = 0;
	ChangeStockMoney();
	hour++;
}

void ShowMain()
{
	gotoxy(0, 1);
	printf(" Stock - Windows®용 주식 게임\n ver 1.3.1004\n\n B 사기, S 팔기, V 주식 목록, P 일시 정지 / 메뉴");
	gotoxy(0, 4);
	printf("\n 현재 내 돈 : %d원, 갚아야 할 돈 : %d원\n\n\n\n", Money, loanMoney);
	ShowStockPrice();
}

void ChangeStockMoney()
{
	srand((int)time(NULL));

	for (int i = 0; i < MAX_COMPANY; i++)
	{
		if (ifGood[i] == true)
		{
			if ((rand() % 2) == 0)
			{
				StockMoney[i] += (rand() % 1000);
			}
			else
			{
				StockMoney[i] -= (rand() % 100);
			}
		}
		else
		{
			if ((rand() % 2) == 0)
			{
				StockMoney[i] += (rand() % 500);
			}
			else
			{
				StockMoney[i] -= (rand() % 1000);
			}
		}
		if (StockMoney[i] < 2000) StockMoney[i] = 2000;
		StockMoney[i] = StockMoney[i] / 10 * 10;
	}
}

void load()
{
	int stocks = 0;
	Stock tmp;

	FILE *save = fopen("save.ns3", "rb");
	if (save == NULL)
	{
		init();
		return;
	}

	fscanf(save, "%d ", &stocks);
	stocks = _rotr(stocks, 1);

	for (int i = 0; i < stocks; i++)
	{
		now = head;

		fscanf(save, "%d %d ", &tmp.company, &tmp.price);
		tmp.company = _rotr(tmp.company, 1); tmp.price = _rotr(tmp.price, 1);
		InsertStock(now, &tmp);
	}

	for (int i = 0; i < MAX_COMPANY; i++)
	{
		fscanf(save, "%d ", &StockMoney[i]);
		StockMoney[i] = _rotr(StockMoney[i], 1);
	}

	for (int i = 0; i < MAX_COMPANY; i++)
	{
		fscanf(save, "%d ", &ifGood[i]);
		ifGood[i] = _rotr(ifGood[i], 1);
	}

	fscanf(save, "%d %d %d %d %d %d %d", &Money, &loanMoney, &Stocks, &StockDeal, &month, &day, &hour);
	Money = _rotr(Money, 1); loanMoney = _rotr(loanMoney, 1); Stocks = _rotr(Stocks, 1);
	StockDeal = _rotr(StockDeal, 1); month = _rotr(month, 1); day = _rotr(day, 1); hour = _rotr(hour, 1);

	fclose(save);
}

void save()
{
	int stocks = 0;
	FILE *save = fopen("save.ns3", "wb");

	for (now = head->next; now; now = now->next) stocks++;
	fprintf(save, "%d ", _rotl(stocks, 1));

	for (now = head->next; now; now = now->next)
		fprintf(save, "%d %d ", _rotl(now->company, 1), _rotl(now->price, 1));

	for (int i = 0; i < MAX_COMPANY; i++)
		fprintf(save, "%d ", _rotl(StockMoney[i], 1));

	for (int i = 0; i < MAX_COMPANY; i++)
		fprintf(save, "%d ", _rotl(ifGood[i], 1));

	fprintf(save, "%d %d %d %d %d %d %d", _rotl(Money, 1), _rotl(loanMoney, 1), _rotl(Stocks, 1), _rotl(StockDeal, 1),
		_rotl(month, 1), _rotl(day, 1), _rotl(hour, 1));

	fclose(save);
}

void ShowStockPrice()
{
	for (int i = 0; i < MAX_COMPANY; i++)
	{
		printf(" 회사 : %-20s │ 가격 : %5d원  ", CompanyName[i], StockMoney[i]);
		if (PrevStockMoney[i] < StockMoney[i])
		{
			textcolor(2);
			printf("▲%4d원 ", StockMoney[i] - PrevStockMoney[i]);
			textcolor(7);
		}
		else if (PrevStockMoney[i] > StockMoney[i])
		{
			textcolor(14);
			printf("▼%4d원 ", -1 * (StockMoney[i] - PrevStockMoney[i]));
			textcolor(7);
		}
		printf("\n");
	}
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
			if (StockMoney[company - 1] <= Money)
			{
				system("cls");
				now = head;

				tmp.company = company - 1;
				tmp.price = StockMoney[company - 1];
				now = InsertStock(now, &tmp);

				Stocks++;
				StockDeal++;
				printf(" %d원을 주고 번째 주식을 구입하였습니다. 주식이 %d개입니다.\n", StockMoney[company - 1], Stocks);
				Money -= StockMoney[company - 1];
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
	printf("\n 현재 %s 회사 주식의 값은 %d원이고, 팔면 %d원의 이익이 나게 됩니다.\n", CompanyName[f->company], StockMoney[f->company], StockMoney[f->company] - f->price);
	printf(" 주식을 파시겠습니까? Y / N ");
	char k;
	scanf(" %c", &k);
	if (k == 'Y')
	{
		Money += (StockMoney[f->company]);
		DeleteStock(f);
	}
}

void showTipNews()
{
	gotoxy(0, 7);
	for (int i = 0; i < 80; i++) printf(" ");
	gotoxy(0, 7);
	if (rand() % 3 == 0)
		printf(" 팁 : %s", Tips[rand() % MAX_TIP]);
	else
	{
		int comp = rand() % MAX_COMPANY;
		if (ifGood[comp] == true) printf(" NEWS : %s%s", CompanyName[comp], GoodNews[rand() % MAX_NEWS]);
		else printf(" NEWS : %s%s", CompanyName[comp], BadNews[rand() % MAX_NEWS]);
	}
}