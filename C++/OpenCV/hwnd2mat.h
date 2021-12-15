#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

/**
 * Takes a screenshot of a window
 * @param[in] An HWND (window handle)
 * @return A cv::Mat instance containing the screenshot
 * @remarks In terms of efficiency, this function averages
 * little over 0.02 seconds, so totally fast enough for
 * just about anything we need to do at Lighthouse.
 *
 * To take a screenshot of the whole screen, set the first
 * parameter to GetDesktopWindow().  This will capture all
 * the windows that are visible on the screen.
 *
 * This came from a post on Stack Overflow:
 * https://stackoverflow.com/questions/14148758/how-to-capture-the-desktop-in-opencv-ie-turn-a-bitmap-into-a-mat
 */
Mat hwnd2mat(HWND hwnd)
{
	HDC hwindowDC, hwindowCompatibleDC;
	int height, width, srcheight, srcwidth;
	HBITMAP hbwindow;
	Mat src;
	BITMAPINFOHEADER  bi;

	hwindowDC = GetDC(hwnd);
	hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

	RECT windowsize;    // get the height and width of the screen
	GetClientRect(hwnd, &windowsize);

	srcheight = windowsize.bottom;
	srcwidth = windowsize.right;
	height = windowsize.bottom / 2;  //change this to whatever size you want to resize to
	width = windowsize.right / 2;

	src.create(height, width, CV_8UC4);

	// create a bitmap
	hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
	bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
	bi.biWidth = width;
	bi.biHeight = -height;  //this is the line that makes it draw upside down or not
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	// use the previously created device context with the bitmap
	SelectObject(hwindowCompatibleDC, hbwindow);
	// copy from the window device context to the bitmap device context
	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow
																							   // avoid memory leak
	DeleteObject(hbwindow); DeleteDC(hwindowCompatibleDC); ReleaseDC(hwnd, hwindowDC);

	return src;
}