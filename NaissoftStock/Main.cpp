//
// Stock
// (c) 2015 Naissoft.
//

#include "GameFunctions.h"

int main(void)
{
	int i, j, cnt, company, stocknum, loanmoney;

	int menu;
	char c, pausemenu;

	system("title 주식 게임");

	printMainMenu();
	scanf("%d", &menu);

	InitStock();
	init();
	i = j = cnt = month = day = hour = company = 0;

	switch (menu)
	{
	case 1:
		ChangeStockPrice();
		save();
		break;
	case 2:
		load();
		break;
	case 3:
		exit(0);
		break;
	default:
		break;
	}
	
	system("cls");
	while (true)
	{
		if (Money <= 0)
		{
			printf("\n 파산... 3000원 대출해 드리겠습니다.");
			getchar();
			loan(3000);
			system("cls");
		}
		ShowMain();
		
		c = '\0';
		getKey(&c);

		switch (c)
		{
		case 'b':
		case 'B':
			buyMenu();
			break;
		case 'v':
		case 'V':
			showStockList();
			break;
		case 27:
			system("cls");
			titleLine("일시 정지");
			printf(" 1. 통  계\n\n 2. 대  출\n\n 3. 갚  기\n\n 4. 저  장\n\n 5. 끝내기\n\n Q 돌아가기");

			scanf(" %c", &pausemenu);
			switch (pausemenu)
			{
			case '1':
				showStats();
				break;
			case '2':
				system("cls");
				titleLine("대  출");
				printf("\n 얼마를 대출받으시겠습니까?");
				scanf("%d", &loanmoney);
				loan(loanmoney);
				break;
			case '3':
				payback();
				break;
			case '4':
				system("cls");
				save();
				printf("\n 게임이 저장되었습니다.");
				Sleep(500);
				break;
			case '5':
				system("cls");
				printf("\n 종료하시겠습니까? 저장되지 않은 정보는 사라집니다.\n Y / N");
				if (getch() == 'Y') exit(0);
				break;
			case 'Q':
			case 'q':
				break;
			default:
				break;
			}
			system("cls");
			Sleep(100);
			break;
		case 's':
		case 'S':
			sellMenu();
			break;
		case 'T':
		case 't':
			settingMenu();
			break;
		case 'W':
		case 'w':
			if (timemode == 1)
			{
				while (cnt % 20 != 0) cnt++;
				cnt += 20;
				Sleep(300);
			}
			break;
		default:
			break;
		}
		for (i = 0; i < MAX_COMPANY; i++)
			PrevStockPrice[i] = StockPrice[i];

		if (cnt % 20 == 0)
		{
			ChangeStockPrice();
			hour++;
		}

		if (cnt % 60 == 0) showTipNews();

		if (hour == 1)
		{
			for (int i = 0; i < MAX_COMPANY; i++)
			{
				if (rand() % 2 == 0) ifGood[i] = true;
				else ifGood[i] = false;
			}
		}
		if (hour > 23)
		{
			hour = 0;
			interest();
			day++;
		}
		if (day > days[month] - 1)
		{
			day = 0;
			month++;
			Money -= ((15000 + (Money / 100)) / 10) * 10;
		}
		if (month > 11) month = 0;

		if (timemode == 0)
		{
			clearbuffer();
			Sleep(DELAY);
			cnt++;
		}
		else if (timemode == 1)
		{
			clearbuffer();
			Sleep(DELAY);
		}
	}
	getchar();
	UnInitStock();
	return 0;
}