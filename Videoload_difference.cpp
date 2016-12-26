#include "cv.hpp" //여기에 필요한 거 다 있음
#include "opencv2/opencv.hpp" //이렇게만 하면 다 뜬다 다 뜬다

using namespace std;
using namespace cv;

int main(){
	Mat diff;
	int count = 0;
	Mat change;
	Mat src;
	Mat prev_src;
	VideoCapture capture("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\freeway.wmv");
	int key;
	int frame_rate = 30;
	
	capture >> src;
	prev_src = src;
	
	while (capture.read(src)){
		
		imshow("SCREEN", src);
		
		absdiff(src, prev_src, diff);
		imshow("diff", diff);
		prev_src = src.clone();

		key = waitKey(frame_rate);
	
		if (key == 27)
			break;
	}
}