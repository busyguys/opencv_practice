#include "cv.hpp" //Header
#include "opencv2/opencv.hpp" //Header include all

using namespace std;
using namespace cv;

int main(){

	Mat src = imread("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\lena.png");
	Mat det,gray;
	vector<Mat> v;
	if (!src.data){
		printf("NO IMAGE\n");
		return -1;
	}
	cvtColor(src, det, CV_BGR2HSV);
	//Scalar h_min = cvScalar(70, 100, 100);
	//Scalar h_max = cvScalar(130, 255, 255);
	//inRange(det, h_min, h_max, gray);
	split(det, v);
	imshow("BGR", src);
	imshow("H", v[0]);
	imshow("S", v[1]);
	imshow("I", v[2]);

	waitKey(0);


}