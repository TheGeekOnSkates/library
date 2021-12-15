#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

// The Windows console supports 16 colors for both the text and its background
enum ConsoleColor
{
	Black, DarkBlue, DarkGreen, DarkCyan,
	DarkRed, DarkMagenta, DarkYellow,
	Gray, DarkGray, Blue, Green, Cyan,
	Red, Magenta, Yellow, White
};

// High-level Console API similar to C#'s
class Console
{
public:

	// Prints text to the console (stdout)
	// @param[in] The text to display
	static void Write(const char * text)
	{
		// Get a handle to the console
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		if (out == INVALID_HANDLE_VALUE) throw "Error getting console handle";

		// Set the text and background colors
		unsigned short flags = ForegroundColor;
		if (BackgroundColor & FOREGROUND_RED)
			flags |= BACKGROUND_RED;
		if (BackgroundColor & FOREGROUND_GREEN)
			flags |= BACKGROUND_GREEN;
		if (BackgroundColor & FOREGROUND_BLUE)
			flags |= BACKGROUND_BLUE;
		if (BackgroundColor & FOREGROUND_INTENSITY)
			flags |= BACKGROUND_INTENSITY;

		// Set the colors, CONSOLE the text, and set the colors back to the defaults
		if (!SetConsoleTextAttribute(out, flags)) throw "SetConsoleTextAttribute failed (before printing text).";
		printf("%s", text);
		if (!SetConsoleTextAttribute(out, ConsoleColor::White)) throw "SetConsoleTextAttribute failed (after printing text).";
	}

	// Prints text to the console (stdout)
	// @param[in] The text to display
	static void WriteLine(const char * text)
	{
		std::string s = text;
		s += "\n";
		Write(s.c_str());
	}

	// Gets user input from the console (stdin)
	static std::string ReadLine()
	{
		std::string s;
		getline(std::cin, s);
		return s;
	}

	// Clears the console
	static void Clear()
	{
		// Declare variables
		COORD topLeft = { 0, 0 };
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO screen;
		DWORD written;

		// This part I don't fully understand, admittedly copied off the web, but
		// it's Win32 code and it works, so I'm not worried.  I also added a TON
		// of extra error checking, because {bugs} lol
		if (!GetConsoleScreenBufferInfo(console, &screen)) throw "Error setting buffer info";
		if (!FillConsoleOutputCharacterA(
			console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		)) throw "Error clearing console";
		if (!FillConsoleOutputAttribute(
			console, ConsoleColor::White,
			screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		)) throw "FillConsoleOutputAttribute failed.";
		if (!SetConsoleCursorPosition(console, topLeft)) throw "Error setting cursor position.";
	}

	// Shows the cursor
	static void ShowCursor()
	{
		SetCursorVisibility(1);
	}

	// Hides the cursor
	static void HideCursor()
	{
		SetCursorVisibility(0);
	}

	// Sets the cursor position
	// @param[in] The x-coordinate
	// @param[y] The x-coordinate
	static void SetCursorPosition(int x, int y)
	{
		// Get a handle to the console
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		if (out == INVALID_HANDLE_VALUE) throw "Error getting console handle";

		COORD c = { x, y };
		if (!SetConsoleCursorPosition(out, c)) throw "Error setting cursor position";
	}

	// The background color
	static unsigned short BackgroundColor;

	// The foreground color
	static unsigned short ForegroundColor;

private:

	// Used in ShowCursor and HideCursor
	// Sets whether or not the sursor is visible
	// @param[in] TRUE to show it, FALSE to hide it
	static void SetCursorVisibility(BOOL value)
	{
		// Get a handle to the console
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		if (out == INVALID_HANDLE_VALUE) throw "Error getting console handle";

		// And set the cursor
		CONSOLE_CURSOR_INFO info;
		if (!GetConsoleCursorInfo(out, &info)) throw "Error getting cursor info";
		info.bVisible = value;
		if (!SetConsoleCursorInfo(out, &info)) throw "Error setting cursor visibility";
	}
};

// Define static members
unsigned short Console::BackgroundColor = ConsoleColor::Black;
unsigned short Console::ForegroundColor = ConsoleColor::White;