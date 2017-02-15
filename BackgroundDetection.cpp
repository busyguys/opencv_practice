#include "cv.hpp" //���⿡ �ʿ��� �� �� ����
#include "opencv2/opencv.hpp" //�̷��Ը� �ϸ� �� ��� �� ���
#include "RoadDetection.h"

using namespace std;
using namespace cv;

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;
using namespace cv;

int main(void) {
	Mat frame, poly, copy;
	Mat back, fore, canny, gray;
	Mat Final, Norm;
	int key, frame_rate=30;
	int blue=0, green=0, red=0;
	
	//VideoCapture cap("example2.avi");
	VideoCapture cap("C:\\Users\\Administrator\\Desktop\\Study\\4�г�\\������\\OpenCV\\TrafficExample\\traffic2.mp4");
	int start = 0;
	BackgroundSubtractorMOG2 bg;

	while (1) {
		cap >> frame;

		if (!frame.data) {
			cout << "end" << endl;
			break;
		}

		//foreground ���
		bg(frame, fore);
		bg.getBackgroundImage(back);
		imshow("BACK", back);
		//Background-illumination-normalization.
		//Norm = Normalization(back);
		//GaussianBlur(Norm, Norm, Size(1,1), 0,0);
		
//		imshow("BACK", Norm);

		/*
		if (start == 0) {
		oldfore = fore.clone();
		start = 1;
		}
		else
		oldfore += fore.clone(); //oldfore�� �׳� ������ ������ ������ ��� ���ϴ� ����.
		*/
		cvtColor(back, gray, CV_BGR2GRAY);
		Canny(gray, canny, 10, 30, 3);
		imshow("CANNY", canny);

		threshold(canny, canny, 127, 255, CV_THRESH_BINARY);
		
		poly = nonedge_area(canny, 0.3, 8);
	
		Final = FindLargestArea(back, poly);// MASK ����
		//cvtColor(Norm, Norm, CV_BGR2HSV);
		Scalar value = mean(Norm, Final);

		printf("Blue = %d, Green = %d, Red = %d\n", int(value.val[0]), int(value.val[1]), int(value.val[2]));

//		for (int i = 0; i < 3; i++)
//			printf("The result[%d] = %d", i, result[i]);

		Final = roadFilter(int(value.val[0]), int(value.val[1]), int(value.val[2]), 1.2, Norm);

		imshow("Frame", frame);
		//imshow("Canny", canny);
		//imshow("Background", back);
	//	imshow("COPY", copy);
		//imshow("NORM", Norm);
		//imshow("final", Final);

		key = waitKey(frame_rate);

		if (key == 27)
			break;
		
		else if (key == 32){
			if (frame_rate == 30)
				frame_rate = 0;
			else if (frame_rate == 0)
				frame_rate = 30;
		}

	}

	return 0;
}




