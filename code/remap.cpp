//#####################
//重映射
//#####################
#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;

int main()
{

	Mat srcImage = imread("Lena.jpg");
	Mat dstImage, map_x, map_y;
	dstImage.create(srcImage.size(), srcImage.type());//创建和原图一样的效果图
	//map_x存的是像素表示中的j值(列)，map_y存的是像素表示中的i值(行).
	map_x.create(srcImage.size(), CV_32FC1);
	map_y.create(srcImage.size(), CV_32FC1);
	imshow("原图", srcImage);
	//遍历每一个像素点，改变map_x & map_y的值,实现翻转180度
	for (int i = 0; i < srcImage.rows; i++)
	{
		for (int j = 0; j < srcImage.cols; j++)//rows表示图像的高(行)，clos表示图像的宽（列）
		{
			//-----上下变换----使坐标的纵坐标数值不变，横坐标从大到小排列（原图中纵坐标是从小到大排列的）
			//map_x.at<float>(i, j) = static_cast<float>(j);
			//map_y.at<float>(i, j) = static_cast<float>(srcImage.rows - i);
			//-----左右变换----使坐标的横坐标数值不变，纵坐标从大到小排列（原图中横坐标是从小到大排列的）
			map_y.at<float>(i, j) =static_cast<float>(i);//x轴横着的
			map_x.at<float>(i, j) =static_cast<float>(srcImage.cols-j);//y轴竖着的
		}
	}

	//进行重映射操作
	remap(srcImage, dstImage, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
	imshow("重映射效果图", dstImage);
	waitKey(0);
	return 0;
}
