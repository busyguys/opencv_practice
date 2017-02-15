#include "cv.hpp" //여기에 필요한 거 다 있음
#include "opencv2/opencv.hpp" //이렇게만 하면 다 뜬다 다 뜬다
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <vector>

using namespace std;
using namespace cv;

int main(){
	
	Mat src;
	Mat gray, fgray;
	Mat canny, sobel;
	Mat range;
	VideoCapture capture("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\freeway.wmv");
	vector<Mat> planes;
	
	int count = 0;
	int key, x, y;
	int frame_rate = 30;
	
	capture >> src;
	Scalar from(50, 50, 0);
	Scalar to(255, 255, 50);
	
	printf("Push your number: ");
	scanf("%d", &count);
	
	
	while (capture.read(src)){
		cvtColor(src, gray, CV_BGR2GRAY);
		inRange(src, from, to, range);
		split(src, planes);
		if (count == 1){
			for (y = 0; y < range.rows;y++)
			for (x = 0; x < range.cols; x++){
				if (range.at<uchar>(y, x) != 255){
					planes[0].at<uchar>(y, x) = gray.at<uchar>(y, x);
					planes[1].at<uchar>(y, x) = gray.at<uchar>(y, x);
					planes[2].at<uchar>(y, x) = gray.at<uchar>(y, x);
				}
			}
			merge(planes, fgray);
			imshow("SCREEN", src);
			imshow("Color", fgray);
			key = waitKey(frame_rate);

			if (key == 27)
				break;
		}
		else if (count == 2){
		Mat_<Vec3b>::iterator i;
		}
	}
	//else if (){}
	//else if (){}
}
