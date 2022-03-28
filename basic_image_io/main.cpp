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
	Mat image = image_raw;

	// Check for failure
	if (image.empty())
	{
		cout << "Image Not Found!!!" << endl;
		cin.get(); //wait for any key press
		return -1;
	}


	for (i = 0; i < 10; i++)
	{
	sprintf_s(mystr, "Frame #%03d", i);

		// Try adding some text
		image = image_raw;
		putText(image, (string) mystr, Point(100, 100), FONT_HERSHEY_SIMPLEX, 5.0, CV_RGB(125, 125, 125), 3);

		// Show our image inside a window.
		imshow("Mike's OpenCV Test Image Preview", image);

		// Wait for any keystroke in the window																								
		waitKey(100);

	}

	// write file
	imwrite("G:\\My Drive\\surgnav\\20211011-phantom-test\\L_002\\L00000003_appended.tif", image);


	// done
	waitKey();
	return 0;
}
