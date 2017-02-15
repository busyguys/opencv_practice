#include "cv.hpp" //여기에 필요한 거 다 있음
#include "opencv2/opencv.hpp" //이렇게만 하면 다 뜬다 다 뜬다
#include "RoadDetection.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;
using namespace cv;

int main(void) {

	char file_name[100];

	printf("이미지 파일을 입력해주세요\n");
	scanf("%s", file_name);

	Mat src = imread(file_name, 1);
	
	if (!src.data) {
		printf("NO IMAGE\n");
		return -1;
	}
	resize(src, src, Size(800, 500), 0, 0, CV_INTER_NN);

	//cvtColor(src, copy, CV_BGR2Lab);

	//GaussianBlur(src, src, Size(3, 3), 0, 0);
	//Canny(src, canny, 20, 40);
	//imshow("CANNY", canny);

	//back = nonedge_area(canny, 0.3, 10);
	//imshow("BACK", back);

	/*contour = back.clone();
	contour = FindLargestArea(copy, contour);

	Scalar value = mean(src, contour);
	printf("Blue = %d, Green = %d, Red = %d", int(value.val[0]), int(value.val[1]), int(value.val[2]));

	filter = roadFilter(int(value.val[0]), int(value.val[1]), int(value.val[2]), 1.2, src);
*/
	

	imshow("ORIGIN", src);	
	setMouseCallback("ORIGIN", callBackFunc, &src);
	
	waitKey(0);
	
	return 0;
}
