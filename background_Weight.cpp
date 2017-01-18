#include "cv.hpp" //���⿡ �ʿ��� �� �� ����
#include "opencv2/opencv.hpp" //�̷��Ը� �ϸ� �� ��� �� ���

using namespace std;
using namespace cv;

int main(){
	VideoCapture inputVideo("C:\\Users\\Administrator\\Desktop\\Study\\4�г�\\������\\OpenCV\\TrafficExample\\traffic.mp4");
	if (!inputVideo.isOpened())
	{
		cout << "Can not open inputVideo !!!" << endl;
		return -1;
	}
	Size size = Size((int)inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int)inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));
	cout << "Size = " << size << endl;

	int fps = (int)(inputVideo.get(CV_CAP_PROP_FPS));
	cout << "fps = " << fps << endl;

	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5)); // MORPH_ELLIPSE

	double alpha = 0.05;
	int nTh = 50;
	int frameNum = -1, i=0;
	int delay = 1000 / fps;
	Mat frame, grayImage;
	Mat avgImage, diffImage, mask, canny;
	for (;;)
	{
		inputVideo >> frame;
		if (frame.empty())
			break;
		frameNum++;	
		//cout << "frameNum: " << frameNum << endl;
		cvtColor(frame, grayImage, COLOR_BGR2GRAY);
		GaussianBlur(grayImage, grayImage, Size(5, 5), 0.5);
		if (frameNum == 0)
		{
			avgImage = grayImage;
			continue;
		}
		avgImage.convertTo(avgImage, CV_32F);
		grayImage.convertTo(grayImage, CV_32F);
		absdiff(grayImage, avgImage, diffImage);
		threshold(diffImage, mask, nTh, 255, THRESH_BINARY);
		mask.convertTo(mask, CV_8U);

		erode(mask, mask, kernel, Point(-1, -1), 2);
		dilate(mask, mask, kernel, Point(-1, -1), 3);

		//imshow("mask", mask);
		bitwise_not(mask, mask);
		accumulateWeighted(grayImage, avgImage, alpha, mask);

		avgImage.convertTo(avgImage, CV_8U);
		//imshow("avgImage", avgImage);
		imshow("ORIGIN", frame);

		Mat canny, hough;

		Canny(avgImage, canny, 200, 400, 3);		
		imshow("Canny", canny);
		
		vector<Vec2f> lines;
		HoughLines(canny, lines, 1, CV_PI/200, 200);

		Mat dstImage(frame.size(), CV_8UC3);
		//	cout << "lines.size() = " << lines.size() << endl;

		Vec2f params;
		float rho, theta;
		float c, s;
		float x0, y0;
		for (int k = 0; k < lines.size(); k++){
			//params = lines.at<Vec2f>(0, k);
			params = lines[k];

			rho = params[0];
			theta = params[1];
			//			printf("lines[%2d] = (rho,theta) = (%f,%f)\n", k, rho, theta);

			//drawing a line

			c = cos(theta);
			s = sin(theta);
			x0 = rho*c;
			y0 = rho*s;

			Point pt1, pt2;
			pt1.x = cvRound(x0 + 1000 * (-s));
			pt1.y = cvRound(y0 + 1000 * (c));

			pt2.x = cvRound(x0 - 1000 * (-s));
			pt2.y = cvRound(y0 - 1000 * (c));
			line(frame, pt1, pt2, Scalar(0, 0, 255), 2);
		}
		imshow("dstImage", frame);

		int cKey = waitKey(delay);
		
		if (cKey == 32){
			if (delay == 1000 / fps)
				delay = 0;
			else if (delay == 0)
				delay = 1000 / fps;
		}
		
		else if (cKey == 27) break;
		
	}
	return 0;
}