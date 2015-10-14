//
// Stock
// (c) 2015 Naissoft.
//

#include "GameFunctions.h"

int main(void)
{
	int i, j, cnt, company, stocknum, loanmoney;
	int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	int menu;
	char c, ch, pausemenu;

	setcursortype(NOCURSOR);

	Sleep(700);
	textcolor(8);
	gotoxy(31, 10), printf("ⓒ 2015 Naissoft");
	Sleep(70);
	textcolor(7);
	gotoxy(31, 10), printf("ⓒ 2015 Naissoft");
	Sleep(70);
	textcolor(15);
	gotoxy(31, 10), printf("ⓒ 2015 Naissoft");
	Sleep(1000);
	textcolor(7);
	gotoxy(31, 10), printf("ⓒ 2015 Naissoft");
	Sleep(70);
	textcolor(8);
	gotoxy(31, 10), printf("ⓒ 2015 Naissoft");
	Sleep(70);
	system("cls");
	textcolor(7);
	Sleep(300);

	setcursortype(NORMALCURSOR);

	system("title 주식 게임");

	printf("\n\n\t\t\t      Stock! - 주식 게임");
	printf("\n\n\t\t\t      ⓒ 2015 Naissoft.");
	printf("\n\n\n\t\t\t항목을 선택해 주시기 바랍니다.");
	printf("\n\n\t\t\t    「 새로 시작하기 : 1」");
	printf("\n\n\t\t\t    「  불 러 오 기  : 2」");
	printf("\n\n\t\t\t    「  종       료  : 3」");
	scanf("%d", &menu);

	InitStock();
	init();
	i = j = cnt = month = day = hour = company = 0;

	switch (menu)
	{
	case 1:
		ChangeStockMoney();
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
		ShowStockPrice(viewmode);

		printf("\n %d월 %d일 %d시", month + 1, day + 1, hour);
		printf("\n\n 1달마다 세금을 냅니다. 내야 할 세금은 %d원입니다.\n %d일 남았습니다.\n", (15000 + (Money / 100)), days[month] - day);

		c = '\0';

		if (timemode == 0)
		{
			if (kbhit()) c = getch();
		}
		else if (timemode == 1)
		{
			c = getch();
		}

		switch (c)
		{
		case 'b':
		case 'B':
			system("cls");
			titleLine("주식 사기");
			printf(" 주식 가격 :\n\n");
			for (int i = 0; i < MAX_COMPANY; i++)
			{
				printf(" %d : %-20s, 가격 : %d원\n", i + 1, CompanyName[i], StockMoney[i]);
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
			break;
		case 'v':
		case 'V':
			system("cls");
			j = 0;
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
			break;
		case 27:
			system("cls");
			titleLine("일시 정지");
			printf(" 1. 통  계\n\n 2. 대  출\n\n 3. 갚  기\n\n 4. 저  장\n\n 5. 끝내기\n\n Q 돌아가기");

			scanf(" %c", &pausemenu);
			switch (pausemenu)
			{
			case '1':
				system("cls");
				titleLine("통  계");
				printf("\n 주식을 사거나 판 횟수 : %d\n 현재 가진 돈 : %d원\n 주식 개수 : %d\n\n 돌아가려면 아무 키나 누르세요.\n", StockDeal, Money, Stocks);
				getch();
				system("cls");
				ShowMain();
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
			break;
		case 'T':
		case 't':
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
			break;
		case 'W':
		case 'w':
			if (timemode == 1)
			{
				cnt += 20;
				Sleep(300);
			}
			break;
		default:
			break;
		}
		for (i = 0; i < MAX_COMPANY; i++)
			PrevStockMoney[i] = StockMoney[i];

		if (cnt % 20 == 0)
		{
			ChangeStockMoney();
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