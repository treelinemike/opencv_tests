// read input video
// add text to each frame
// and write back out to a new video file
//
// TODO: seems accurate up to the last frame which isn't read nicely by OpenCV!!
// TODO: can't quite match 60/1.001 framerate, using rounding trick to get closer but still not great, can we change the time base? maybe need a better tool than OpenCV for this...
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	// variables and settings
	Mat thisFrame;
	string inputVideoFile  = "C:\\Users\\f002r5k\\Desktop\\test2.mov";
	string outputVideoFile = "C:\\Users\\f002r5k\\Desktop\\test2_output.avi";
	//static int outputCodec = VideoWriter::fourcc('I', 'Y', 'U', 'V');     // raw avi, yuv420p pixel format, 664,549 kb/s at 59.94 frames per second: https://stackoverflow.com/questions/46605325/recording-video-in-uyvy-codec-in-opencv
	static int outputCodec = VideoWriter::fourcc('v', '2', '1','0'); // TODO: get v210 working...

	// open video to capture
	VideoCapture myVideoCapture = VideoCapture(inputVideoFile);
	if (!myVideoCapture.isOpened()) {
		cout << endl << "ERROR OPENING VIDEO FILE!!" << endl << endl;
	}

	// get framerate, size, and number of frames in input video
	// this is not great
	// TODO: investigate further...
	// ffprobe -v 0 -select_streams v -show_entries stream=duration_ts,time_base,nb_frames test2.mov
	double inputFramerate = myVideoCapture.get(CAP_PROP_FPS);
	double actualFPS = round(inputFramerate * (double)100000.0) / (double)100000.0;
	char tempStr[100];
	sprintf_s(tempStr, "%0.6f", inputFramerate);	
	string inputFramerateStr = (string)tempStr;
	unsigned int numFrames = (unsigned int)myVideoCapture.get(CAP_PROP_FRAME_COUNT);
	unsigned int inputWidth = (unsigned int)myVideoCapture.get(CAP_PROP_FRAME_WIDTH);
	unsigned int inputHeight = (unsigned int)myVideoCapture.get(CAP_PROP_FRAME_HEIGHT);
	long int inputCodec = myVideoCapture.get(CAP_PROP_FOURCC);
	tempStr[0] = 0x00;
	unsigned int i;
	for (i = 0; i < 4; ++i)
	{
		sprintf_s(tempStr, "%s%c", tempStr, ((inputCodec >> (8 * i)) & 0xFF));
	}
	string inputCodecStr = (string)tempStr;
	cout << endl << "Capturing " << numFrames << " frames of " << inputWidth << " x " << inputHeight << " " << inputCodecStr << " video at " << inputFramerateStr << " frames per second." << endl << endl;
	
	// open video file to write
	VideoWriter myVideoWriter = VideoWriter(outputVideoFile, outputCodec, actualFPS, cv::Size(inputWidth, inputHeight), true);

	unsigned int nextFrameIdx = (unsigned int)myVideoCapture.get(CAP_PROP_POS_FRAMES);
	cout << endl << "Next frame to grab is #" << nextFrameIdx << endl << endl;

	// capture frames
	// for full generality we will grab() first and then retrieve()
	// if reading from multiple unsynchronized cameras, calling grab() for each will quickly pull in the frames
	// then we can more slowly decode them with retrieve()
	// in this simple example we could have either used read() which combines grab() and retrieve(),
	// or we could have just used the stream operator, e.g. myVideoCapture >> thisFrame.
	unsigned long frameNum = 0;
	while (myVideoCapture.grab())
	{
		// decode frame
		myVideoCapture.retrieve(thisFrame);

		// add frame number
		char mystr[255];
		sprintf_s(mystr, "Frame #%03d", frameNum);
		putText(thisFrame, (string)mystr, Point(50, thisFrame.rows / 2), FONT_HERSHEY_SIMPLEX, 5.0, CV_RGB(255, 0, 255), 10);
		++frameNum;

		// write frame to output video
		myVideoWriter.write(thisFrame);

		//nextFrameIdx = (unsigned int)myVideoCapture.get(CAP_PROP_POS_FRAMES);
		//cout << endl << "Next frame to grab is #" << nextFrameIdx << endl << endl;

		// display frame
		imshow("This Frame", thisFrame);
		waitKey(1);
	} 

	cout << endl << "Last frame should be #" << (frameNum - 1) << endl << endl;

	// close output video	
	myVideoWriter.release();

	// return
	return 0;
}
