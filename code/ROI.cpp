#include <iostream>
#include<opencv2\opencv.hpp>   
#include<opencv2\highgui.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("xiaopao.jpg");
	//��1��
	//imshow("xiaopao", srcImage(Rect(0, 0, 200, 300)));//200��������300������
	//��2��
	Mat ROI(srcImage.rows, srcImage.cols, CV_8UC3);
	srcImage(Rect(0, 0, 200, 300)).copyTo(ROI);
	imshow("xiaopao", ROI);
	
	imshow("ԭͼ",srcImage);
	waitKey(0);
	return 0;
}