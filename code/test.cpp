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

	/*namedWindow("ԭͼ����");
	namedWindow("�Ҷ�ͼ����");
	cvtColor(srcImage, dstImage, CV_BGR2GRAY);
	GaussianBlur(img1, dstImage, Size(9, 9), 1);   //x����ı�׼��ѡΪ1 
	imshow("ԭͼ����", img1);
	imshow("�Ҷ�ͼ����", dstImage);*/

	//��Щ��ʽ�����Լ�ӵ�ж������ڴ�ռ�
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

	//���涼��ǳ������ָ��ָ��ͬһ��ʵ��
	Mat img9 = img8;
	Mat img10(img8);

	waitKey(0);
	return 0;
}
