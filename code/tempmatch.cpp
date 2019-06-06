//#####################
//ģ��ƥ��
//#####################
#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;

int main()
{
	Mat img, imgcopy,templ, result;
	img = imread("xiaopao1.jpg");
	img.copyTo(imgcopy);
	templ = imread("xiaopaotemp.jpg");

	int matchnum = 0;
	int result_cols = img.cols - templ.cols + 1;
	int result_rows = img.rows - templ.rows + 1;
	result.create(result_cols, result_rows, CV_32FC1);
	while(1)
	{
		matchnum++;
		matchTemplate(imgcopy, templ, result, CV_TM_SQDIFF_NORMED);//��������ʹ�õ�ƥ���㷨�Ǳ�׼ƽ����ƥ�� method=CV_TM_SQDIFF_NORMED����ֵԽСƥ���Խ��
		normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
		imshow("res", result);
		double minVal = -1;
		double maxVal;
		Point minLoc;
		Point maxLoc;
		Point matchLoc;
		Point oldmatchLoc;
		minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
		cout << "ƥ��ȣ�" << minVal << endl;

		if (minLoc == oldmatchLoc)//�Ѿ�ƥ�����λ�ò��ٽ���ƥ��
		{
			break;
		}
		matchLoc = minLoc;//ƥ�䷽����Ӧ��С�����λ��
		rectangle(img, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(0, 255, 0), 2, 8, 0);
		imshow("img", img);
	
		Rect r1(matchLoc.x , matchLoc.y, templ.rows , templ.cols);
		try {
			imgcopy(r1).setTo(0);//��ԭͼ���ѳɹ�ƥ������������䣬�˺���ڴ�����ƥ�䲻��
		}
		catch (exception err) {//��������ʧ�ܣ�ƥ�䵽�������С����������ƥ��
			//cout << err.what() << endl;
			cout <<"ƥ�������"<< matchnum << endl;
			waitKey(0);
			return 0;
		}
		imshow("imgcopy", imgcopy);
		
	}
	waitKey(0);
	return 0;
}