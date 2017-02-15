#include "cv.hpp" //���⿡ �ʿ��� �� �� ����
#include "opencv2/opencv.hpp" //�̷��Ը� �ϸ� �� ��� �� ���
#include "RoadDetection.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;
using namespace cv;

int main(void) {
	Mat back, canny, contour, filter, copy;
	Mat src = imread("C:\\Users\\Administrator\\Desktop\\Study\\4�г�\\������\\OpenCV\\TrafficExample\\Image3.jpg");
	
	if (!src.data) {
		printf("NO IMAGE\n");
		return -1;
	}
	
	cvtColor(src, src, CV_BGR2GRAY);

	GaussianBlur(src, src, Size(3, 3), 0, 0);
	Canny(src, canny, 20, 40);
	threshold(canny, canny, 50, 100, THRESH_BINARY);
	
	back = nonedge_area(canny, 0.3, 10);
	contour = back.clone();
	contour = FindLargestArea(copy, contour);
	
	Scalar value = mean(src, contour);
	printf("Blue = %d, Green = %d, Red = %d", int(value.val[0]), int(value.val[1]), int(value.val[2]));
	
	filter = roadFilter(int(value.val[0]), int(value.val[1]), int(value.val[2]), 1.2, src);

	imshow("ORIGIN", src);
	imshow("CANNY", canny);
	imshow("BACK", back);
	imshow("CONTOUR", contour);
	imshow("FILTER", filter);
	imshow("OTHER", copy);
	waitKey(0);

	return 0;
}