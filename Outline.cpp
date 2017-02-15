#include "cv.hpp" //Header
#include "opencv2/opencv.hpp" //Header include all
#include <vector>

using namespace std;
using namespace cv;

int* FindLargestArea(Mat origin, Mat cannies);

int main(){

	int* result;
	int i = 0;
	Mat src = imread("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\Lena.png", 1);
	Mat range, canny, copy, origin;

	if (!src.data){
		printf("NO IMAGE\n");
		return -1;
	}

	origin = src.clone();
	
	Canny(src, canny, 200, 400);
	
	Mat morph;
	Mat kernel = getStructuringElement(0, Size(7, 7));
	morphologyEx(canny, morph, MORPH_CLOSE, kernel);//close -> 팽창 1 침식 1 

	copy = morph.clone();
	
	result = FindLargestArea(src, copy);
	
	for (i = 0; i < 3; i++)
		printf("In Main: result[%d] = %d\n", i, result[i]);


	imshow("RESULT", src);
	waitKey(0);


}

int* FindLargestArea(Mat origin, Mat cannies){
	Mat src;
	int* bgr = (int*)malloc(3);
	int i = 0, count=0;
	int x = 0, y = 0;
	int nBlue = 0, nGreen = 0, nRed = 0;

	double maxcontour = 0;

	for (i = 0; i < 3; i++)
		bgr[i] = 0;

	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;

	src = origin.clone();

	findContours(cannies, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	for (i = 0; i < contours.size(); i++){
		printf("%d = %lf\n", i, contourArea(contours[i]));

		if (contourArea(contours[i])>maxcontour){
			maxcontour = contourArea(contours[i]);
			count = i;
		}

	}

	drawContours(origin, contours, count, Scalar(0, 0, 255), CV_FILLED, 8, hierarchy);

	for (x = 0; x<origin.rows; x++){
		for (y = 0; y<origin.cols; y++){
			if (origin.at<cv::Vec3b>(x, y)[0] == 0 && origin.at<cv::Vec3b>(x, y)[1] == 0 && origin.at<cv::Vec3b>(x, y)[2] == 255){
				nBlue = src.at<cv::Vec3b>(x, y-1)[0];
				nGreen = src.at<cv::Vec3b>(x, y-1)[1];
				nRed = src.at<cv::Vec3b>(x, y-1)[2];
			}
		}
	}
		
	bgr[0] = nBlue;
	bgr[1] = nGreen;
	bgr[2] = nRed;

	printf("In Function: Blue = %d, Green = %d, Red = %d\n", bgr[0], bgr[1], bgr[2]);
	
	return bgr;
}