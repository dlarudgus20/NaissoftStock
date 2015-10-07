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

	system("title �ֽ� ����");

	printf("\n\n\t\t\t      Stock! - �ֽ� ����");
	Sleep(100);
	printf("\n\n\t\t\t      �� 2015 Naissoft.");
	Sleep(100);
	printf("\n\n\n\t\t\t�׸��� ������ �ֽñ� �ٶ��ϴ�.");
	Sleep(100);
	printf("\n\n\t\t\t    �� ���� �����ϱ� : 1��");
	printf("\n\n\t\t\t    ��  �� �� �� ��  : 2��");
	printf("\n\n\t\t\t    ��  ��       ��  : 3��");
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
			printf("\n �Ļ�... 3000�� ������ �帮�ڽ��ϴ�.");
			getchar();
			loan(3000);
			Money = 3000;
			system("cls");
		}
		ShowMain();

		printf("\n %d�� %d�� %d��", month + 1, day + 1, hour);
		printf("\n\n 1�޸��� ������ ���ϴ�. ���� �� ������ %d���Դϴ�.\n %d�� ���ҽ��ϴ�.\n", (15000 + (Money / 100)), days[month] - day);
		
		c = '\0';
		if (kbhit()) c = getch();
		switch (c)
		{
			case 'b' :
			case 'B' :
				system("cls");
				printf(" �ֽ� ���� :\n\n");
				for (int i = 0; i < MAX_COMPANY; i++)
				{
					printf(" %d : %-20s, ���� : %d��\n", i + 1, CompanyName[i], StockMoney[i]);
				}
				
				printf("\n ��� ȸ���� �ֽ��� �����Ͻðڽ��ϱ�?\n ����Ϸ��� 0�� �����ϼ���.\n");
				scanf("%d", &company);

				printf("\n �� ���� �����Ͻðڽ��ϱ�?\n");
				scanf("%d", &stocknum);
				
				for (int i = 0; i < stocknum; i++)
				{
					if (company != 0 && company <= MAX_COMPANY)
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
							printf(" %d���� �ְ� ��° �ֽ��� �����Ͽ����ϴ�. �ֽ��� %d���Դϴ�.\n", StockMoney[company - 1], Stocks);
							Money -= StockMoney[company - 1];
							printf(" ���� ���� %d���Դϴ�.\n", Money);
						}
						else
						{
							printf(" ���� �����մϴ�. �ֽ��� �� �� �����ϴ�.\n");
							break;
						}
					}
				}
				Sleep(500);
				system("cls");
				break;
			case 'v' :
			case 'V' :
				system("cls");
				j = 0;
				if (Stocks <= 0)
				{
					printf("\n �ֽ��� �����ϴ�.\n");
				}
				else
				{
					printf("\n [ �ֽ� ��� ]\n\n");
					
					for (int i = 0; i < MAX_COMPANY; i++)
					{
						printf("\n %s �ֽ�\n", CompanyName[i]);
						j = 1;
						for (now = head->next; now; now = now->next)
						{
							if (now->company == i)
							{
								printf("\n %d. ���� : %d��", j, now->price);
								j++;
							}
						}
						printf("\n");
					}
				}
				printf("\n ���ư����� Enter�� ��������.");
				getchar();
				system("cls");
				break;
			case 'p':
			case 'P':
				system("cls");
				printf("\n������������ �Ͻ� ���� ������������\n\n ");
				printf("1. ��  ��\n\n 2. ��  ��\n\n 3. ��  ��\n\n 4. ��  ��\n\n 5. ������\n\n 6. ���ư���");

				scanf(" %c", &pausemenu);
				switch (pausemenu)
				{
				case '1':
					system("cls");
					printf("\n������������ ��  �� ������������\n\n �ֽ��� ��ų� �� Ƚ�� : %d\n ���� ���� �� : %d��\n �ֽ� ���� : %d\n\n ���ư����� �ƹ� Ű�� ��������.\n", StockDeal, Money, Stocks);
					getch();
					system("cls");
					ShowMain();
					break;
				case '2':
					system("cls");
					printf("\n �󸶸� ��������ðڽ��ϱ�?");
					scanf("%d", &loanmoney);

					loan(loanmoney);
					break;
				case '3':
					payback();
					break;
				case '4':
					system("cls");
					save();
					printf("\n ������ ����Ǿ����ϴ�.");
					Sleep(500);
					break;
				case '5':
					system("cls");
					printf("\n �����Ͻðڽ��ϱ�? ������� ���� ������ ������ϴ�.\n Y / N");
					if (getch() == 'Y') exit(0);
					break;
				case '6':
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
					printf("\n [ �� �ֽ��� �������� ]\n\n");
					j = 1;
					for (now = head->next; now; now = now->next)
					{
						printf("\n %d. ȸ�� : %-20s, ���� : %d��", j, CompanyName[now->company], now->price);
						j++;
					}
					printf("\n ���ư����� 0�� �����ϼ���.\n");
					scanf("%d", &i);
					if (i != 0)
					{
						Stock *f = FindStock(i - 1);
						printf("\n ���� %s ȸ�� �ֽ��� ���� %d���̰�, �ȸ� %d���� ������ ���� �˴ϴ�.\n", CompanyName[f->company], StockMoney[f->company], StockMoney[f->company] - f->price);
						printf(" �ֽ��� �Ľðڽ��ϱ�? Y / N ");
						char k;
						scanf(" %c", &k);
						if (k == 'Y')
						{
							Money += (StockMoney[f->company]);
							DeleteStock(f);
						}
					}
				}
				system("cls");
				break;
			default:
				break;
		}
		
		for (i = 0; i < MAX_COMPANY; i++)
		{
			PrevStockMoney[i] = StockMoney[i];
		}
		if (cnt % 20 == 0)
		{
			ChangeStockMoney();
			hour++;
		}
		if (cnt % 60 == 0)
		{
			gotoxy(0, 7);
			for (int i = 0; i < 80; i++) printf(" ");
			gotoxy(0, 7);
			if (rand() % 3 == 0)
				printf(" �� : %s", Tips[rand() % MAX_TIP]);
			else
			{
				int comp = rand() % MAX_COMPANY;
				if (ifGood[comp] == true) printf(" NEWS : %s%s", CompanyName[comp], GoodNews[rand() % MAX_NEWS]);
				else printf(" NEWS : %s%s", CompanyName[comp], BadNews[rand() % MAX_NEWS]);
			}
		}
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
		
		while (kbhit()) getch();
		Sleep(DELAY);
		cnt++;
	}
	getchar();
	UnInitStock();
	return 0;
}