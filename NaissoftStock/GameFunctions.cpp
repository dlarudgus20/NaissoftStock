#include "GameFunctions.h"

int month, day, hour;

int viewmode, timemode;

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

int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void init()
{
	Money = DEF_MONEY;
	for (int i = 0; i < MAX_COMPANY; i++) StockPrice[i] = 9000;
	for (int i = 0; i < MAX_COMPANY; i++) ifGood[i] = true;
	Stocks = StockDeal = 0;
	loanMoney = 0;
	ChangeStockPrice();
	hour++;
	viewmode = timemode = 0;
}

void ShowMain()
{
	gotoxy(0, 1);
	printf(" Stock - Windows®용 주식 게임\n ver 1.4.1014\n\n B 사기, S 팔기, V 주식 목록, Esc 일시 정지 메뉴, T 설정");
	if (timemode == 1) printf(" W 기다리기");
	gotoxy(0, 4);
	printf("\n 현재 내 돈 : %d원, 갚아야 할 돈 : %d원\n\n\n\n", Money, loanMoney);

	ShowStockPrice(viewmode);

		printf("\n %d월 %d일 %d시", month + 1, day + 1, hour);
		printf("\n\n 1달마다 세금을 냅니다. 내야 할 세금은 %d원입니다.\n %d일 남았습니다.\n", (15000 + (Money / 100)), days[month] - day);
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
		fscanf(save, "%d ", &StockPrice[i]);
		StockPrice[i] = _rotr(StockPrice[i], 1);
	}

	for (int i = 0; i < MAX_COMPANY; i++)
	{
		fscanf(save, "%d ", &ifGood[i]);
		ifGood[i] = _rotr(ifGood[i], 1);
	}

	fscanf(save, "%d %d %d %d %d %d %d %d %d", &Money, &loanMoney, &Stocks, &StockDeal, &month, &day, &hour, &viewmode, &timemode);
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
		fprintf(save, "%d ", _rotl(StockPrice[i], 1));

	for (int i = 0; i < MAX_COMPANY; i++)
		fprintf(save, "%d ", _rotl(ifGood[i], 1));

	fprintf(save, "%d %d %d %d %d %d %d %d %d", _rotl(Money, 1), _rotl(loanMoney, 1), _rotl(Stocks, 1), _rotl(StockDeal, 1),
		_rotl(month, 1), _rotl(day, 1), _rotl(hour, 1), viewmode, timemode);

	fclose(save);
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

void buyMenu()
{
	int company, stocknum;

	system("cls");
	titleLine("주식 사기");
	printf(" 주식 가격 :\n\n");
	for (int i = 0; i < MAX_COMPANY; i++)
	{
		printf(" %d : %-20s, 가격 : %d원\n", i + 1, CompanyName[i], StockPrice[i]);
	}

	printf("\n 어느 회사의 주식을 구입하시겠습니까?\n 취소하려면 0을 선택하세요.\n");
	scanf("%d", &company);

	if (company != 0)
	{
		printf("\n 몇 개를 구입하시겠습니까?\n");
		scanf("%d", &stocknum);

		buyStock(stocknum, company);

		Sleep(500);
	}
	system("cls");
	return;
}

void sellMenu()
{
	int i, j;
	i = 1;
	while (i != 0)
	{
		system("cls");
		titleLine("주식 팔기");
		printf("\n [ 팔 주식을 고르세요 ]\n\n");
		j = 1;
		for (now = head->next; now; now = now->next)
		{
			printf("\n %d. 회사 : %-20s, 가격 : %d원", j, CompanyName[now->company], now->price);
			j++;
		}
		printf("\n 돌아가려면 0을 선택하세요.\n");
		scanf("%d", &i);
		if (i != 0) sellStock(i);
	}
	system("cls");
}

void showStats()
{
	system("cls");
	titleLine("통  계");
	printf("\n 주식을 사거나 판 횟수 : %d\n 현재 가진 돈 : %d원\n 주식 개수 : %d\n\n 돌아가려면 Enter를 누르세요.\n", StockDeal, Money, Stocks);
	getchar();
	system("cls");
}

void getKey(char *c)
{
	if (!timemode)
	{
		if (kbhit()) *c = getch();
	}
	else *c = getch();
}

void settingMenu()
{
	int select;
			system("cls");
			titleLine("설  정");
			printf(" 1. 보기 모드 전환\n 2. 시간 흐름 방식 전환\n Q 돌아가기");
			scanf("%d", &select);

			switch (select)
			{
			case 1:
				viewmode++;
				if (viewmode > 2) viewmode = 0;
				switch (viewmode)
				{
				case 0:
					printf(" 보기 방식이 기본 모드로 전환되었습니다.");
					break;
				case 1:
					printf(" 보기 방식이 내림차순 모드로 전환되었습니다.");
					break;
				case 2:
					printf(" 보기 방식이 오름차순 모드로 전환되었습니다.");
					break;
				}
				break;
			case 2:
				timemode++;
				if (timemode > 1) timemode = 0;
				switch (timemode)
				{
				case 0:
					printf(" 시간 흐름이 자동으로 전환되었습니다.");
					break;
				case 1:
					printf(" 시간 흐름이 수동으로 전환되었습니다.");
					break;
				}
				break;
			default:
				break;
			}
			Sleep(300);
			system("cls");
			return;
}