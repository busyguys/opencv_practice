#include "cv.hpp" //Header
#include "opencv2/opencv.hpp" //Header include all
#include <vector>

using namespace std;
using namespace cv;

int main(){
	int i = 0;
	int count = 0;
	Mat src = imread("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\lena.png", 1);
	Mat gray, histo;
	if (!src.data){
		printf("NO IMAGE\n");
		return -1;
	}
	cvtColor(src, gray, CV_BGR2GRAY);
	equalizeHist(gray, histo);

	imshow("NORMAL", src);
	imshow("GRAY", gray);
	imshow("HISTO", histo);
	waitKey(0);


}
