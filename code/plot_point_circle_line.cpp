//#####################
//画几何形状
//ellipse(Mat& img, Point center, Size axes, double angle, double startAngle, double endAngle, const Scalar& color, int thickness = 1, int lineType = 8, int shift = 0)
//rectangle(Mat& img,Rect rec, const Scalar&color, intthickness=1, intlineType=8,intshift=0 )
//line(InputOutputArray img, Point pt1, Point pt2, const Scalar& color,int thickness = 1, int lineType = LINE_8, int shift = 0);
//circle( CvArr* img, CvPoint center, int radius, CvScalar color,int thickness = 1, int line_type = 8, int shift = 0 );
//圆、点都是使用circle()函数来画
//#####################
#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;
RNG rng(12345);//构造方法设定一个具体值，表示下面代码每次生成的结果都是一样的
Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));//从[0,255)范围内随机一个值
int main()
{
	Mat image = imread("vn.jpg");
	Point p(100,100),p1(300,100); 
	////这种初始化点的方式也可以 
	//Point p2;
	//p2.x = 100;
	//p2.y = 100;
	circle(image, p, 50, color,5);
	circle(image, p1, 50, color,-1);
	ellipse(image, Point(100, 100), Size(90, 60), 30, 0, 360, Scalar(255, 255, 0), 2, 8);
	rectangle(image, Rect(50, 50, 100, 100), Scalar(255, 255, 0), 2, 8);
	line(image, Point(100, 100), Point(500, 310), Scalar(255, 0, 255),2, 8);
	imshow("绘制几何", image);

	waitKey(0);
	return 0;
}
