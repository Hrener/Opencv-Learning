//#####################
//���ĳһ�������ⷽ���һ��΢С�ı䶯��������ҶȺܴ�ı仯����ô���ǾͿ��԰Ѹõ㿴���ǽǵ㡣
//cornerHarris(InputArray src, OutputArray dst, int blockSize, int ksize,double k, int borderType = BORDER_DEFAULT);
//#####################
#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;

void on_CornerHarris(int, void*);
int thresh = 0; //��ǰ��ֵ  
int max_thresh = 175; //�����ֵ  
Mat imgcopy, imggray;
Mat img = imread("vn.jpg");

RNG rng(12345);//���췽���趨һ������ֵ����ʾ�������ÿ�����ɵĽ������һ����

int main()
{
	
	imgcopy = img.clone();
	cvtColor(img, imggray, CV_BGR2GRAY);
	//imshow("ԭʼͼ", img);

	namedWindow("�ǵ���");
	createTrackbar("��ֵ: ", "�ǵ���", &thresh, max_thresh, on_CornerHarris);
	on_CornerHarris(thresh, 0);

	waitKey(0);
	return 0;
}
void on_CornerHarris(int, void*)
{
	Mat dstImage;//Ŀ��ͼ  
	Mat normImage;//��һ�����ͼ  
	Mat scaledImage;//���Ա任��İ�λ�޷������͵�ͼ  

	//���㵱ǰ��Ҫ��ʾ������ͼ���������һ�ε��ô˺���ʱ���ǵ�ֵ  
	dstImage = Mat::zeros(img.size(), CV_32FC1);
	imgcopy = img.clone();

	//���нǵ���  
	//������������ʾ�����С�����ĸ�������ʾSobel���ӿ׾���С�������������ʾHarris����
	cornerHarris(imggray, dstImage, 2, 3, 0.04, BORDER_DEFAULT);

	// ��һ����ת��  
	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(normImage, scaledImage);//����һ�����ͼ���Ա任��8λ�޷�������   
	
	// ����⵽�ģ��ҷ�����ֵ�����Ľǵ���Ƴ���  
	
	for (int j = 0; j < normImage.rows; j++)
	{
		for (int i = 0; i < normImage.cols; i++)
		{
			//Mat::at<float>(j,i)��ȡ����ֵ��������ֵ�Ƚ�
			if ((int)normImage.at<float>(j, i) > thresh + 100)
			{
				Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));//��[0,255)��Χ�����һ��ֵ
				circle(imgcopy, Point(i, j), 3, color, -1, 8, 0);
				circle(scaledImage, Point(i, j), 3, color, -1, 8, 0);
			}
		}
	}

	imshow("�ǵ���", imgcopy);
	imshow("�ǵ���2", scaledImage);
}
