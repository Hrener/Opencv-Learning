#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;

int main()
{

	Mat srcimg = imread("fangzi.png");
	Mat cannyout, houghout,houghout1;
	/*cvtColor(srcimg, houghout, CV_BGR2GRAY);
	Canny(houghout, cannyout, 50, 200, 3);
	imshow("a", cannyout);*/
	Canny(srcimg,cannyout,200,250,3);
	cvtColor(cannyout, houghout, CV_GRAY2BGR);//转BGR是因为最后要画直线（彩色）
	cvtColor(cannyout, houghout1, CV_GRAY2BGR);//转BGR是因为最后要画直线（彩色）
	imshow("边缘检测后的图", cannyout);

	//一、HoughLines

	vector<Vec2f> lines;// 定义矢量结构存放检测出来的直线
	HoughLines(cannyout, lines, 1, CV_PI / 180, 150, 0, 0);
	/*这里注意第五个参数，表示阈值，阈值越大，表明检测的越精准，速度越快，
	得到的直线越少（得到的直线都是很有把握的直线）
	这里得到的lines是包含rho和theta的，而不包括直线上的点，所以下面需要根据
	得到的rho和theta来建立一条直线*/

	//依次画出每条线段
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0]; //就是圆的半径r
		float theta = lines[i][1]; //就是直线的角度
		float angle = theta / CV_PI * 180;//弧度转角度
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));//乘以1000加长线的长度
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));

		line(houghout, pt1, pt2, Scalar(255, 0, 0), 1, LINE_AA); //Scalar函数用于调节线段颜色，就是你想检测到的线段显示的是什么颜色

		imshow("HoughLines", houghout);
		//rho表示离坐标原点（就是图片左上角的点）的距离，theta是直线的旋转角度（0度表示垂直线，90度表示水平线）。
		cout << "line " << i << ":" << "  rho:" << rho << "  theta:" << angle << endl;
	}


	//二、HoughLinesP
	vector<Vec4i> lines1;
	//与HoughLines不同的是，HoughLinesP得到lines的是含有直线上点的坐标的，所以下面进行划线时就不再需要自己求出两个点来确定唯一的直线了
	HoughLinesP(cannyout, lines1, 1, CV_PI / 180, 150, 50, 10);//注意第五个参数，为阈值

	//依次画出每条线段
	for (size_t i = 0; i < lines1.size(); i++)
	{
		Vec4i l = lines1[i];
		line(houghout1, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, LINE_AA); //Scalar函数用于调节线段颜色
		imshow("HoughLinesP", houghout1);
	}
	waitKey(0);
	return 0;
}
