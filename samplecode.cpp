#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main(){
	Mat src = imread("lena.png");
	imshow("SCREEN", src);
	waitKey(0);
}