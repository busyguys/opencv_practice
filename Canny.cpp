#include "cv.hpp" //Header
#include "opencv2/opencv.hpp" //Header include all

using namespace std;
using namespace cv;

int main(){

	Mat src = imread("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\p96.jpg");
	Mat det,gray;
	if (!src.data){
		printf("NO IMAGE\n");
		return -1;
	}
	cvtColor(src, gray, CV_BGR2GRAY);
	GaussianBlur(gray, det, Size(3, 3),0,0);
	Canny(gray, det, 50, 100, 3);
	imshow("SCREEN", src);
	imshow("DEST", det);

	waitKey(0);


}
