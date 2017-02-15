#include "cv.hpp" //���⿡ �ʿ��� �� �� ����
#include "opencv2/opencv.hpp" //�̷��Ը� �ϸ� �� ��� �� ���

using namespace std;
using namespace cv;

int main(){
	Mat background;
	Mat src;
	VideoCapture capture("C:\\Users\\Administrator\\Desktop\\Study\\4�г�\\������\\OpenCV\\background.mp4");
	int key;
	int frame_rate = 30;

	capture >> src;

	background = src;

	imshow("screen", background);
	while (capture.read(src)){

		imshow("SCREEN", src);
		cvtColor(src, background, CV_BGR2GRAY); // Change to Gray
		imshow("diff", background);

		key = waitKey(frame_rate);

		if (key == 27)
			break;
	}
}