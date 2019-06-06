//#####################
//��ӳ��
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
	dstImage.create(srcImage.size(), srcImage.type());//������ԭͼһ����Ч��ͼ
	//map_x��������ر�ʾ�е�jֵ(��)��map_y��������ر�ʾ�е�iֵ(��).
	map_x.create(srcImage.size(), CV_32FC1);
	map_y.create(srcImage.size(), CV_32FC1);
	imshow("ԭͼ", srcImage);
	//����ÿһ�����ص㣬�ı�map_x & map_y��ֵ,ʵ�ַ�ת180��
	for (int i = 0; i < srcImage.rows; i++)
	{
		for (int j = 0; j < srcImage.cols; j++)//rows��ʾͼ��ĸ�(��)��clos��ʾͼ��Ŀ��У�
		{
			//-----���±任----ʹ�������������ֵ���䣬������Ӵ�С���У�ԭͼ���������Ǵ�С�������еģ�
			//map_x.at<float>(i, j) = static_cast<float>(j);
			//map_y.at<float>(i, j) = static_cast<float>(srcImage.rows - i);
			//-----���ұ任----ʹ����ĺ�������ֵ���䣬������Ӵ�С���У�ԭͼ�к������Ǵ�С�������еģ�
			map_y.at<float>(i, j) =static_cast<float>(i);//x����ŵ�
			map_x.at<float>(i, j) =static_cast<float>(srcImage.cols-j);//y�����ŵ�
		}
	}

	//������ӳ�����
	remap(srcImage, dstImage, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
	imshow("��ӳ��Ч��ͼ", dstImage);
	waitKey(0);
	return 0;
}
