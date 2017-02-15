#include "cv.hpp" //���⿡ �ʿ��� �� �� ����
#include "opencv2/opencv.hpp" //�̷��Ը� �ϸ� �� ��� �� ���

using namespace std;
using namespace cv;

int main(){
	Mat background, diff;
	Mat diff2;
	Mat src;
	VideoCapture capture("C:\\Users\\Administrator\\Desktop\\Study\\4�г�\\������\\OpenCV\\background.mp4");
	int key;
	int count = 6;
	int frame_rate = 30;

	Mat kernel = getStructuringElement(0, Size(5, 5));
	Scalar from(200, 200, 200);
	Scalar to(255, 255, 255);
	
	capture >> src;
	capture >> background;

	while (capture.read(src)){
		//inRange(src, from, to, background);
		diff2 = src - background;
		Canny(diff2, diff2, 50, 100, 3);
		morphologyEx(diff2, diff2, MORPH_CLOSE, kernel);
		//imshow("Backgrouond", background);
		//imshow("SCREEN", diff);
	//	imshow("Origin", src);
		imshow("diff", diff2);
		imshow("background", background);
		
		
		//imshow("background", background);

		key = waitKey(frame_rate);

		if (key == 27)
			break;
	}
}