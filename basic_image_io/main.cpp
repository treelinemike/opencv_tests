// OpenCV test from: https://www.geeksforgeeks.org/opencv-c-windows-setup-using-visual-studio-2019/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <windows.h>
#include <sysinfoapi.h>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	// variables
	unsigned long i;
	char mystr[255];
	VideoWriter myVideoWriter;
	ULONGLONG start_ms, end_ms, duration_ms;
	unsigned long N_frames;

	// Read the image file
	//Mat image_raw = imread("G:\\My Drive\\surgnav\\20211011-phantom-test\\L_002\\L00000003.tif");
	Mat image_raw = imread("G:\\My Drive\\surgnav\\20211202-xi-testing\\002\\R\\R00000012.tif");
	Mat image;
	image_raw.copyTo(image);

	// initialize VideoWriter
	//static int myCodec = VideoWriter::fourcc('M', 'J', 'P', 'G');   // generic mp4
	//static int myCodec = VideoWriter::fourcc('v', '2', '1', '0');   // doesn't write out in real time? actually compressed?
	//static int myCodec = VideoWriter::fourcc('H', 'D', 'Y', 'C');   // doesn't work
	static int myCodec = VideoWriter::fourcc('I', 'Y', 'U', 'V');     // raw avi, yuv420p pixel format, 664,549 kb/s at 59.94 frames per second: https://stackoverflow.com/questions/46605325/recording-video-in-uyvy-codec-in-opencv
	//static int myCodec = VideoWriter::fourcc('F', 'F', 'V', '1');   // SLOW! raw? avi, bgra pixel format, 294,333 kb/s at 59.94 frames per second

	//static int myCodec = -1;
	double myFrameRate = 60 / 1.001;
	//double myFrameRate = 30 / 1.001;
	myVideoWriter = VideoWriter("C:\\Users\\f002r5k\\Desktop\\test.avi", myCodec, myFrameRate, cv::Size(image.cols,image.rows), true);

	// Check for failure
	if (image.empty())
	{
		cout << "Image Not Found!!!" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	// create a window for displaying image(s)
	namedWindow("My Window", WINDOW_AUTOSIZE);

	start_ms = GetTickCount64();

	// display a series of images
	N_frames = 35963;
	for (i = 0; i < N_frames; i++)
	{
		// Try adding some text
		image_raw.copyTo(image);
		sprintf_s(mystr, "Frame #%03d", i);
		putText(image, (string)mystr, Point(50, image.rows/2), FONT_HERSHEY_SIMPLEX, 5.0, CV_RGB(255, 255, 0),10);

		// show image
		//imshow("My Window", image);

		// write image into video
		myVideoWriter.write(image);

		// Wait for any keystroke in the window																								
		//waitKey(5);
	}

	// write video file
	myVideoWriter.release();

	// compute elapsed time
	end_ms = GetTickCount64();
	duration_ms = end_ms - start_ms;
	sprintf_s(mystr, "\r\n\nVideo write speed: %4.3f frames/sec\r\n\n", (double)N_frames / ((double)duration_ms/1e3));
	cout << mystr;

	// show image
	imshow("My Window", image);


	// write image file
	imwrite("G:\\My Drive\\surgnav\\20211202-xi-testing\\002\\R\\R00000012_appended.tif", image);

	// done, but wait for keypress
	waitKey();
	return 0;
}
