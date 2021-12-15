/**
 * This header contains functions we went over in a course I took in 2017,
 * "OpenCV 3, getting started with image processing".  I saved them here
 * because I think they'll be useful when I get to using computer vision
 * to analyze inaccessible UIs at work (and maybe some other stuff too).
 */
#pragma once
#include <opencv2\opencv.hpp>

using namespace cv;

/**
 * Reduces the range of colors an image can contain
 * @param[in, out] The image to be transformed
 * @param[in] The number of colors to allow (I think - he didn't really explain it well lol)
 * @remarks This is one of the functions I wrote as part of the course I took I took, and in
 * that lesson I used Terry's ship as the first parameter.  The end result was kind of like
 * what happens when saving an image to a different format in Paint (where Windows warns you
 * there could be a loss of color, and there usually is).  This could be very useful in using
 * computer vision to make stuff accessible, because it can probably help "de-pixelate" (is
 * that a word? lol) a UI where Citrix or Windows font smoothing make AHK's ImageSearch fail.
 */
void reduce(Mat image, int div = 64)
{
	int n1 = image.rows;
	int n2 = image.cols * image.channels();
	uchar div2 = div >> 1;

	// Just an FYI (or FMI I guess cuz this is for me) there's supposedly a more
	// efficient way to do this, using image.isContinuous() and some really wacky
	// math(?) functions like "log" (whatever that is) and bit-shifting if the
	// image is "continuous" (he REALLY didn't explain this well).  But the code
	// as it is below is still very efficient, clocking in at an average of 0.003
	// seconds.  But if we ever need it to be 10% better (apparently) I got more
	// research to do (though hopefully by then the functions he used won't seem
	// as bizarre as they do currently.
	for (int j = 0; j < n1; j++)
	{
		uchar * data = image.ptr<uchar>(j);
		for (int i = 0; i < n2; i++)
		{
			data[i] = data[i] / div * div + div2;
		}
	}
}

/**
 * Sharpens an image (increases contrast)
 * @param[in] The image to be sharpened
 * @param[out] The sharpened image
 * @remarks Like other functions from the course, this was not explained in
 * as much detail as I would have liked (lots of math I don't understand yet)
 * but it definitely seems to get the job done!  Average time is 0.02 seconds.
 */
void sharpen(const Mat & image, Mat & result)
{
	// Create an empty mat with the same parameters as our input image
	result.create(image.size(), image.type());
	
	// Save the image's channels to a variable so it doesn't have to be
	// recalculated every time we need it (good optimization tip from the course)
	int channels = image.channels();

	for (int j = 1; j < image.rows - 1; j++)
	{
		// Declare variables
		const uchar * previous = image.ptr<const uchar>(j - 1);
		const uchar * current = image.ptr<const uchar>(j);
		const uchar * next = image.ptr<const uchar>(j + 1);
		uchar * output = result.ptr<uchar>(j);

		// Not entirely sure what this does, but it seems to be
		// calculating how to "sharpen" each pixel and copying it to the result image
		for (int i = channels; i < (image.cols - 1) * channels; i++)
		{
			*output++ = saturate_cast<uchar>(5 * current[i] - current[i - channels] - current[i + channels] - previous[i] - next[i]);
		}
	}

	// He explained that in this appraoch, the borders can't be sharpened,
	// so this sets the borders of our result image to 0 (black)
	result.row(0).setTo(Scalar(0));
	result.row(result.rows - 1).setTo(Scalar(0));
	result.col(0).setTo(Scalar(0));
	result.col(result.cols - 1).setTo(Scalar(0));
}