#include <stdio.h>
#include <time.h>
#include <cv.h>
#include <highgui.h>
#define PI 3.1416
#define WINSIZE 7            //optical flow�� ������ �������� ������.  ���⼭�� 7*7
#define MAX_COUNT 100  //flow �� ��ó ����Ʈ ��� ����ϴ°�

using namespace std;
using namespace cv;
void main()
{
	int pressed_key;
	int width, height;
	IplImage* src_color_R;
	IplImage* src_grey_R;
	IplImage* pre_src_color_R;  //t-1�� �̹��� ������
	IplImage* pre_src_grey_R;  //t-1�� �̹��� ������
	IplImage* result_view_R;
	CvCapture* capture_R = cvCaptureFromFile("C:\\Users\\darke\\Desktop\\CV\\traffic3.mp4");  //��ķ �����

	cvNamedWindow("Optical Flow", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("Optical Flow", 0, 0);
	//ù �̹��� �޾ƿ���
	src_color_R = cvQueryFrame(capture_R);
	width = src_color_R->width;    //�ҽ� �̹��� ����ü���� �̹��� �� �ҷ�����
	height = src_color_R->height;   //�ҽ� �̹��� ����ü���� �̹��� ���� �ҷ�����
	printf("image width : %d    height : %d  \n", width, height);  //�̹����� ũ�⸦ ����ϱ�
	src_grey_R = cvCreateImage(cvSize(width, height), 8, 1);
	pre_src_color_R = cvCreateImage(cvSize(width, height), 8, 3);
	pre_src_grey_R = cvCreateImage(cvSize(width, height), 8, 1);
	result_view_R = cvCreateImage(cvSize(width, height), 8, 3);
	//goodfeature to track 
	//int MAX_COUNT = 100;  //flow �� ��ó ����Ʈ ��� ����ϴ°�
	int num_of_pts_R;
	int pre_num_of_pts_R;
	IplImage* eig_R = cvCreateImage(cvSize(width, height), 32, 1);
	IplImage* temp_R = cvCreateImage(cvSize(width, height), 32, 1);
	//������ ����Ǵ°�  �׳� ������ �ſ� ũ�� ����  
	CvPoint2D32f feature_points_R[5000];
	CvPoint2D32f pre_feature_points_R[5000];
	//OpenCV ȭ�鿡 ���ھ���
	char s_output_result[50];
	CvFont font;
	//����ð� ������
	clock_t start, finish; //����ð�üũ
	double duration;
	//Optical Flow
	char* status_R = 0;
	status_R = new char[MAX_COUNT];
	int flags_R = 0;
	IplImage* pyramid_R = cvCreateImage(cvSize(width, height), 8, 1);
	IplImage* prev_pyramid_R = cvCreateImage(cvSize(width, height), 8, 1);
	//result_view_R->origin = -1;  //�̹��� ���Ʒ� ������ ���̰� �ϱ�


	// initial work  ù �̹����� �� �̹��� ������ ��� ���ִ°�
	//goodfeature to track
	double quality = 0.01;
	double min_distance = 10;
	num_of_pts_R = MAX_COUNT;
	src_color_R = cvQueryFrame(capture_R);
	cvCvtColor(src_color_R, src_grey_R, CV_BGR2GRAY);
	//tracking�ϱ� ���� ��(corner)���� ã��
	cvGoodFeaturesToTrack(src_grey_R, eig_R, temp_R, feature_points_R, &num_of_pts_R, quality, min_distance, 0, WINSIZE, 0, 0.04);
	//cvFindCornerSubPix(src_grey_R, feature_points_R, num_of_pts_R, cvSize(WINSIZE, WINSIZE), cvSize(-1, -1), cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03));

	//������ draw
	for (int i = 0; i<num_of_pts_R; ++i)
		cvCircle(result_view_R, cvPointFrom32f(feature_points_R[i]), 1, CV_RGB(0, 255, 0), -1, 4, 0);

	//���� �� ó�� ���� ���� ���� ���� �������� ����
	cvCopy(src_grey_R, pre_src_grey_R);
	cvCopy(pyramid_R, prev_pyramid_R);
	//���� ã�� �� ��ǥ ����
	for (int i = 0; i<num_of_pts_R; ++i)
		pre_feature_points_R[i] = feature_points_R[i];

	pre_num_of_pts_R = num_of_pts_R;
	while (1)
	{
		start = clock();  //����ð�����

		src_color_R = cvQueryFrame(capture_R);
		cvCopy(src_color_R, result_view_R);
		cvCvtColor(src_color_R, src_grey_R, CV_BGR2GRAY);
		if (pre_num_of_pts_R>0)
		{
			printf("opflow start\n");
			cvCalcOpticalFlowPyrLK(pre_src_grey_R, src_grey_R, prev_pyramid_R, pyramid_R, pre_feature_points_R, feature_points_R, num_of_pts_R, cvSize(WINSIZE, WINSIZE), 3, status_R, 0, cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03), flags_R);
			flags_R |= CV_LKFLOW_PYR_A_READY;
			int valid_pt_R = 0;  //valid�� ���� ���� count
			for (int i = 0; i<num_of_pts_R; ++i)  //�� point�� valid ����
			{
				if (status_R[i] != 0)
					++valid_pt_R;
			}

			printf("valid_pts_R:%d\n", valid_pt_R);
			sprintf(s_output_result, "valid points : %d", valid_pt_R);    //�켱 sprintf�� ���ڿ� ����
			cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC, 0.5, 0.5, 0, 1);  //�̷� ���� ����.
			cvPutText(result_view_R, s_output_result, cvPoint(15, height - 20), &font, cvScalar(0, 255, 0));   //cvPoint�� ���� ���� ��ġ ����(uv)

			//draw result, ȭ��ǥ ������� �׸��� ���� ������ �Ÿ��� 3�� ���̷� ȭ��ǥ �׷���
			for (int i = 0; i<num_of_pts_R; i++)
			{
				if (status_R[i] == 0)  //valid �� ���� �ƴϸ� �Ѿ
					continue;
				int line_thickness = 1;
				CvScalar line_color = CV_RGB(255, 0, 0);
				CvPoint p, q;
				p.x = (int)pre_feature_points_R[i].x;
				p.y = (int)pre_feature_points_R[i].y;
				q.x = (int)feature_points_R[i].x;
				q.y = (int)feature_points_R[i].y;
				double angle;
				angle = atan2((double)p.y - q.y, (double)p.x - q.x);
				double arrow_length;
				arrow_length = sqrt(pow((float)(p.y - q.y), 2) + pow((float)(p.x - q.x), 2));

				q.x = (int)(p.x - 3 * arrow_length * cos(angle));  //3�� ���̷� ȭ��ǥ �׷���
				q.y = (int)(p.y - 3 * arrow_length * sin(angle));

				//������������ ȭ��ǥ�� �׸��� �ʴ´�.
				if ((arrow_length<1) | (arrow_length>40)) //ȭ��ǥ ���̰� �ʹ�ª�ų� ��� �ȱ׸���.
					continue;
				//draw arrow
				cvLine(result_view_R, p, q, line_color, line_thickness, CV_AA, 0);
				p.x = (int)(q.x + 5 * cos(angle + PI / 4));
				if (p.x >= width)
					p.x = width - 1;
				else if (p.x<0)
					p.x = 0;
				p.y = (int)(q.y + 5 * sin(angle + PI / 4));
				if (p.y >= height)
					p.y = height - 1;
				else if (p.y<0)
					p.y = 0;
				cvLine(result_view_R, p, q, line_color, line_thickness, CV_AA, 0);
				p.x = (int)(q.x + 5 * cos(angle - PI / 4));
				if (p.x >= width)
					p.x = width - 1;
				else if (p.x<0)
					p.x = 0;
				p.y = (int)(q.y + 5 * sin(angle - PI / 4));
				if (p.y>height)
					p.y = height - 1;
				else if (p.y<0)
					p.y = 0;
				cvLine(result_view_R, p, q, line_color, line_thickness, CV_AA, 0);
			}
		}
		//goodfeature to track
		num_of_pts_R = MAX_COUNT;
		cvGoodFeaturesToTrack(src_grey_R, eig_R, temp_R, feature_points_R, &num_of_pts_R, quality, min_distance, 0, WINSIZE, 0, 0.04);

		cvFindCornerSubPix(src_grey_R, feature_points_R, num_of_pts_R, cvSize(WINSIZE, WINSIZE), cvSize(-1, -1), cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03));

		printf("max_count_R : %d\n", num_of_pts_R);

		for (int i = 0; i<num_of_pts_R; ++i)
			cvCircle(result_view_R, cvPointFrom32f(feature_points_R[i]), 1, CV_RGB(0, 255, 0), -1, 4, 0);

		//���� �� ó�� ���� ���ݿ��� ����
		cvCopy(src_grey_R, pre_src_grey_R);
		cvCopy(pyramid_R, prev_pyramid_R);
		//���� ã�� �� ��ǥ ����
		for (int i = 0; i<num_of_pts_R; ++i)
			pre_feature_points_R[i] = feature_points_R[i];
		pre_num_of_pts_R = num_of_pts_R;
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		sprintf(s_output_result, "time : %f", duration);    //�켱 sprintf�� ���ڿ� ����
		cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC, 0.5, 0.5, 0, 1);  //�̷� ���� ����.
		cvPutText(result_view_R, s_output_result, cvPoint(width - 150, height - 20), &font, cvScalar(0, 255, 0));   //cvPoint�� ���� ���� ��ġ ����(uv)
		cvShowImage("Optical Flow", result_view_R);
		pressed_key = cvWaitKey(30);
		if (pressed_key == 'q')
			break;
	}
	cvDestroyAllWindows();
	cvReleaseCapture(&capture_R);
	if (src_grey_R)
		cvReleaseImage(&src_grey_R);
	if (pre_src_color_R)
		cvReleaseImage(&pre_src_color_R);
	if (result_view_R)
		cvReleaseImage(&result_view_R);
	//goodfeature to track 
	if (eig_R)
		cvReleaseImage(&eig_R);
	if (temp_R)
		cvReleaseImage(&temp_R);
	if (status_R)
		delete[] status_R;

}