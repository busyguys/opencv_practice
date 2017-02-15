#include "cv.hpp" //���⿡ �ʿ��� �� �� ����
#include "opencv2/opencv.hpp" //�̷��Ը� �ϸ� �� ��� �� ���

using namespace std;
using namespace cv;

int main(){
	Mat src, canny;
	VideoCapture capture("C:\\Users\\Administrator\\Desktop\\Study\\4�г�\\������\\OpenCV\\TrafficExample\\traffic.mp4");
	int key;
	int number = 0;
	int count = 0;
	int frame = capture.get(CV_CAP_PROP_FPS);
	int frame_rate = frame;
	capture >> src;
	
	while (capture.read(src)){
	
		imshow("ORG", src);
	
		key = waitKey(frame_rate);

		if (count % (frame * 10) == 0){
			number++;
			printf("Count : %d, frame_rate = %d\n", number, frame_rate);
			
			
		}

		if (key == 32){
			if (frame_rate == frame)
				frame_rate = 0;
			else if (frame_rate == 0)
				frame_rate = frame;
		}
		else if (key == 27)
			break;

		count++;
	}


	
}