//#####################
//����
//#####################
#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;

Mat src; Mat src_gray;
RNG rng(12345);//���췽���趨һ������ֵ����ʾ�������ÿ�����ɵĽ������һ����

int main(int argc, char** argv)
{
	/// ����ԭͼ��, ����3ͨ��ͼ��
	src = imread("draw.png", 1);
	imshow("Source", src);
	/// ת���ɻҶ�ͼ�񲢽���ƽ��
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	Mat threshold_output;
	vector<vector<Point> > contours;

	/// ʹ��Threshold����Ե
	threshold(src_gray, threshold_output, 100, 255, THRESH_BINARY);
	/// �ҵ�����
	findContours(threshold_output, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// ����αƽ����� + ��ȡ���κ�Բ�α߽��
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
	}

	/// ����������� + ��Χ�ľ��ο� + Բ�ο�
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	Mat srccopy = src.clone();
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));//��[0,255)��Χ�����һ��ֵ
		rectangle(srccopy, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
	}

	/// ��ʾ��һ������
	imshow("Source", srccopy);

	waitKey(0);
	return(0);
}

