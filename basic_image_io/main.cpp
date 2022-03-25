// OpenCV test from: https://www.geeksforgeeks.org/opencv-c-windows-setup-using-visual-studio-2019/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	// Read the image file
	Mat image = imread("G:\\My Drive\\surgnav\\20211011-phantom-test\\L_002\\L00000003.tif");

	// Check for failure
	if (image.empty())
	{
		cout << "Image Not Found!!!" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	// Try adding some text
	putText(image, "Hello, world!", Point(100, 100), FONT_HERSHEY_SIMPLEX, 5.0, CV_RGB(125, 125, 125), 3);

	// write file
	imwrite("G:\\My Drive\\surgnav\\20211011-phantom-test\\L_002\\L00000003_appended.tif", image);

	// Show our image inside a window.
	imshow("Mike's OpenCV Test Image Preview", image);

	// Wait for any keystroke in the window																								
	waitKey(0);
	return 0;
}
