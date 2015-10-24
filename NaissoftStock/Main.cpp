//
// Stock
// (c) 2015 Naissoft.
//

#include "GameFunctions.h"

int main(void)
{
	int menu, cnt, order;
	char c, pausemenu;

	system("title �ֽ� ����");

	startLogo();

	printMainMenu();
	scanf("%d", &menu);

	InitStock();
	init();
	cnt = month = day = hour = order = 0;

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
			printf("\n �Ļ�... 3000�� ������ �帮�ڽ��ϴ�.");
			getchar();
			loan(3000);
			system("cls");
		}
		ShowMain();

		gotoxy(57, 9 + order - 1);
		printf("  ");
		gotoxy(57, 9 + order + 1);
		printf("  ");
		gotoxy(57, 9 + order);
		printf("��");
		
		c = '\0';
		getKey(&c);

		switch (c)
		{
		case 'b':
		case 'B':
			buyMenu(order);
			break;
		case 'v':
		case 'V':
			showStockList();
			break;
		case 27:
			system("cls");
			titleLine("�Ͻ� ����");
			printf(" 1. ��  ��\n\n 2. ��  ��\n\n 3. ��  ��\n\n 4. ��  ��\n\n 5. ������\n\n Q ���ư���");

			scanf(" %c", &pausemenu);
			switch (pausemenu)
			{
			case '1':
				showStats();
				break;
			case '2':
				loanMenu();
				break;
			case '3':
				payback();
				break;
			case '4':
				settingMenu();
				break;
			case '5':
				system("cls");
				printf("\n �����Ͻðڽ��ϱ�? ������� ���� ������ ������ϴ�.\n Y / N");
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
		case 'E':
		case 'e':
			system("cls");
			save();
			printf("\n ������ ����Ǿ����ϴ�.");
			Sleep(500);
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
		case 'I':
		case 'i':
			showCompanyInfo();
			break;
		case '2':
			if (order < MAX_COMPANY - 1) order++;
			break;
		case '8':
			if (order > 0) order--;
			break;
		default:
			break;
		}
		for (int i = 0; i < MAX_COMPANY; i++)
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