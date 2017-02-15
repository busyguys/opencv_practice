/////////////////////////////21200161 김정군

#include <opencv2\highgui\highgui.hpp>
// imread 와 imshow 함수 쓰기 위함
#include <opencv2\imgproc\imgproc.hpp>
#include "opencv\cv.h"
#include "opencv2\opencv.hpp"
#include <ctime>

using namespace std;
using namespace cv;

int main(){
	clock_t begin, end;
	double msec;
	begin = clock();

	Mat frame, range, hsv, range2, gray, gray2, canny, rgb_canny;
	VideoCapture capture("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\opencvtest\\주간1.avi");

	Scalar from(50, 120, 255);
	Scalar to(10, 15, 180);

	Scalar from2(180, 40, 255);
	Scalar to2(0, 0, 180);

	vector<Mat> channels(3);
	vector<Vec4i> lines;
	Vec4i k;
	Vec4i j;
	Vec4i l;

	float x1_1[100], x2_1[100], y1_1[100], y2_1[100];
	float x1_2[100], x2_2[100], y1_2[100], y2_2[100];

	float x_position1, y_position1;
	float x_position2, y_position2;

	float x1[100];
	float x2[100];
	float y1[100];
	float y2[100];

	float plus_grad[100];
	float grad[100];
	float max_grad;
	float puls_max_grad;
	int count = 0;
	int count2 = 0;
	int count3 = 0;

	int n = 1;
	int element_shape = MORPH_RECT;
	Mat element = getStructuringElement(element_shape, Size(n, n));

	double thresh = 100, maxval = 255;
	int threshType = THRESH_BINARY;

	for (;;){
		capture >> frame;
		Mat copy_frame;
		frame.copyTo(copy_frame);

		Rect rect = Rect(330, 300, 660, 280);
		//Mat roi = frame(rect);
		Mat roi(copy_frame, Rect(330, 300, 660, 280));

		if (!capture.read(frame))
			break;


		//if (capture.get(CV_CAP_PROP_POS_MSEC) > 5900)///////////////마지막에 오류가 떠서 이렇게 했습니다.
			//break;

		cvtColor(roi, hsv, CV_BGR2HSV);
		cvtColor(roi, gray, CV_BGR2GRAY);

		inRange(hsv, to, from, range);
		inRange(hsv, to2, from2, range2);

		split(roi, channels);
		Mat V = channels[2];
		Mat S = channels[1];
		Mat H = channels[0];

		V = (V & range);
		S = (S & range);
		H = (H & range);

		gray = gray & range2;


		Mat img3, pick;

		merge(channels, img3);
		cvtColor(gray, gray, CV_GRAY2BGR);
		img3 = img3 | gray;

		threshold(img3, pick, thresh = 100, maxval, threshType);

		morphologyEx(pick, pick, CV_MOP_OPEN, element);
		morphologyEx(pick, pick, CV_MOP_CLOSE, element);
		//////////////////////////////////////////////////////////////////////////////
		cvtColor(roi, gray2, CV_BGR2GRAY);
		Canny(pick, canny, 50, 200, 3);
		cvtColor(canny, rgb_canny, CV_GRAY2BGR);


		HoughLinesP(canny, lines, 1, CV_PI / 180, 50, 2, 50);

		for (size_t i = 0; i < lines.size(); i++){

			l = lines[i];

			x1[i] = l[0];
			x2[i] = l[2];
			y1[i] = l[1];
			y2[i] = l[3];

			float temp = (y1[i] - y2[i])*1.0 / (x1[i] - x2[i]) / 1.0;

			if ((-0.75 > temp) && (temp > -1.4)) {

				grad[count] = temp;
				x1_1[count] = x1[i];
				x2_1[count] = x2[i];
				y1_1[count] = y1[i];
				y2_1[count] = y2[i];
				count = count + 1;
			}
			else if ((0.7 < temp) && (temp < 1.3))
			{
				plus_grad[count2] = temp;
				x1_2[count] = x1[i];
				x2_2[count] = x2[i];
				y1_2[count] = y1[i];
				y2_2[count] = y2[i];
				count2 = count2 + 1;
			}

		}

		max_grad = grad[0];
		puls_max_grad = plus_grad[0];


		if (count > 0){
			for (int w = 0; w < count; w++){

				if (max_grad > grad[w]){
					max_grad = grad[w];
					x_position1 = x1_1[w];
					y_position1 = y1_1[w];
				}
			}
		}
		if (count2 > 0){
			for (int w = 0; w < count; w++){
				if (puls_max_grad < plus_grad[w]){
					puls_max_grad = plus_grad[w];
					x_position2 = x1_2[w];
					y_position2 = y1_2[w];
				}
			}
		}


		if (1){
			float b = y_position1 - x_position1*max_grad;
			float x_end1, x_end2, s1, s2, s3, s4;

			x_end1 = (720 - b) / max_grad;
			x_end2 = (-b) / max_grad;

			s1 = x_end1 + 330;
			s2 = 720 + 300;
			s3 = x_end2 + 330;
			s4 = 0 + 300;

			float b2 = s2 - s1*max_grad;

			x_end1 = (720 - b2) / max_grad;
			x_end2 = (-b2) / max_grad;

			k[0] = x_end1;
			k[1] = 720;
			k[2] = x_end2;
			k[3] = 0;

			if ((-0.75 > max_grad) && (max_grad > -1.4))
				line(frame, Point(k[0], k[1]), Point(k[2], k[3]), Scalar(0, 0, 255), 3);
		}

		////////////////////////////////////////////////////////////////////////////////////////
		if (1){
			float a = y_position2 - x_position2*puls_max_grad;
			float x_end3, x_end4, q1, q2, q3, q4;

			x_end3 = (720 - a) / puls_max_grad;
			x_end4 = (-a) / puls_max_grad;

			q1 = x_end3 + 330;
			q2 = 720 + 300;
			q3 = x_end4 + 330;
			q4 = 0 + 300;

			float a2 = q2 - q1*puls_max_grad;

			x_end3 = (720 - a2) / puls_max_grad;
			x_end4 = (-a2) / puls_max_grad;

			j[0] = x_end3;
			j[1] = 720;
			j[2] = x_end4;
			j[3] = 0;

			if ((0.7 < puls_max_grad) && (puls_max_grad < 1.3))
				line(frame, Point(j[0], j[1]), Point(j[2], j[3]), Scalar(0, 0, 255), 3);
		}

		count = 0;
		count2 = 0;

		for (int i = 0; i < 11; i++){
			x1[i] = 0;
			x2[i] = 0;
			y1[i] = 0;
			y2[i] = 0;
			grad[i] = 0;
		}


		//imshow("src", roi);
		imshow("before", img3);
		//imshow("color", pick);
		//imshow("gray", gray);
		//imshow("canny", canny);

		imshow("output", frame);
		waitKey(30);



	}

	end = clock();
	msec = 1000.0*(end - begin) / CLOCKS_PER_SEC;
	cout << "Run time: " << msec << " msec" << endl;

	return 0;
}