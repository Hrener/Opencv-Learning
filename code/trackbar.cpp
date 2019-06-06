#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;


int pic_num = 0;
Mat imggray = imread("Lena.jpg");
Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
Mat result;
void on_track(int, void*)
{
	if (pic_num == 0)
	{
		erode(imggray, result, element);
	}
	else if(pic_num == 1)
	{
		dilate(imggray, result, element);
	}
	imshow("��ʴ����", result);
	cout << pic_num << endl;
}

int main()
{
	namedWindow("��ʴ����");
	createTrackbar("0-1", "��ʴ����", &pic_num, 1, on_track);
	on_track(pic_num, NULL);
	waitKey(0);
	return 0;
}