#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main()
{
	Mat a = imread("zp.jpg");
	imshow("ԭͼ", a);
	cvtColor(a, a, CV_RGB2GRAY);     //תΪ�Ҷ�ͼ
	Mat ax, ay;
	Mat axx, ayy;
	Sobel(a, ax, CV_16S, 1, 0, -1);
	Sobel(a, ay, CV_16S, 0, 1, -1);
	convertScaleAbs(ax, axx);      //��CV_16SתΪCV_8U
	convertScaleA, a);
	cvWaitKey(10000);
}