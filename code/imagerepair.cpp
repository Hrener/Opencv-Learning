//#####################
//ͼ���޸�
//#####################
#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;

//int main()
//{
//	Mat img, imggray;
//	img = imread("xiufu1.jpg");
//	imshow("ԭͼ", img);
//	cvtColor(img, imggray, CV_RGB2GRAY);
//
//	Mat imgMask = Mat(img.size(), CV_8UC1, Scalar::all(0));
//	//ͨ����ֵ��������Mask
//	threshold(imggray, imgMask, 240, 255, CV_THRESH_BINARY);
//	Mat Kernel = getStructuringElement(MORPH_RECT, Size(3,3));
//	//��Mask���ʹ�������Mask���
//	dilate(imgMask, imgMask, Kernel);
//	//erode(imgMask, imgMask, Kernel);
//	
//	
//	//ͼ���޸�
//	inpaint(img, imgMask, img,5, INPAINT_TELEA);
//	imshow("��������Mask", imgMask);
//	imshow("�޸���", img);
//	waitKey(0);
//	return 0;
//}

Point ptL, ptR; //��껭�����ο�������յ�
Mat imageSource, imageSourceCopy;
Mat ROI; //ԭͼ��Ҫ�޸������ROI

		 //���ص�����
void OnMouse(int event, int x, int y, int flag, void *ustg);

//���Ȧ��������ֵ����+Mask���ʹ���
int main()
{
	imageSource = imread("xiufu.jpg");
	imshow("ԭͼ", imageSource);
	setMouseCallback("ԭͼ", OnMouse);
	waitKey();
}
void OnMouse(int event, int x, int y, int flag, void *ustg)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		ptL = Point(x, y);
		ptR = Point(x, y);
	}
	if (flag == CV_EVENT_FLAG_LBUTTON)
	{
		ptR = Point(x, y);
		imageSourceCopy = imageSource.clone();
		rectangle(imageSourceCopy, ptL, ptR, Scalar(255, 0, 0));
		imshow("ԭͼ", imageSourceCopy);
	}
	if (event == CV_EVENT_LBUTTONUP)
	{
		if (ptL != ptR)
		{
			ROI = imageSource(Rect(ptL, ptR));
			//imshow("ROI", ROI);
			waitKey();
		}
	}
	//��������Ҽ���ʼͼ���޸�
	if (event == CV_EVENT_RBUTTONDOWN)
	{
		imageSourceCopy = ROI.clone();
		Mat imageGray;
		cvtColor(ROI, imageGray, CV_RGB2GRAY); //ת��Ϊ�Ҷ�ͼ
		Mat imageMask = Mat(ROI.size(), CV_8UC1, Scalar::all(0));

		//ͨ����ֵ��������Mask
		threshold(imageGray, imageMask, 180, 255, CV_THRESH_BINARY);
		Mat Kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(imageMask, imageMask, Kernel);  //��Mask���ʹ���
		inpaint(ROI, imageMask, ROI, 5, INPAINT_TELEA);  //ͼ���޸�,���ĸ��������޸��뾶
		//imshow("Mask", imageMask);
		//imshow("�޸���", imageSource);
		imshow("ԭͼ", imageSource);
	}
}