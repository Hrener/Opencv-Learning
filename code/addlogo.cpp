//################
//���Ե��ӣ�ʹ��addWeigthed������copyTo����,��ͼ���logo
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
	resize(logo, logo, Size(), 0.2, 0.2, INTER_AREA);//logo̫����Ҫ��С

	//��ԭͼ�пٳ���������Rect��һ��������ʾ�������ϽǶ��������(�У���)��������������ʾ���еĿ�͸�(�У���)
	//ע����ǳcopy,ָ��ͬһ��ʵ������ROI�������Ƕ�ԭͼ��Ӧλ�ò���
	Mat imageROI = srcImage(Rect(20,20, logo.cols, logo.rows));
	Mat imageroi = srcImage(Rect(20, 150, logo.cols, logo.rows));
	//dst = src1[I]*alpha+ src2[I]*beta + gamma����һ���ĸ��������Ǹ���Ȩ�أ���5���������ǹ�ʽ�е�ƫִ����gamma��
	addWeighted(imageROI, 0.1, logo, 0.9, 0., imageROI);
	logo.copyTo(imageroi);
	imshow("ԭͼ+logo", srcImage);
	waitKey(0);
	return 0;
}