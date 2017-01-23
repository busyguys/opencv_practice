#include "cv.hpp" //여기에 필요한 거 다 있음
#include "opencv2/opencv.hpp" //이렇게만 하면 다 뜬다 다 뜬다
#include "RoadDetection.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;
using namespace cv;

void callBackFunc(int event, int x, int y, int flags, void* userdata);

Mat src = imread("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\TrafficExample\\image5.jpg",1);
Mat src2 = src.clone();
Mat src3 = src.clone();
Mat src4 = src.clone();

int counts = 1;

int main(void) {
	
	if (!src.data) {
		printf("NO IMAGE\n");
		return -1;
	}
	resize(src, src, Size(800, 500), 0, 0, CV_INTER_NN);

	//cvtColor(src, copy, CV_BGR2Lab);

	//GaussianBlur(src, src, Size(3, 3), 0, 0);
	//Canny(src, canny, 20, 40);
	//imshow("CANNY", canny);

	//back = nonedge_area(canny, 0.3, 10);
	//imshow("BACK", back);

	/*contour = back.clone();
	contour = FindLargestArea(copy, contour);

	Scalar value = mean(src, contour);
	printf("Blue = %d, Green = %d, Red = %d", int(value.val[0]), int(value.val[1]), int(value.val[2]));

	filter = roadFilter(int(value.val[0]), int(value.val[1]), int(value.val[2]), 1.2, src);
*/
	

	imshow("ORIGIN", src);	
	setMouseCallback("ORIGIN", callBackFunc, &src);
	
	waitKey(0);
	
	return 0;
}
//BGR, HSV, YCrCb, Lab
void callBackFunc(int event, int x, int y, int flags, void* userdata){

	Mat src5 = src.clone();

	cvtColor(src2, src2, CV_BGR2Lab);
	cvtColor(src3, src3, CV_BGR2HSV);
	//img_bgr = src;
	cvtColor(src4, src4, CV_BGR2YCrCb);
	//cvtColor(src, img_hls, CV_BGR2HLS);
	
	switch (event){
	case EVENT_LBUTTONDOWN:
		
		printf("%d : X = %d, Y = %d\n", counts, x, y);
		printf("BGR Screen: Scalar[0] = %d, Scalar[1] = %d, Scalar[2] = %d\n",
			src.at<Vec3b>(y, x)[0], src.at<Vec3b>(y, x)[1], src.at<Vec3b>(y, x)[2]);
		printf("Lab Screen: Scalar[0] = %d, Scalar[1] = %d, Scalar[2] = %d\n",
			src2.at<Vec3b>(y, x)[0], src2.at<Vec3b>(y, x)[1], src2.at<Vec3b>(y, x)[2]);
		printf("HSV Screen: Scalar[0] = %d, Scalar[1] = %d, Scalar[2] = %d\n",
			src3.at<Vec3b>(y, x)[0], src3.at<Vec3b>(y, x)[1], src3.at<Vec3b>(y, x)[2]);
		printf("YCrCb Screen: Scalar[0] = %d, Scalar[1] = %d, Scalar[2] = %d\n",
			src4.at<Vec3b>(y, x)[0], src4.at<Vec3b>(y, x)[1], src4.at<Vec3b>(y, x)[2]);
		printf("-----------------------------------------------------------------\n");
		//x = 0; y = 0;
		rectangle(src, Point(x-10, y-10), Point(x + 10, y + 10), Scalar(0, 0, 255), 1, 8);
		char str[200];
		sprintf(str, "%d", counts);
		putText(src, str, Point(x, y), 1, 1, Scalar(0, 0, 255));
		imshow("ORIGIN", src);
		counts++;
		break;
	}

}