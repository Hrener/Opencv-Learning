#include <iostream>
#include<opencv2\opencv.hpp>   
#include<opencv2\highgui.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage;
	Mat dstImage;
	srcImage = imread("Lena.jpg");

	/*namedWindow("原图窗口");
	namedWindow("灰度图窗口");
	cvtColor(srcImage, dstImage, CV_BGR2GRAY);
	GaussianBlur(img1, dstImage, Size(9, 9), 1);   //x方向的标准差选为1 
	imshow("原图窗口", img1);
	imshow("灰度图窗口", dstImage);*/

	//这些方式都是自己拥有独立的内存空间
	Mat img1(2, 2, CV_8UC3, Scalar(0, 0, 255));
	cout << img1 << endl;

	Mat img2;
	img2.create(4, 4, CV_8UC3);
	cout << "img2:\n"<<img2 << endl;

	Mat img6 = Mat::zeros(4, 4, CV_8UC3);
	cout << "img6:\n" << img6 << endl;

	Mat img7 = img6.clone();
	cout << "img7:\n" << img7 << endl;

	Mat img8;
	img6.copyTo(img8);
	cout << "img8:\n" << img8 << endl;

	//下面都是浅拷贝，指针指向同一个实例
	Mat img9 = img8;
	Mat img10(img8);

	waitKey(0);
	return 0;
}
