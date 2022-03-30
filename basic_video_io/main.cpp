#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	// variables
	unsigned long i;
	char mystr[255];
	VideoCapture myVideoCapture = VideoCapture("C:\\Users\\f002r5k\\Desktop\\test2.mov");
	VideoWriter myVideoWriter;	
	unsigned long N_frames;
	Mat thisFrame;

	if (!myVideoCapture.isOpened()) {
		cout << endl << "ERROR OPENING!!" << endl << endl;
	}

	myVideoCapture >> thisFrame;

	imshow("This Frame", thisFrame);

	// return
	return 0;
}
