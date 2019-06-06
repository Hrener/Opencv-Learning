#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("ruiwen.jpg");
	imshow("ԭʼͼ", img);

	//Mat dst = Mat::zeros(512, 512, CV_8UC3); //��Ҫת��Ϊ512*512��С��
	Mat dst, dst1;
	resize(img, dst, Size(),0.5,0.5, INTER_AREA);
	resize(img, dst1, Size(), 1.5, 1.5, INTER_LINEAR);
	imshow("resize��С", dst);
	imshow("resize�Ŵ�", dst1);

	Mat dst2, dst3;
	pyrDown(img, dst2, Size(img.cols * 0.5, img.rows * 0.5)); //��СΪԭ����һ��
	pyrUp(img, dst3, Size(img.cols * 2, img.rows * 2)); //�Ŵ�һ��,ֻ����������
	imshow("pyrDown��С", dst2);
	imshow("pyrUp�Ŵ�", dst3);
	waitKey(0);
	return 0;
}
