//#####################
//如果某一点在任意方向的一个微小的变动都会引起灰度很大的变化，那么我们就可以把该点看做是角点。
//cornerHarris(InputArray src, OutputArray dst, int blockSize, int ksize,double k, int borderType = BORDER_DEFAULT);
//#####################
#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;

void on_CornerHarris(int, void*);
int thresh = 0; //当前阈值  
int max_thresh = 175; //最大阈值  
Mat imgcopy, imggray;
Mat img = imread("vn.jpg");

RNG rng(12345);//构造方法设定一个具体值，表示下面代码每次生成的结果都是一样的

int main()
{
	
	imgcopy = img.clone();
	cvtColor(img, imggray, CV_BGR2GRAY);
	//imshow("原始图", img);

	namedWindow("角点检测");
	createTrackbar("阈值: ", "角点检测", &thresh, max_thresh, on_CornerHarris);
	on_CornerHarris(thresh, 0);

	waitKey(0);
	return 0;
}
void on_CornerHarris(int, void*)
{
	Mat dstImage;//目标图  
	Mat normImage;//归一化后的图  
	Mat scaledImage;//线性变换后的八位无符号整型的图  

	//置零当前需要显示的两幅图，即清除上一次调用此函数时他们的值  
	dstImage = Mat::zeros(img.size(), CV_32FC1);
	imgcopy = img.clone();

	//进行角点检测  
	//第三个参数表示邻域大小，第四个参数表示Sobel算子孔径大小，第五个参数表示Harris参数
	cornerHarris(imggray, dstImage, 2, 3, 0.04, BORDER_DEFAULT);

	// 归一化与转换  
	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(normImage, scaledImage);//将归一化后的图线性变换成8位无符号整型   
	
	// 将检测到的，且符合阈值条件的角点绘制出来  
	
	for (int j = 0; j < normImage.rows; j++)
	{
		for (int i = 0; i < normImage.cols; i++)
		{
			//Mat::at<float>(j,i)获取像素值，并与阈值比较
			if ((int)normImage.at<float>(j, i) > thresh + 100)
			{
				Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));//从[0,255)范围内随机一个值
				circle(imgcopy, Point(i, j), 3, color, -1, 8, 0);
				circle(scaledImage, Point(i, j), 3, color, -1, 8, 0);
			}
		}
	}

	imshow("角点检测", imgcopy);
	imshow("角点检测2", scaledImage);
}
