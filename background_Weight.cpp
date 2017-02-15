#include "cv.hpp" //여기에 필요한 거 다 있음
#include "opencv2/opencv.hpp" //이렇게만 하면 다 뜬다 다 뜬다

using namespace std;
using namespace cv;

int* FindLargestArea(Mat origin, Mat cannies);

int main(){
	VideoCapture inputVideo("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\TrafficExample\\traffic.mp4");
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

int* FindLargestArea(Mat origin, Mat cannies){
	Mat src;
	int* bgr = (int*)malloc(3);
	int i = 0, count = 0;
	int x = 0, y = 0;
	int nBlue = 0, nGreen = 0, nRed = 0;

	double maxcontour = 0;

	for (i = 0; i < 3; i++)
		bgr[i] = 0;

	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;

	src = origin.clone();

	findContours(cannies, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	for (i = 0; i < contours.size(); i++){
		printf("%d = %lf\n", i, contourArea(contours[i]));

		if (contourArea(contours[i])>maxcontour){
			maxcontour = contourArea(contours[i]);
			count = i;
		}

	}

	drawContours(origin, contours, count, Scalar(0, 0, 255), CV_FILLED, 8, hierarchy);

	for (x = 0; x<origin.rows; x++){
		for (y = 0; y<origin.cols; y++){
			if (origin.at<cv::Vec3b>(x, y)[0] == 0 && origin.at<cv::Vec3b>(x, y)[1] == 0 && origin.at<cv::Vec3b>(x, y)[2] == 255){
				nBlue = src.at<cv::Vec3b>(x, y - 1)[0];
				nGreen = src.at<cv::Vec3b>(x, y - 1)[1];
				nRed = src.at<cv::Vec3b>(x, y - 1)[2];
			}
		}
	}

	bgr[0] = nBlue;
	bgr[1] = nGreen;
	bgr[2] = nRed;

	printf("In Function: Blue = %d, Green = %d, Red = %d\n", bgr[0], bgr[1], bgr[2]);

	return bgr;
}