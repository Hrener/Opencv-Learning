//#####################
//�������� һ��ָ�����  ������̬��ַ+at()����Ԫ��
//#####################
#include <iostream>
#include<opencv2\opencv.hpp>   
#include<opencv2\highgui.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat img= imread("Lena.jpg");
	Mat img1 = img.clone();
	//##################һ��ָ�����###############
	
	//��1��******************��ͨ�����ʷ�1
	int rows = img.rows;
	int cols = img.cols;
	for (int i = 0; i < rows; i++)
	{
		//uchar* p = img1.ptr<uchar>(i);  //��ȡ��i�е��׵�ַ
		for (int j = 0; j < cols; j++)
		{
			//�������������Ԫ��
			uchar *p = img1.ptr<uchar>(i, j);
			p[0] = p[0] / 2;//Bͨ��
			p[1] = p[1] / 2;//Gͨ��
			p[2] = p[2] / 2;//Rͨ��
		}
	}
	imshow("ָ����ʶ�ͨ�����ʷ�1", img1);

	//��3��********************��ͨ�����ʷ�2
	Mat img2 = img.clone();
	int channels = img2.channels(); //��ȡͨ����
	int rows3 = img2.rows;
	int cols3 = img2.cols* channels; //ע�⣬������*ͨ����
	for (int i = 0; i < rows3; i++)
	{
		uchar* p = img2.ptr<uchar>(i);  //��ȡ��i�е��׵�ַ
		for (int j = 0; j < cols3; j+=3)
		{
			//�������������Ԫ��
			p[j] = p[j] / 2;
			p[j + 1] = p[j + 1] / 2;
			p[j + 2] = p[j + 2] / 2;
		}
	}
	imshow("ָ����ʶ�ͨ�����ʷ�2", img2);

	//��3��*******************��ͨ��ͼ��
	Mat img3 = img.clone();
	cvtColor(img3, img3, CV_BGR2GRAY);
	imshow("img", img3);
	for (int i = 0; i < img3.rows; i++)
	{
		uchar* p = img3.ptr<uchar>(i);  //��ȡ��i�е��׵�ַ
		for (int j = 0; j < img3.cols; j++)
		{
			//�������������Ԫ��
			p[j] = p[j] / 2;
		}
	}
	imshow("ָ����ʵ�ͨ�����ʷ�", img3);

	//################ ������̬��ַ+at()����Ԫ��################

	/****************��1�����ʶ�ͨ��Ԫ��*********************/
	Mat img4 = img.clone();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//���������ÿ��ͨ����Ԫ��,ע�⣬��Ա����at(int y,int x)�Ĳ���
			img4.at<Vec3b>(i, j)[0] = img4.at<Vec3b>(i, j)[0] / 2;
			img4.at<Vec3b>(i, j)[1] = img4.at<Vec3b>(i, j)[1] / 2;
			img4.at<Vec3b>(i, j)[2] = img4.at<Vec3b>(i, j)[2] / 2;

		}
	}
	imshow("��̬��ַ+at()��ͨ������", img4);

	/****************��2�����ʵ�ͨ��Ԫ��*********************/
	Mat img5 = img.clone();
	cvtColor(img5, img5, CV_RGB2GRAY);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//���������ÿ��ͨ����Ԫ��,ע�⣬��Ա����at(int y,int x)�Ĳ���
			img5.at<uchar>(i, j) = img5.at<uchar>(i, j) / 2;
		}
	}
	imshow("��̬��ַ+at()��ͨ������", img5);

	waitKey(0);
	return 0;
}
