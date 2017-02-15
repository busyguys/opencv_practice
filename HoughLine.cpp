#include "cv.hpp" //Header
#include "opencv2/opencv.hpp" //Header include all

using namespace std;
using namespace cv;

int main(){
	int i = 0;
	Mat src = imread("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\p96.jpg");
	Mat det, gray, hough;
	if (!src.data){
		printf("NO IMAGE\n");
		return -1;
	}
	cvtColor(src, gray, CV_BGR2GRAY);
	GaussianBlur(gray, det, Size(3, 3), 0, 0);
	Canny(gray, det, 50, 100, 3);
	//cvtColor(det, hough, CV_GRAY2BGR);

	vector<Vec4i> lines;
	HoughLinesP(det, lines, 1, CV_PI / 180, 80, 30, 10);

	for (i = 0; i < lines.size(); i++){
		Vec4i l = lines[i];
		line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 3);
	}
	//imshow("SCREEN", src);
	//imshow("DEST", det);
	imshow("LINE", src);

	waitKey(0);


}
