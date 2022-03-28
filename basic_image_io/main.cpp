// OpenCV test from: https://www.geeksforgeeks.org/opencv-c-windows-setup-using-visual-studio-2019/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	// variables
	unsigned int i;
	char mystr[255];

	// Read the image file
	Mat image_raw = imread("G:\\My Drive\\surgnav\\20211011-phantom-test\\L_002\\L00000003.tif");
	Mat image;
	image_raw.copyTo(image);

	// Check for failure
	if (image.empty())
	{
		cout << "Image Not Found!!!" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	// create a window for displaying image(s)
	namedWindow("My Window", WINDOW_AUTOSIZE);

	// display a series of images
	for (i = 0; i < 10; i++)
	{
		// Try adding some text
		image_raw.copyTo(image);
		sprintf_s(mystr, "Frame #%03d", i);
		putText(image, (string)mystr, Point(50, image.rows/2), FONT_HERSHEY_SIMPLEX, 5.0, CV_RGB(255, 255, 0),10);

		// show image
		imshow("My Window", image);

		// Wait for any keystroke in the window																								
		waitKey(100);
	}

	// write file
	imwrite("G:\\My Drive\\surgnav\\20211011-phantom-test\\L_002\\L00000003_appended.tif", image);

	// done, but wait for keypress
	waitKey();
	return 0;
}
