#include <iostream>
#include<opencv2\opencv.hpp>   
#include<opencv2\highgui.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("Lena.jpg");
	Mat erode1,dilate1;

	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	erode(srcImage, erode1, element);
	dilate(srcImage, dilate1, element);

	imshow("srcImage", srcImage);
	imshow("erode", erode1);
	imshow("dilate", dilate1);

	waitKey(0);
	return 0;
}
