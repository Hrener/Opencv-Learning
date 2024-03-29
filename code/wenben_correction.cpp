//#####################
//@图像矫正
//基于直线提取的矫正算法,适用于文本
//1、用霍夫线变换探测出图像中的所有直线
//2、计算出每条直线的倾斜角，求他们的平均值
//3、根据倾斜角旋转矫正
//4、最后根据文本尺寸裁剪图片
//#####################
#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;
#define ERROR 1234

//度数转换
double DegreeTrans(double theta)
{
	double res = theta / CV_PI * 180;
	return res;
}


//逆时针旋转图像degree角度（原尺寸）    
void rotateImage(Mat src, Mat& img_rotate, double degree)
{
	//旋转中心为图像中心    
	Point2f center;
	center.x = float(src.cols / 2.0);
	center.y = float(src.rows / 2.0);
	int length = 0;
	length = sqrt(src.cols*src.cols + src.rows*src.rows);
	//计算二维旋转的仿射变换矩阵  
	Mat M = getRotationMatrix2D(center, degree, 1);
	warpAffine(src, img_rotate, M, Size(src.cols, src.rows), 1, 0, Scalar(255, 255, 255));//仿射变换，背景色填充为白色  
}

//通过霍夫变换计算角度
double CalcDegree(const Mat &srcImage, Mat &dst)
{
	Mat midImage, dstImage;

	Canny(srcImage, midImage, 50, 200, 3);
	cvtColor(midImage, dstImage, CV_GRAY2BGR);

	//通过霍夫变换检测直线
	vector<Vec2f> lines;
	HoughLines(midImage, lines, 1, CV_PI / 180, 300, 0, 0);//第5个参数就是阈值，阈值越大，检测精度越高
	//cout << lines.size() << endl;

	//由于图像不同，阈值不好设定，因为阈值设定过高导致无法检测直线，阈值过低直线太多，速度很慢
	//所以根据阈值由大到小设置了三个阈值，如果经过大量试验后，可以固定一个适合的阈值。

	if (!lines.size())
	{
		HoughLines(midImage, lines, 1, CV_PI / 180, 200, 0, 0);
	}
	//cout << lines.size() << endl;

	if (!lines.size())
	{
		HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);
	}
	//cout << lines.size() << endl;
	if (!lines.size())
	{
		cout << "没有检测到直线！" << endl;
		return ERROR;
	}

	float sum = 0;
	//依次画出每条线段
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0];
		float theta = lines[i][1];
		Point pt1, pt2;
		//cout << theta << endl;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		//只选角度最小的作为旋转角度
		sum += theta;

		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA); //Scalar函数用于调节线段颜色

		imshow("直线探测效果图", dstImage);
	}
	float average = sum / lines.size(); //对所有角度求平均，这样做旋转效果会更好

	cout << "average theta:" << average << endl;

	double angle = DegreeTrans(average) - 90;

	rotateImage(dstImage, dst, angle);
	//imshow("直线探测效果图2", dstImage);
	return angle;
}


void ImageRecify(const char* pInFileName, const char* pOutFileName)
{
	double degree;
	Mat src = imread(pInFileName);
	imshow("原始图", src);
	Mat dst;
	//倾斜角度矫正
	degree = CalcDegree(src, dst);
	if (degree == ERROR)
	{
		cout << "矫正失败！" << endl;
		return;
	}
	rotateImage(src, dst, degree);
	cout << "angle:" << degree << endl;
	imshow("旋转调整后", dst);

	Mat resulyImage = dst(Rect(50, 50, dst.cols-100, dst.rows - 100)); //根据先验知识，估计好文本的长宽，再裁剪下来
	imshow("裁剪之后", resulyImage);
	//imwrite("recified.jpg", resulyImage);
}


int main()
{
	ImageRecify("wenben.jpg", "afterwenben.jpg");
	waitKey();
	return 0;
}