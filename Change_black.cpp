#include "cv.hpp" //���⿡ �ʿ��� �� �� ����
#include "opencv2/opencv.hpp" //�̷��Ը� �ϸ� �� ��� �� ���

using namespace std;
using namespace cv;

int main(){
	Mat diff;
	Mat src;
	VideoCapture capture("C:\\Users\\Administrator\\Desktop\\Study\\4�г�\\������\\OpenCV\\freeway.wmv");
	int key;
	int frame_rate = 30;

	capture >> src;


	while (capture.read(src)){

		imshow("SCREEN", src);
		cvtColor(src, diff, CV_BGR2GRAY); // Change to Gray
		imshow("diff", diff);

		key = waitKey(frame_rate);

		if (key == 27)
			break;
	}
}