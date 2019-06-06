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


	// 全局阈值二值化
	int th = 100;
	threshold(srcImage, global, th, 255, CV_THRESH_BINARY_INV);
	// 自适应阈值二值化
	int blockSize = 3;		//邻域块大小
	int constValue = -5;	//常数C,参数C表示与算法有关的参数，它是一个从均值或加权均值提取的常数，可以是负数
	adaptiveThreshold(srcImage, local1, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, blockSize, constValue);
	adaptiveThreshold(srcImage, local2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, blockSize, constValue);
	
	imshow("原图窗口", srcImage);
	imshow("全局阈值二值化窗口", global);
	imshow("自适应阈值二值化窗口1", local1);
	imshow("自适应阈值二值化窗口2", local2);
	

	waitKey(0);
	return 0;
}