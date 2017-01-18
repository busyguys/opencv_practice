#include "cv.hpp" //Header
#include "opencv2/opencv.hpp" //Header include all
#include <vector>

using namespace std;
using namespace cv;

int main(){
	int i = 0;
	int count = 0;
	Mat src = imread("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\apple.jpg", 1);
	Mat range, canny, copy, origin;
	
	Scalar from(20, 20, 135); // Blue , Green , Red
	Scalar to(200, 110, 255);
	
	if (!src.data){
		printf("NO IMAGE\n");
		return -1;
	}
	origin = src.clone();
	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;
	
//	blur(src, canny, Size(3, 3), Point(-1, 1), 2);
	inRange(src, from, to, range);
	Canny(range, canny, 80, 200);

	Mat morph;
	Mat kernel = getStructuringElement(0, Size(7, 7));
	morphologyEx(canny, morph, MORPH_CLOSE, kernel);//close -> 팽창 1 침식 1 

	copy = morph.clone();

	findContours(copy, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	for (i = 0; i < contours.size(); i++){
		drawContours(src, contours, i, Scalar(0, 255, 0), CV_FILLED, 8, hierarchy);
		Rect rect = boundingRect(contours[i]);
		if (rect.area() > 200){
			rectangle(src, rect.tl(), rect.br(), Scalar(0, 0, 255), 2, 8, 0);
			count++;
		}
	}
	//blur(src, normal, 3, Point(-1, 1), 3);
	char msg[100];
	sprintf(msg, "number of apples = %d", count);
	putText(src, msg, Point(20, 40), FONT_HERSHEY_PLAIN, 3.2, Scalar(0, 0, 255));

	imshow("NORMAL", src);
	imshow("ORIGIN", origin);
//	imshow("RANGE", range);
	imshow("Blur", canny);
//	imshow("COPY", copy);
	waitKey(0);


}