#include "cv.hpp" //여기에 필요한 거 다 있음
#include "opencv2/opencv.hpp" //이렇게만 하면 다 뜬다 다 뜬다

using namespace std;
using namespace cv;

int main(){

	Mat origin, src, add, back, contour;
	Mat canny, canny2, sobel;
	VideoCapture capture("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\TrafficExample\\traffic4.mp4");
	int key, i=0, count=0;
	int frame_rate = 30;
	Mat pre,not,morph, morph2;

	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;

	BackgroundSubtractorMOG2 fgbg;

	capture >> src;
	

	while (capture.read(src)){
		capture >> origin;
		imshow("ORIGIN", origin);
		cvtColor(src, src, CV_RGB2GRAY);
		GaussianBlur(src, src, Size(3, 3), 0);
		fgbg(src, back);
		fgbg.getBackgroundImage(pre);
		//imshow("ORG", src);
		imshow("PRE", pre);
		Canny(pre, canny, 10, 30, 3);
		imshow("CANNY", canny);
		bitwise_not(canny, not);
		imshow("NOT", not);
		morphologyEx(not, morph, CV_MOP_OPEN, getStructuringElement(MORPH_RECT, Size(3, 3)));
		morphologyEx(morph, morph2, CV_MOP_CLOSE, getStructuringElement(MORPH_RECT, Size(3, 3)));

		findContours(morph, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		for (i = 0; i < contours.size(); i++){
			drawContours(src, contours, i, Scalar(0, 255, 0), CV_FILLED, 8, hierarchy);
			Rect rect = boundingRect(contours[i]);
			if (rect.area() > 20000){
				rectangle(origin, rect.tl(), rect.br(), Scalar(0, 0, 255), 2, 8, 0);
				count++;
			}
		}
		
		imshow("MORPH", morph);
		imshow("MORPH2", morph2);
		
		imshow("CONTOUR", origin);
		//imshow("BACK", back);
		//imshow("BACKGROUND", canny);


		key = waitKey(frame_rate);

		if (key == 32){
			if (frame_rate != 0)
				frame_rate = 0;
			else if (frame_rate == 0)
				frame_rate = 30;

		}
		else if (key == 27)
			break;
		else if (key == 'f')
			frame_rate /= 2;
		else if (key == 's')
			frame_rate *= 2;
	}
}