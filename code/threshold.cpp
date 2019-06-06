#include <iostream>
#include<opencv2\opencv.hpp>   
#include<opencv2\highgui.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage;
	Mat global;
	Mat local1,local2;
	srcImage = imread("Lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);


	// ȫ����ֵ��ֵ��
	int th = 100;
	threshold(srcImage, global, th, 255, CV_THRESH_BINARY_INV);
	// ����Ӧ��ֵ��ֵ��
	int blockSize = 3;		//������С
	int constValue = -5;	//����C,����C��ʾ���㷨�йصĲ���������һ���Ӿ�ֵ���Ȩ��ֵ��ȡ�ĳ����������Ǹ���
	adaptiveThreshold(srcImage, local1, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, blockSize, constValue);
	adaptiveThreshold(srcImage, local2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, blockSize, constValue);
	
	imshow("ԭͼ����", srcImage);
	imshow("ȫ����ֵ��ֵ������", global);
	imshow("����Ӧ��ֵ��ֵ������1", local1);
	imshow("����Ӧ��ֵ��ֵ������2", local2);
	

	waitKey(0);
	return 0;
}