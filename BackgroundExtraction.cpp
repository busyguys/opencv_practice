#include "cv.hpp" //���⿡ �ʿ��� �� �� ����
#include "opencv2/opencv.hpp" //�̷��Ը� �ϸ� �� ��� �� ���

using namespace std;
using namespace cv;

int main(){
	Mat src, add, back, add2;
	VideoCapture capture("C:\\Users\\Administrator\\Desktop\\Study\\4�г�\\������\\OpenCV\\TrafficExample\\traffic.mp4");
	int key;
	int frame_rate = 30;
	int flag=-1;
	Mat pre;

	capture >> src;

	while (capture.read(src)){
		flag++;
		
		if (flag == 0){
			src = back;
			continue;
		}
		cvtColor(back, back, CV_RGB2GRAY);
		src.convertTo(add, CV_32F);
		back.convertTo(back, CV_32F);
		
		absdiff(back, add, add2);
		threshold(add2, add2, 50, 255, THRESH_BINARY);
		add2.convertTo(add2, CV_8U);

		
		imshow("ORG", src);
		imshow("CV_32F", add);
		imshow("CV_32F2", add2);
	
		key = waitKey(frame_rate);

		if (key == 27)
			break;
	}
}