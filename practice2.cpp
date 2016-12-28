#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <opencv.hpp>

using namespace cv;
using namespace std;

int main(){

	VideoCapture capture("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\freeway.wmv");
	Mat frame, grayImage, range, GrayConv, notRange, unmask;
	int order;

	bool stop(false);
	double rate = capture.get(CV_CAP_PROP_FPS);
	int delay = 1000 / rate;
	int key = 0;

	Scalar from(50, 50, 0);
	Scalar to(255, 255, 60);
	vector<Mat> planes(3);
	vector<Mat> masked(3);
	bool first = true;

	cout << "Insert order: ";
	cin >> order;

	while (!capture.read(frame)){
	
	}

}