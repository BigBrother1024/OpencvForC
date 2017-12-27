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
	Mat aa;
	Laplacian(a, aa, CV_16S, 3);
	Mat aaa;
	convertScaleAbs(aa, aaa);     //��CV_16SתΪCV_8U
	imshow("Ч��ͼ", aaa);
	cvWaitKey(10000);
}