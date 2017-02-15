//openCV
#include "cv.hpp"
#include "opencv2/opencv.hpp"
//C
#include "RoadDetection.h"
#include <stdio.h>
//C++
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

int main(void){

	char* videoFilename = "C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\TrafficExample\\traffic.mp4";

	Mat frame, fore, back, mask;

	VideoCapture cap(videoFilename);

	int fps = cap.get(CV_CAP_PROP_FPS);
	int frame_rate = fps;
	int keyboard = 0;

	BackgroundSubtractorMOG2 fgbg;

	cap >> frame;

	if (!cap.isOpened()) {
		//error in opening the video input
		cerr << "Unable to open video file: " << videoFilename << endl;
		exit(EXIT_FAILURE);
	}

	while (1) {

		//read the current frame
		if (!cap.read(frame)) {
			cerr << "Unable to read next frame." << endl;
			cerr << "Exiting..." << endl;
			exit(EXIT_FAILURE);
		}
		//foreground
		//fgbg2(frame, fore2);
		//cvtColor(frame, frame, CV_BGR2YUV);

		fgbg(frame, fore);
		//background
		fgbg.getBackgroundImage(back);
		//gray, binary

		mask = LabBgrMask(frame, back);

		imshow("ORIGIN", frame);
		imshow("MASK", mask);
		imshow("FORE", fore);

		if (keyboard == 32) {
			if (frame_rate == fps)
				frame_rate = 0;
			else if (frame_rate == 0)
				frame_rate = fps;
		}
		else if (keyboard == 27)
			break;

		keyboard = (char)waitKey(frame_rate);

	}
}