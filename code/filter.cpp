#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("ruiwen.jpg");
	imshow("ԭʼͼ", img);

	Mat boxout,blurout,gaussout,medianout,biout,out;
	boxFilter(img, boxout, -1, Size(5, 5));//-1ָԭͼ���
	blur(img, blurout, Size(5, 5));//-1ָԭͼ���
	GaussianBlur(img, gaussout, Size(3, 3), 0, 0);
	medianBlur(img, medianout, 7);//������������ʾ�׾������Գߴ磬����ֵ�����Ǵ���1������
	bilateralFilter(img, biout, 25, 25 * 2, 25 / 2);

	imshow("�����˲�", boxout);
	imshow("��ֵ�˲�", blurout);
	imshow("��˹�˲�", gaussout);
	imshow("��ֵ�˲�", medianout);
	imshow("˫���˲�", biout);

	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�

	//�߼���̬ѧ����������������Ϳ����ˣ�����Ҫѡ�����ֲ��������޸ĵ����������Ϳ����ˡ�������ʾ������̬ѧ�ݶȴ���
	//morphologyEx(img, out, MORPH_TOPHAT, element);
	morphologyEx(img, out, MORPH_BLACKHAT, element);
	imshow("��ñ", out);
	waitKey(0);

}