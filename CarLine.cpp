#include "cv.hpp" //Header
#include "opencv2/opencv.hpp" //Header include all

using namespace std;
using namespace cv;

int main(){
	int i = 0;
	int key, frame_rate = 30;
	VideoCapture capture = ("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\TrafficExample\\traffic.mp4");
	Mat src, det, gray, hough;
	Mat origin;

	Scalar y_from(0, 170, 170);
	Scalar y_to(120, 255, 255);
	Scalar w_from(200, 200, 200);
	Scalar w_to(255, 255, 255);
	Vec4i slope;

	Mat morph;
	Mat kernel = getStructuringElement(0, Size(5, 5));

	vector<Mat> v(3);

	capture >> src;
	origin = src.clone();

	if (!src.data){
		printf("NO IMAGE\n");
		return -1;
	}

	split(src, v);

	while (capture.read(src)){

		hough = src.clone();

		inRange(src, y_from, y_to, v[0]);
		GaussianBlur(v[0], v[0], Size(3, 3), 0, 0);
		Canny(v[0], v[0], 50, 100, 3);
		morphologyEx(v[0], v[0], MORPH_CLOSE, kernel);
		vector<Vec4i> lines;
		HoughLinesP(v[0], lines, 1, CV_PI / 180, 150, 100, 100);
		
		for (i = 0; i < lines.size(); i++){
			Vec4i l = lines[i];
			line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 255, 255), 3);	
		}
		
		

		inRange(src, w_from, w_to, v[1]);
		GaussianBlur(v[1], v[1], Size(3, 3), 0, 0);
		Canny(v[1], v[1], 50, 100, 3);
		morphologyEx(v[1], v[1], MORPH_CLOSE, kernel);

		vector<Vec4i> liness;
		HoughLinesP(v[1], liness, 1, CV_PI / 180, 80, 30, 10);
		for (i = 0; i < liness.size(); i++){
			Vec4i l = liness[i];
			line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 255, 0), 3);

		}

		cvtColor(src, v[2], CV_BGR2GRAY);
//		merge(v, morph);

		//imshow("LINE", src);
		//imshow("YELLOW", v[0]);
		//imshow("WHITE", v[1]);
		//imshow("HOUGH", morph);

		imshow("RESULT", src);

		key = waitKey(frame_rate);

		if (key == 27)
			break;

	}

}