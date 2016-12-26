#include "cv.hpp" //Header
#include "opencv2/opencv.hpp" //Header include all

using namespace std;
using namespace cv;

int main(){

	Mat src = imread("C:\\Users\\Administrator\\Desktop\\Study\\4학년\\공프기\\OpenCV\\lena.png");

	if (!src.data){
		printf("NO IMAGE\n");
		return -1;
	}
	imshow("SCREEN", src);
	waitKey(0);


}