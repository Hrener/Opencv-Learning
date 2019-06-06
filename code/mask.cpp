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

	//制作掩膜
	//【1】第一步建立与原图一样大小的mask图像，并将所有像素初始化为0，因此全图成了一张全黑色图。
	mask = Mat::zeros(image.size(), CV_8UC1);
	//【2】第二步将mask图中的r1区域的所有像素值设置为255,也就是整个r1区域变成了白色。
	mask(r1).setTo(255);
	imshow("mask", mask);

	//取出ROI,原图(image)与掩膜(mask)进行与运算后得到了结果图（img1）。
	image.copyTo(img1, mask);
	imshow("img1", img1);
	//去除ROI,原始图image拷贝一份给img2，然后img2将mask白色区域设置为0（黑色）
	image.copyTo(img2);
	img2.setTo(0, mask);
	imshow("img2", img2);

	waitKey(0);
	return 0;
}
