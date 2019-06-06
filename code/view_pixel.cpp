//#####################
//访问像素 一、指针访问  二、动态地址+at()访问元素
//#####################
#include <iostream>
#include<opencv2\opencv.hpp>   
#include<opencv2\highgui.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat img= imread("Lena.jpg");
	Mat img1 = img.clone();
	//##################一、指针访问###############
	
	//【1】******************多通道访问法1
	int rows = img.rows;
	int cols = img.cols;
	for (int i = 0; i < rows; i++)
	{
		//uchar* p = img1.ptr<uchar>(i);  //获取第i行的首地址
		for (int j = 0; j < cols; j++)
		{
			//在这里操作具体元素
			uchar *p = img1.ptr<uchar>(i, j);
			p[0] = p[0] / 2;//B通道
			p[1] = p[1] / 2;//G通道
			p[2] = p[2] / 2;//R通道
		}
	}
	imshow("指针访问多通道访问法1", img1);

	//【3】********************多通道访问法2
	Mat img2 = img.clone();
	int channels = img2.channels(); //获取通道数
	int rows3 = img2.rows;
	int cols3 = img2.cols* channels; //注意，是列数*通道数
	for (int i = 0; i < rows3; i++)
	{
		uchar* p = img2.ptr<uchar>(i);  //获取第i行的首地址
		for (int j = 0; j < cols3; j+=3)
		{
			//在这里操作具体元素
			p[j] = p[j] / 2;
			p[j + 1] = p[j + 1] / 2;
			p[j + 2] = p[j + 2] / 2;
		}
	}
	imshow("指针访问多通道访问法2", img2);

	//【3】*******************单通道图像
	Mat img3 = img.clone();
	cvtColor(img3, img3, CV_BGR2GRAY);
	imshow("img", img3);
	for (int i = 0; i < img3.rows; i++)
	{
		uchar* p = img3.ptr<uchar>(i);  //获取第i行的首地址
		for (int j = 0; j < img3.cols; j++)
		{
			//在这里操作具体元素
			p[j] = p[j] / 2;
		}
	}
	imshow("指针访问单通道访问法", img3);

	//################ 二、动态地址+at()访问元素################

	/****************【1】访问多通道元素*********************/
	Mat img4 = img.clone();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//在这里访问每个通道的元素,注意，成员函数at(int y,int x)的参数
			img4.at<Vec3b>(i, j)[0] = img4.at<Vec3b>(i, j)[0] / 2;
			img4.at<Vec3b>(i, j)[1] = img4.at<Vec3b>(i, j)[1] / 2;
			img4.at<Vec3b>(i, j)[2] = img4.at<Vec3b>(i, j)[2] / 2;

		}
	}
	imshow("动态地址+at()多通道访问", img4);

	/****************【2】访问单通道元素*********************/
	Mat img5 = img.clone();
	cvtColor(img5, img5, CV_RGB2GRAY);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//在这里访问每个通道的元素,注意，成员函数at(int y,int x)的参数
			img5.at<uchar>(i, j) = img5.at<uchar>(i, j) / 2;
		}
	}
	imshow("动态地址+at()单通道访问", img5);

	waitKey(0);
	return 0;
}
