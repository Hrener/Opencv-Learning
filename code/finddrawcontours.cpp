//#####################
//������
//#####################
#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;

int main()
{
	Mat srcimg = imread("xiaopao.jpg");	
	Mat imggray;
	cvtColor(srcimg, imggray, CV_RGB2GRAY);
	// ����Ӧ��ֵ��ֵ��
	int blockSize = 51;		//������С
	int constValue = 17;	//����C,����C��ʾ���㷨�йصĲ���������һ���Ӿ�ֵ���Ȩ��ֵ��ȡ�ĳ����������Ǹ���
	adaptiveThreshold(imggray, imggray, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, blockSize, constValue);

	//Mat element = getStructuringElement(MORPH_RECT, Size(20,20));
	//dilate(imggray, imggray, element);
	//erode(imggray, imggray, element);
	morphologyEx(imggray, imggray, MORPH_CLOSE, Mat());//��̬ѧ������ȥ���
	
	imshow("��ֵ��",imggray);

	vector<vector<Point> > contours;
	findContours(imggray, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //������
	vector<vector<Point>> contours1;
	for (int i = 0; i < contours.size(); ++i)
	{
		contours1.push_back(contours[i]);
	}

	Mat hole(imggray.size(), CV_8U, Scalar(0)); //����ͼ��
	drawContours(hole, contours1, -1, Scalar(255), CV_FILLED); //������ͼ���ϣ��ð�ɫ��������������õ�MASK
	imshow("My hole", hole);
	Mat crop(srcimg.rows, srcimg.cols, CV_8UC3);
	srcimg.copyTo(crop, imggray);//��ԭͼ�񿽱�������ͼ��
	imshow("My warpPerspective", crop);
	waitKey(0);
	return 0;
}
