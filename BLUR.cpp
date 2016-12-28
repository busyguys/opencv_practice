#include "cv.hpp" //Header
#include "opencv2/opencv.hpp" //Header include all
#include <vector>

using namespace std;
using namespace cv;

int main(){
	int i = 0;
	Mat src = imread("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\coin.jpg", 1);
	Mat gaus, normal, median, copy, contour, canny;
	if (!src.data){
		printf("NO IMAGE\n");
		return -1;
	}
	
	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;

	GaussianBlur(src, gaus, Size(3, 3), 0, 0);
	medianBlur(src, median, 7);
	Canny(median, canny, 70, 140);
	copy = canny.clone();
	
	findContours(copy, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

//	for (i = 0; i < contours.size(); i++){
	//	drawContours(src, contours, i, Scalar(0, 255, 0), CV_FILLED, 8, hierarchy);
	/*	Rect rect = boundingRect(contours[i]);
		if (rect.area() > 500)
			rectangle(src, rect.tl(), rect.br(), Scalar(0, 0, 255), 2, 8, 0);*/
//	}
	//blur(src, normal, 3, Point(-1, 1), 3);
	imshow("NORMAL", src);
	//imshow("BLUR", normal);
	imshow("GAUS", gaus);
	imshow("MEDIAN", median);

	waitKey(0);


}
