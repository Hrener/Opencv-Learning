//#####################
//@ͼ�����
//����������ȡ�Ľ����㷨,�����������Եı߽�������ͼ
//1��ͼƬ�ҶȻ�
//2����ֵ��ֵ��
//3���������
//4��Ѱ�������İ�Χ���󣬲��һ�ȡ�Ƕ�
//5�����ݽǶȽ�����ת����
//6������ת���ͼ�����������ȡ
//7���������ڵ�ͼ������ٳ�������Ϊһ�Ŷ���ͼ��
//#####################
#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("jiaozhengtu.jpg");
	imshow("src", src);
	Mat gray,binimg;
	cvtColor(src, gray, CV_RGB2GRAY);
	

	threshold(gray, binimg, 100, 255, CV_THRESH_BINARY);
	//imshow("bin", binimg);
	vector<vector<Point> > contours;
	vector<Rect> boundRect(contours.size());
	//ע���5������ΪCV_RETR_EXTERNAL��ֻ�������  
	findContours(binimg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //������
	cout << contours.size() << endl;

	CvBox2D rect;
	for (int i = 0; i < contours.size(); i++)
	{
		 rect = minAreaRect(Mat(contours[i]));//minAreaRect�ҵ�������С��Ӿ���
		
	}
	CvPoint2D32f rectpoint[4];
	cvBoxPoints(rect, rectpoint); //��ȡ��С��Ӿ���4���������� �����涥���˳�����Ϊ�����Ĳ�ͬ����ͬ


	//��ˮƽ�ߵĽǶ�  
	float angle = rect.angle;
	cout << angle << endl;

	int line1 = sqrt((rectpoint[1].y - rectpoint[0].y)*(rectpoint[1].y - rectpoint[0].y) + (rectpoint[1].x - rectpoint[0].x)*(rectpoint[1].x - rectpoint[0].x));
	int line2 = sqrt((rectpoint[3].y - rectpoint[0].y)*(rectpoint[3].y - rectpoint[0].y) + (rectpoint[3].x - rectpoint[0].x)*(rectpoint[3].x - rectpoint[0].x));
	//rectangle(binImg, rectpoint[0], rectpoint[3], Scalar(255), 2);
	//���̫С��ֱ��pass
	/*if (line1 * line2 < 600)
	{
		continue;
	}*/
	////Ϊ���������κ��ŷţ�������ת�Ƕ��ǲ�һ���ġ����ŵģ�������90�ȣ�������  
	if (line1 > line2)
	{
		angle = 90 + angle;
	}



	//�½�һ������Ȥ������ͼ����С��ԭͼһ����  
	Mat RoiSrcImg(src.rows, src.cols, CV_8UC3); //ע���������ѡCV_8UC3
	RoiSrcImg.setTo(0); //��ɫ������Ϊ��ɫ  
	//imshow("�½���ROI", RoiSrcImg);
	//�Եõ����������һ��  
	drawContours(binimg, contours, -1, Scalar(255), CV_FILLED);
	//imshow("binimg", binimg);
	//��ͼ��RoiSrcImg
	src.copyTo(RoiSrcImg, binimg);
	//imshow("RoiSrcImg", RoiSrcImg);



	//����һ����ת���ͼ��  
	Mat RatationedImg(RoiSrcImg.rows, RoiSrcImg.cols, CV_8UC1);
	RatationedImg.setTo(0);
	//��RoiSrcImg������ת  
	Point2f center = rect.center;  //���ĵ�  
	Mat M2 = getRotationMatrix2D(center, angle, 1);//������ת�����ŵı任���� 
	warpAffine(RoiSrcImg, RatationedImg, M2, RoiSrcImg.size(), 1, 0, Scalar(0));//����任 
	//imshow("��ת֮��", RatationedImg);
	//imwrite("afterjiaozheng.jpg", RatationedImg); //���������ͼƬ��������



	//��ROI������п�ͼ
	//����ת���ͼƬ����������ȡ  
	vector<vector<Point> > contours2;
	Mat SecondFindImg;
	cvtColor(RatationedImg, SecondFindImg, COLOR_BGR2GRAY);  //�ҶȻ�  
	threshold(SecondFindImg, SecondFindImg, 80, 200, CV_THRESH_BINARY);
	findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//cout << "sec contour:" << contours2.size() << endl;

	for (int j = 0; j < contours2.size(); j++)
	{
		//��ʱ����ʵ����һ���������ˣ����Ի�ȡrect  
		Rect rect = boundingRect(Mat(contours2[j]));
		//���̫С������ֱ��pass,ͨ�����ù��������С�����Ա�ֻ֤�õ����
		if (rect.area() < 600)
		{
			continue;
		}
		Mat dstImg = RatationedImg(rect);
		imshow("dst", dstImg);
		//imwrite("jiaozhengROI.jpg", dstImg);

	}
#if 0
		//��ROI������п�ͼ

		//����ת���ͼƬ����������ȡ  
		vector<vector<Point> > contours2;
		Mat raw = imread("afterjiaozheng.jpg");
		Mat SecondFindImg;
		//SecondFindImg.setTo(0);
		cvtColor(raw, SecondFindImg, COLOR_BGR2GRAY);  //�ҶȻ�  
		threshold(SecondFindImg, SecondFindImg, 80, 200, CV_THRESH_BINARY);
		findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		//cout << "sec contour:" << contours2.size() << endl;

		for (int j = 0; j < contours2.size(); j++)
		{
			//��ʱ����ʵ����һ���������ˣ����Ի�ȡrect  
			Rect rect = boundingRect(Mat(contours2[j]));
			//���̫С������ֱ��pass,ͨ�����ù��������С�����Ա�ֻ֤�õ����
			if (rect.area() < 600)
			{
				continue;
			}
			Mat dstImg = raw(rect);
			imshow("dst", dstImg);
			imwrite("jiaozhengROI.jpg", dstImg);
		}
#endif
	waitKey(0);
	return 0;
}
