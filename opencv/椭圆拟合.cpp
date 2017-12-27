#include "cv.h"
#include "highgui.h"

int slider_pos = 70;//������ֵ
IplImage *image1 = 0, *image2 = 0, *image3 = 0;//����IplImage����
void process_image(int h);

int main(int argc, char ** argv)
{
	cv::Mat src = cv::imread("view.jpg");
	imshow("ԭʼͼ", src);
	cv::Mat qz;
	medianBlur(src, qz, 3);//ȥ��
	imshow("ȥ��ͼ", qz);
	cv::Mat src_gray;
	cvtColor(qz, src_gray, CV_RGB2GRAY);//�Ҷ�ͼ��
	cv::Mat dst = src_gray.clone();//sobel
	int nRows = dst.rows;
	int nCols = dst.cols;
	for (int i = 1; i < nRows - 1; i++)
	{
		for (int j = 1; j < nCols - 1; j++)
		{
			int temp1 = ((-1)*src_gray.at<uchar>(i - 1, j - 1) + src_gray.at<uchar>(i + 1, j - 1)
				+ (-2)*src_gray.at<uchar>(i - 1, j) + 2 * src_gray.at<uchar>(i + 1, j)
				+ (-1)*src_gray.at<uchar>(i - 1, j + 1) + src_gray.at<uchar>(i + 1, j + 1));

			int temp2 = (src_gray.at<uchar>(i - 1, j - 1) + 2 * src_gray.at<uchar>(i, j + 1) + src_gray.at<uchar>(i + 1, j - 1)
				+ (-1)*src_gray.at<uchar>(i - 1, j + 1) + (-2)*src_gray.at<uchar>(i, j + 1) + (-1)*src_gray.at<uchar>(i + 1, j + 1));

			dst.at<uchar>(i, j) = (uchar)sqrt(temp1*temp1 + temp2*temp2);
		}
	}
	imshow("��Ե��ȡ", dst);
	imwrite("bytq.jpg", dst);

	const char *filename = "view.jpg";//��Ϊǰ��ı�Ե��ȡ�����ͼ��ܲ���ﻹ����ԭͼ
	if ((image1 = cvLoadImage(filename, 0)) == 0)//ǿ��תΪ�Ҷ�ֵ
	{
		return -1;
	}
	image2 = cvCloneImage(image1);
	image3 = cvCloneImage(image1);

	cvNamedWindow("��Բ���", 1);

	cvCreateTrackbar("��ֵ", "��Բ���", &slider_pos, 255, process_image);//�����޸���ֵ

	process_image(0);
	cvWaitKey(0);
	cvReleaseImage(&image2);
	cvDestroyWindow("��Բ���");
	return 0;
}

//�������Ѱ�ҳ�����������Բ��ϻ���
void process_image(int h)
{
	CvMemStorage *stor;//�������ݽṹ����
	CvSeq *cont;
	CvBox2D32f *box;
	CvPoint *PointArray;
	CvPoint2D32f *PointArray2D32f;

	stor = cvCreateMemStorage(0);// �����ڴ��
	cont = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), stor);//��������

	cvThreshold(image1, image2, slider_pos, 255, CV_THRESH_BINARY);//��ֵ��

	cvFindContours(image2, stor, &cont, sizeof(CvContour),
		CV_RETR_LIST, CV_CHAIN_APPROX_NONE, cvPoint(0, 0));//��������

	cvZero(image2);
	cvZero(image3);

	//������������������Բ���
	for (; cont; cont = cont->h_next)
	{
		int i;
		int count = cont->total;//��������
		CvPoint center;
		CvSize size;
		int x, y, l, s;

		//�����������6������cvFitEllipse_32f��Ҫ��
		if (count<6)
		{
			continue;
		}

		//�����ڴ���㼯
		PointArray = (CvPoint *)malloc(count * sizeof(CvPoint));
		PointArray2D32f = (CvPoint2D32f*)malloc(count * sizeof(CvPoint2D32f));

		//�����ڴ����Բ����
		box = (CvBox2D32f *)malloc(sizeof(CvBox2D32f));

		//�õ��㼯
		cvCvtSeqToArray(cont, PointArray, CV_WHOLE_SEQ);

		//��CvPoint�㼯ת��ΪCvBox2D32f����
		for (i = 0; i<count; i++)
		{
			PointArray2D32f[i].x = (float)PointArray[i].x;
			PointArray2D32f[i].y = (float)PointArray[i].y;
		}

		//��ϵ�ǰ����
		cvFitEllipse(PointArray2D32f, count, box);

		//���Ƶ�ǰ����
		cvDrawContours(image3, cont, CV_RGB(255, 255, 255), CV_RGB(255, 255, 255),
			0, 1, 8, cvPoint(0, 0));

		//����Բ���ݴӸ���ת��Ϊ������ʾ
		center.x = cvRound(box->center.x);
		center.y = cvRound(box->center.y);
		size.width = cvRound(box->size.width*0.5);
		size.height = cvRound(box->size.height*0.5);
		box->angle = -box->angle;

		//����Բ
		cvEllipse(image3, center, size, box->angle, 0, 360, CV_RGB(0, 0, 255), 1, CV_AA, 0);

		free(PointArray);
		free(PointArray2D32f);
		free(box);
		//�������
		x = cvRound(center.x);
		y = cvRound(center.y);
		s = cvRound(size.width*0.5);
		l = cvRound(size.height*0.5);
		printf("��Բ���������꣺x=%d, y=%d, ����ֵ��l=%d, ����ֵ��s=%d \n", x, y, l, s);
	}
	cvShowImage("��Բ���", image3);
}
