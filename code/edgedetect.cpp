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
	imshow("原始图", grayImage);
	//先使用3*3内核来降噪
	blur(grayImage, grayImage, Size(3, 3));

	//运行canny算子
	Canny(grayImage, edge, 50, 100, 3);
	imshow("边缘提取效果", edge);

	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;
	//求x方向梯度
	Sobel(grayImage, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("x方向soble", abs_grad_x);
	//求y方向梯度
	Sobel(grayImage, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("y向soble", abs_grad_y);
	//合并梯度
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	imshow("整体方向soble", dst);

	Mat dstLap, abs_dst;
	Laplacian(grayImage, dstLap, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	//计算绝对值，并将结果转为8位
	convertScaleAbs(dstLap, abs_dst);
	imshow("laplace效果图", abs_dst);
	waitKey(0);
	return 0;
}
