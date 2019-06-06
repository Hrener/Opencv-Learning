//#####################
//画轮廓
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
	// 自适应阈值二值化
	int blockSize = 51;		//邻域块大小
	int constValue = 17;	//常数C,参数C表示与算法有关的参数，它是一个从均值或加权均值提取的常数，可以是负数
	adaptiveThreshold(imggray, imggray, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, blockSize, constValue);

	//Mat element = getStructuringElement(MORPH_RECT, Size(20,20));
	//dilate(imggray, imggray, element);
	//erode(imggray, imggray, element);
	morphologyEx(imggray, imggray, MORPH_CLOSE, Mat());//形态学开运算去噪点
	
	imshow("二值化",imggray);

	vector<vector<Point> > contours;
	findContours(imggray, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //找轮廓
	vector<vector<Point>> contours1;
	for (int i = 0; i < contours.size(); ++i)
	{
		contours1.push_back(contours[i]);
	}

	Mat hole(imggray.size(), CV_8U, Scalar(0)); //遮罩图层
	drawContours(hole, contours1, -1, Scalar(255), CV_FILLED); //在遮罩图层上，用白色像素填充轮廓，得到MASK
	imshow("My hole", hole);
	Mat crop(srcimg.rows, srcimg.cols, CV_8UC3);
	srcimg.copyTo(crop, imggray);//将原图像拷贝进遮罩图层
	imshow("My warpPerspective", crop);
	waitKey(0);
	return 0;
}
