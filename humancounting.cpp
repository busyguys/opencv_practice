#include "cv.hpp" //여기에 필요한 거 다 있음
#include "opencv2/opencv.hpp" //이렇게만 하면 다 뜬다 다 뜬다

using namespace std;
using namespace cv;

int main(){
	Mat background, diff;
	Mat diff2;
	Mat src;
	VideoCapture capture("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\background.mp4");
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