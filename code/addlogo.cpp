//################
//线性叠加，使用addWeigthed函数和copyTo函数,给图像加logo
//################
#include <iostream>
#include<opencv2\opencv.hpp>   
#include<opencv2\highgui.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("vn.jpg");
	Mat logo = imread("dota.jpg");
	resize(logo, logo, Size(), 0.2, 0.2, INTER_AREA);//logo太大需要缩小

	//从原图中抠出矩形区域，Rect第一二参数表示矩形左上角定点的坐标(列，行)，后两个参数表示举行的宽和高(列，行)
	//注意是浅copy,指向同一个实例，对ROI操作即是对原图对应位置操作
	Mat imageROI = srcImage(Rect(20,20, logo.cols, logo.rows));
	Mat imageroi = srcImage(Rect(20, 150, logo.cols, logo.rows));
	//dst = src1[I]*alpha+ src2[I]*beta + gamma；第一第四个参数就是各自权重，第5个参数就是公式中的偏执因子gamma。
	addWeighted(imageROI, 0.1, logo, 0.9, 0., imageROI);
	logo.copyTo(imageroi);
	imshow("原图+logo", srcImage);
	waitKey(0);
	return 0;
}