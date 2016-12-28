#include "cv.hpp" //Header
#include "opencv2/opencv.hpp" //Header include all
#include <vector>

using namespace std;
using namespace cv;

int main(){
	int i = 0;
	int count = 0;
	Mat src = imread("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\coin.jpg", 1);
	Mat gaus, normal, median, copy, contour, canny;
	if (!src.data){
		printf("NO IMAGE\n");
		return -1;
	}

	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;

	GaussianBlur(src, gaus, Size(3, 3), 0, 0);
	medianBlur(src, median, 5);
	Canny(median, canny, 70, 200);

	Mat morph;
	Mat kernel = getStructuringElement(0, Size(5, 5));
	morphologyEx(canny, morph, MORPH_CLOSE, kernel);//close -> 팽창 1 침식 1 

	copy = morph.clone();

	findContours(copy, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	for (i = 0; i < contours.size(); i++){
		drawContours(src, contours, i, Scalar(0, 255, 0), CV_FILLED, 8, hierarchy);
		Rect rect = boundingRect(contours[i]);
		if (rect.area() > 10000){
			rectangle(src, rect.tl(), rect.br(), Scalar(0, 0, 255), 2, 8, 0);
			count++;
		}
	}
	//blur(src, normal, 3, Point(-1, 1), 3);
	char msg[100];
	sprintf(msg, "number of coins = %d", count);
	putText(src, msg, Point(20, 40), FONT_HERSHEY_PLAIN, 3.2, Scalar(20, 0, 0));
	imshow("NORMAL", src);
	imshow("CANNY", canny);
	imshow("MORPH", morph);
	//imshow("Copy", copy); // find Contours 로 인해 파일이 조금 훼손된다.
	//imshow("BLUR", normal);
	//imshow("GAUS", gaus);
	//imshow("MEDIAN", median);
	waitKey(0);


}
