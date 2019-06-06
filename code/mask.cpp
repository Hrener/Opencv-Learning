#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;

int main()
{
	Mat image, mask;
	Rect r1(380, 30, 100, 80);//ROI
	Mat img1, img2;
	image = imread("vn.jpg");

	//������Ĥ
	//��1����һ��������ԭͼһ����С��maskͼ�񣬲����������س�ʼ��Ϊ0�����ȫͼ����һ��ȫ��ɫͼ��
	mask = Mat::zeros(image.size(), CV_8UC1);
	//��2���ڶ�����maskͼ�е�r1�������������ֵ����Ϊ255,Ҳ��������r1�������˰�ɫ��
	mask(r1).setTo(255);
	imshow("mask", mask);

	//ȡ��ROI,ԭͼ(image)����Ĥ(mask)�����������õ��˽��ͼ��img1����
	image.copyTo(img1, mask);
	imshow("img1", img1);
	//ȥ��ROI,ԭʼͼimage����һ�ݸ�img2��Ȼ��img2��mask��ɫ��������Ϊ0����ɫ��
	image.copyTo(img2);
	img2.setTo(0, mask);
	imshow("img2", img2);

	waitKey(0);
	return 0;
}
