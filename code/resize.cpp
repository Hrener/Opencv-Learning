#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("ruiwen.jpg");
	imshow("原始图", img);

	//Mat dst = Mat::zeros(512, 512, CV_8UC3); //我要转化为512*512大小的
	Mat dst, dst1;
	resize(img, dst, Size(),0.5,0.5, INTER_AREA);
	resize(img, dst1, Size(), 1.5, 1.5, INTER_LINEAR);
	imshow("resize缩小", dst);
	imshow("resize放大", dst1);

	Mat dst2, dst3;
	pyrDown(img, dst2, Size(img.cols * 0.5, img.rows * 0.5)); //缩小为原来的一半
	pyrUp(img, dst3, Size(img.cols * 2, img.rows * 2)); //放大一倍,只能是整数倍
	imshow("pyrDown缩小", dst2);
	imshow("pyrUp放大", dst3);
	waitKey(0);
	return 0;
}
