#pragma once
#include <Windows.h>

/**
 * Sends a simulated mouse click
 * @param[in] The x-coordinate to click at
 * @param[in] The y-coordinate to click at
 */
void Click(int x, int y)
{
	INPUT ip = { 0 };
	ip.type = INPUT_MOUSE;
	ip.mi.dwExtraInfo = 0;
	ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
	ip.mi.dx = x;
	ip.mi.dy = y;
	ip.mi.mouseData = 0;
	ip.mi.time = 0;
	SetCursorPos(x, y);
	SendInput(1, &ip, sizeof(INPUT));
}
