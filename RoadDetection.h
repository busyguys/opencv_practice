/*
2017 �̰������� ĸ���� ��
CCTV ���󿡼� ���θ� ���ϴ� ���α׷��� ���� �κ�
FindLargestArea -> Contour �� ���� ū ������ �����ϴ� Contour�� ���ϴ� ���α׷�.
nonedge_area -> ������ ���� �κ��� ���� n*n �� mask�� ����� ���α׷�
roadFilter -> Ư���� Scalar ���� �ָ� float ���� �������� ���� �ִ� Scalar ������ ���͸�
Normalization -> ������ Lab �������� �ٲٰ� ��� ���� ��Ȱȭ ���ִ� ���α׷�.
callBackFunc -> ���콺 �̺�Ʈ���� ���� Ŭ�� ��, �ش��ϴ� Color Space ǥ��.
LabBgrMask -> ���ȭ���� Lab�� Bgr ���� ǥ�������� Mask�� ����� �Լ�.
*/

#include "cv.hpp" //���⿡ �ʿ��� �� �� ����
#include "opencv2/opencv.hpp" //�̷��Ը� �ϸ� �� ��� �� ���

using namespace cv;

Mat Normalization(Mat src);
Mat FindLargestArea(Mat origin, Mat cannies);
Mat nonedge_area(Mat src, float sky_rate, int window_size);
Mat roadFilter(const Mat& src, double sigma, Mat mask);
Mat roadFilter2(const Mat& src, double sigma, Mat mask);
void callBackFunc2(int event, int x, int y, int flags, void* userdata);
Mat LabBgrMask(Mat origin, Mat background);//Input: Background Matrix, Output: Mask Road Image