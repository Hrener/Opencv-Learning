#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("ruiwen.jpg");
	imshow("原始图", img);

	Mat boxout,blurout,gaussout,medianout,biout,out;
	boxFilter(img, boxout, -1, Size(5, 5));//-1指原图深度
	blur(img, blurout, Size(5, 5));//-1指原图深度
	GaussianBlur(img, gaussout, Size(3, 3), 0, 0);
	medianBlur(img, medianout, 7);//第三个参数表示孔径的线性尺寸，它的值必须是大于1的奇数
	bilateralFilter(img, biout, 25, 25 * 2, 25 / 2);

	imshow("方框滤波", boxout);
	imshow("均值滤波", blurout);
	imshow("高斯滤波", gaussout);
	imshow("中值滤波", medianout);
	imshow("双边滤波", biout);

	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的

	//高级形态学处理，调用这个函数就可以了，具体要选择哪种操作，就修改第三个参数就可以了。这里演示的是形态学梯度处理
	//morphologyEx(img, out, MORPH_TOPHAT, element);
	morphologyEx(img, out, MORPH_BLACKHAT, element);
	imshow("顶帽", out);
	waitKey(0);

}