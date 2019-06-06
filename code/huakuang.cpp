//#####################
//画框
//#####################
#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;

Mat src; Mat src_gray;
RNG rng(12345);//构造方法设定一个具体值，表示下面代码每次生成的结果都是一样的

int main(int argc, char** argv)
{
	/// 载入原图像, 返回3通道图像
	src = imread("draw.png", 1);
	imshow("Source", src);
	/// 转化成灰度图像并进行平滑
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	Mat threshold_output;
	vector<vector<Point> > contours;

	/// 使用Threshold检测边缘
	threshold(src_gray, threshold_output, 100, 255, THRESH_BINARY);
	/// 找到轮廓
	findContours(threshold_output, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// 多边形逼近轮廓 + 获取矩形和圆形边界框
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
	}

	/// 画多边形轮廓 + 包围的矩形框 + 圆形框
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	Mat srccopy = src.clone();
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));//从[0,255)范围内随机一个值
		rectangle(srccopy, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
	}

	/// 显示在一个窗口
	imshow("Source", srccopy);

	waitKey(0);
	return(0);
}

