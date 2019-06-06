#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("ruiwen.jpg");
	Mat grayImage,edge;
	cvtColor(img, grayImage, COLOR_BGR2GRAY);
	imshow("ԭʼͼ", grayImage);
	//��ʹ��3*3�ں�������
	blur(grayImage, grayImage, Size(3, 3));

	//����canny����
	Canny(grayImage, edge, 50, 100, 3);
	imshow("��Ե��ȡЧ��", edge);

	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;
	//��x�����ݶ�
	Sobel(grayImage, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("x����soble", abs_grad_x);
	//��y�����ݶ�
	Sobel(grayImage, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("y��soble", abs_grad_y);
	//�ϲ��ݶ�
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	imshow("���巽��soble", dst);

	Mat dstLap, abs_dst;
	Laplacian(grayImage, dstLap, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	//�������ֵ���������תΪ8λ
	convertScaleAbs(dstLap, abs_dst);
	imshow("laplaceЧ��ͼ", abs_dst);
	waitKey(0);
	return 0;
}
