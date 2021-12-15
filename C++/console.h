// Header:			console.h
// Purpose:			To simplify working with advanced console functionality
// Author:			The Geek on Skates
// Date created:	2018-08-21
// Last revised:	2019-02-22

#ifndef _CONSOLE_H_WNDOWS_
#define _CONSOLE_H_WNDOWS_

#include <Windows.h>
#include <stdio.h>

#define CONSOLE_BLACK			0
#define CONSOLE_DARK_BLUE		1
#define CONSOLE_DARK_GREEN		2
#define CONSOLE_DARK_CYAN		3
#define CONSOLE_DARK_RED		4
#define CONSOLE_DARK_MAGENTA	5
#define CONSOLE_DARK_YELLOW		6
#define CONSOLE_GRAY			7
#define CONSOLE_DARK_GRAY		8
#define CONSOLE_BLUE			9
#define CONSOLE_GREEN			10
#define CONSOLE_CYAN			11
#define CONSOLE_RED				12
#define CONSOLE_MAGENTA			13
#define CONSOLE_YELLOW			14
#define CONSOLE_WHITE			15

void Console_SetBackgroundColor(unsigned short color) {
	unsigned short flags = 0;
	if (color & FOREGROUND_RED)
		flags |= BACKGROUND_RED;
	if (color & FOREGROUND_GREEN)
		flags |= BACKGROUND_GREEN;
	if (color & FOREGROUND_BLUE)
		flags |= BACKGROUND_BLUE;
	if (color & FOREGROUND_INTENSITY)
		flags |= BACKGROUND_INTENSITY;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), flags);
}

void Console_SetTextColor(unsigned short color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Console_GetScreenSize(int *x, int *y) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	GetConsoleScreenBufferInfo(console, &screen);
	*x = screen.srWindow.Right;
	*y = screen.srWindow.Bottom;
}

void Console_HideCursor() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(out, &info);
	info.bVisible = 0;
	SetConsoleCursorInfo(out, &info);
}

void Console_ShowCursor() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(out, &info);
	info.bVisible = 1;
	SetConsoleCursorInfo(out, &info);
}

void Console_GetPosition(int *x, int *y) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	GetConsoleScreenBufferInfo(console, &screen);
	*x = screen.dwCursorPosition.X;
	*y = screen.dwCursorPosition.Y;
}

void Console_MoveBy(int x, int y) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	GetConsoleScreenBufferInfo(console, &screen);
	screen.dwCursorPosition.X += x;
	screen.dwCursorPosition.Y += y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), screen.dwCursorPosition);
}

void Console_MoveTo(int x, int y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Console_MoveUp() { Console_MoveBy(0, -1); }
void Console_MoveDown() { Console_MoveBy(0, 1); }
void Console_MoveLeft() { Console_MoveBy(-1, 0); }
void Console_MoveRight() { Console_MoveBy(1, 0); }

void Console_Clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	unsigned long written;
	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, CONSOLE_WHITE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
}

void Console_ClearBuffer() {
	while (getchar() != '\n') {}
}

void Console_EchoOff() {
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_ECHO_INPUT;
	SetConsoleMode(hStdin, mode);
}

void Console_EchoOn() {
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	mode |= ENABLE_ECHO_INPUT;
	SetConsoleMode(hStdin, mode);
}

#endif // !_CONSOLE_H_WNDOWS_
