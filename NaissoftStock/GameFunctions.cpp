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
	"의 성공적인 새 전략",
	", 환율 급등으로 주가 폭등",
	"에 외국인의 대규모 투자로 호재",
};

char *BadNews[MAX_NEWS] =
{
	"의 새 상품 대 실패... CEO 해임 위기",
	", 지금 추세로는 위험하다 - 전문가 분석",
	"의 위기... 시급한 대책 마련 필요",
	", 환율로 인한 심각한 피해",
	" 주식 팔자.. 외국인 대규모 매도에 주가 급락",
};

char *Infos[MAX_COMPANY] =
{
	" Naissoft는 자칭 대한민국 최대 규모의 소프트웨어 개발 업체입니다.\n 유틸리티, 게임 등 여러 가지 프로그램들을 개발하고 있죠.",
	" 앵그리소프트웨어너드는 나이스소프트에 항상 밀리는 비운의 소프트웨어 업체입니다.\n 이름이 비슷하다며 앵그리 비디오 게임 너드가 소송을 걸었다는 소문이 있어요.",
	" 암겨농업은 산지에서 갓 생산된 싱싱한 작물을 전국에 유통하고 식품을 만드는 회사입니다.\n 특이한 이름이 회사 마케팅에 도움을 주죠.\n 최근은 경운기 등 농기구도 생산하고 있답니다.",
	" MK Electronics는 전자제품 생산 회사입니다.\n TV, PC, 스마트폰, 냉장고 등을 생산하죠.",
	" 폭펭군수는 군수 물자 생산 업체입니다.\n 이름답게 폭탄을 주로 생산하는 회사예요.",
	" CJ 제일손연재는 패스트 푸드 업체입니다.\n 손연재란 먹을 손(飡), 잔치 연(宴), 집 재(齋) 로,\n 항상 먹는 잔치가 벌어지는 집이라는 의미랍니다.",
	" KJS 시스템은 기업, 서버용 소프트웨어를 개발하는 회사입니다.\n 주로 가상 머신, 개발자 도구 등을 만들죠.",
	" Fruit는 유명한 모바일 기기 회사입니다.\n 태블릿, 스마트폰, 스마트 워치 등을 생산하고 있어요.\n Grand Theft Auto V™에 출연한 적이 있답니다.",
	" 수배자 모터스는 자동차를 개발/생산하는 업체입니다.\n 독자적인 엔진도 개발 중이며, 독일의 자동차 회사들과 경쟁 중입니다.",
	" 기야조선업은 기야그룹 산하의 중공업 회사로, 배를 만드는 회사랍니다.",
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
	printf(" Stock! - Windows®용 주식 게임\n ver 1.5.1022\n\n B 사기, S 팔기, V 목록, E 저장, I 회사 정보, Esc 메뉴");
	if (timemode == 1) printf(" W 기다리기");
	gotoxy(0, 4);
	printf("\n 현재 내 돈 : %d원, 갚아야 할 돈 : %d원\n\n\n\n", Money, loanMoney);

	ShowStockPrice(viewmode);

	printf("\n %d월 %d일 %d시", month + 1, day + 1, hour);
	printf("\n\n 이번 달의 세금은 %d원입니다. %d일 남았습니다.\n", (15000 + (Money / 100)), days[month] - day);
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
	if (rand() % 4 == 0)
		printf(" 팁 : %s", Tips[rand() % MAX_TIP]);
	else
	{
		int comp = rand() % MAX_COMPANY;
		if (ifGood[comp] == true) printf(" NEWS : %s%s", CompanyName[comp], GoodNews[rand() % MAX_NEWS]);
		else printf(" NEWS : %s%s", CompanyName[comp], BadNews[rand() % MAX_NEWS]);
	}
}

void buyMenu(int order)
{
	char ch;
	int amount;

	system("cls");
	titleLine("주식 사기");

	printf(" 현재 %s 회사의 주가는 %d원입니다.\n 구입하시겠습니까? Y / N", CompanyName[order], StockPrice[order]);
	scanf(" %c", &ch);

	if (ch == 'Y' || ch == 'y')
	{
		printf("\n 몇 개를 구입하시겠습니까?\n");
		scanf("%d", &amount);

		buyStock(order, amount);
	}
	printf("\n\n 구입하였습니다.");
	Sleep(2000);
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

void loanMenu()
{
	int loanmoney;

	system("cls");
	titleLine("대  출");
	printf("\n 얼마를 대출받으시겠습니까?");
	scanf("%d", &loanmoney);
	loan(loanmoney);

	return;
}

void showCompanyInfo()
{
	int i = 0;
	char ch = '\0';

	system("cls");
	while (ch != 27)
	{
		system("cls");
		titleLine("회사 정보");

		gotoxy(0, 5);
		printf(" %d / %d. W, S 키로 넘겨 볼 수 있습니다.\n 회사 : %s\n\n", i + 1, MAX_COMPANY, CompanyName[i]);
		printf("%s", Infos[i]);

		ch = getch();

		switch (ch)
		{
		case 'W':
		case 'w':
			if (i < MAX_COMPANY - 1) i++;
			break;
		case 'S':
		case 's':
			if (i > 0) i--;
			break;
		}
	}
	system("cls");
}