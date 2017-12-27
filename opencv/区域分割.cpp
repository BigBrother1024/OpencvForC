#include <vector>
#include <stack>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>    
#include <opencv2/imgproc/imgproc.hpp>  
#include <iostream> 
using namespace std;
using namespace cv;

static Point connects[8] = { Point(-1, -1), Point(0, -1), Point(1, -1), Point(1, 0), Point(1, 1), Point(0, 1), Point(-1, 1), Point(-1, 0) };

int main(int argc, char* argv[])
{
	Mat midImage;
	Mat src = imread("yuan.png");
	if (!src.data)
	{
		return -1;
	}
	cv::namedWindow("a", CV_WINDOW_NORMAL);
	imshow("a", src);

	Mat res = Mat::zeros(src.rows, src.cols, CV_8U);
	// ���ڱ���Ƿ������ĳ��  
	Mat flagMat;
	res.copyTo(flagMat);

	// ��ֵͼ��  
	Mat bin;
	threshold(src, bin, 80, 255, CV_THRESH_BINARY);

	// ��ʼ���� 
	stack<Point> seeds;
	seeds.push(Point(0, 0));
	res.at

		<uchar>(0, 0) = 255;


	while (!seeds.empty())
	{
		Point seed = seeds.top();
		seeds.pop();

		// ���Ϊ�ѱ������ĵ�  
		flagMat.at

			<uchar>(seed.y, seed.x) = 1;

		// ����8����  
		for (size_t i = 0; i < 8; i++)
		{
			int tmpx = seed.x + connects[i].x;
			int tmpy = seed.y + connects[i].y;

			if (tmpx < 0 || tmpy < 0 || tmpx >= src.cols || tmpy >= src.rows)
				continue;
			// ǰ������û�б���ǹ��ĵ�  
			if (bin.at

				<uchar>(tmpy, tmpx) != 0 && flagMat.at

				<uchar>(tmpy, tmpx) == 0)
			{
				res.at

					<uchar>(tmpy, tmpx) = 255; // ����  
				flagMat.at

					<uchar>(tmpy, tmpx) = 1; // ���  
				seeds.push(Point(tmpx, tmpy)); // ����ѹջ  
			}
		}
	}
	cv::namedWindow("RES", CV_WINDOW_NORMAL);
	imshow("RES", res);

	waitKey();
	return 0;
}



