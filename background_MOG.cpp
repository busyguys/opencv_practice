#include "cv.hpp" //여기에 필요한 거 다 있음
#include "opencv2/opencv.hpp" //이렇게만 하면 다 뜬다 다 뜬다

using namespace std;
using namespace cv;

int main(){

	Mat src, add, back;
	Mat canny,sobel;
	VideoCapture capture("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\TrafficExample\\traffic.mp4");
	int key;
	int frame_rate = 5;
	Mat pre;

	BackgroundSubtractorMOG2 fgbg;

	capture >> src;

	while (capture.read(src)){
		cvtColor(src, src, CV_RGB2GRAY);
		GaussianBlur(src, src, Size(3, 3), 0);
		fgbg(src, back);
		fgbg.getBackgroundImage(pre);
		imshow("ORG", src);
		imshow("PRE", pre);
		Canny(pre, canny, 10, 30, 3);
		
		//imshow("BACK", back);
		imshow("BACKGROUND", canny);


		key = waitKey(frame_rate);

		if (key == 32){
			if (frame_rate == 5)
				frame_rate = 0;
			else if (frame_rate == 0)
				frame_rate = 5;

		}
		else if (key == 27)
			break;
	}
}