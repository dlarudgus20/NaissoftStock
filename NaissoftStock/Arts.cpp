#include "Arts.h"

#include <stdio.h>
#include <Windows.h>

void startLogo()
{
	setcursortype(NOCURSOR);

	Sleep(500);
	textcolor(8);
	gotoxy(31, 10), printf("ⓒ 2015 Naissoft");
	Sleep(50);
	textcolor(7);
	gotoxy(31, 10), printf("ⓒ 2015 Naissoft");
	Sleep(50);
	textcolor(15);
	gotoxy(31, 10), printf("ⓒ 2015 Naissoft");
	Sleep(600);
	textcolor(7);
	gotoxy(31, 10), printf("ⓒ 2015 Naissoft");
	Sleep(50);
	textcolor(8);
	gotoxy(31, 10), printf("ⓒ 2015 Naissoft");
	Sleep(50);
	system("cls");
	textcolor(7);
	Sleep(200);

	setcursortype(NORMALCURSOR);
}

void printMainMenu()
{
	printf("\n\n\t\t\t      Stock! - 주식 게임");
	printf("\n\n\t\t\t      ⓒ 2015 Naissoft.");
	printf("\n\n\n\t\t\t항목을 선택해 주시기 바랍니다.");
	printf("\n\n\t\t\t    「 새로 시작하기 : 1」");
	printf("\n\n\t\t\t    「  불 러 오 기  : 2」");
	printf("\n\n\t\t\t    「  종       료  : 3」");
}