//#####################
//@图像矫正
//基于轮廓提取的矫正算法,适用于有明显的边界轮廓的图
//1、图片灰度化
//2、阈值二值化
//3、检测轮廓
//4、寻找轮廓的包围矩阵，并且获取角度
//5、根据角度进行旋转矫正
//6、对旋转后的图像进行轮廓提取
//7、对轮廓内的图像区域抠出来，成为一张独立图像
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
	//注意第5个参数为CV_RETR_EXTERNAL，只检索外框  
	findContours(binimg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //找轮廓
	cout << contours.size() << endl;

	CvBox2D rect;
	for (int i = 0; i < contours.size(); i++)
	{
		 rect = minAreaRect(Mat(contours[i]));//minAreaRect找到轮廓最小外接矩形
		
	}
	CvPoint2D32f rectpoint[4];
	cvBoxPoints(rect, rectpoint); //获取最小外接矩形4个顶点坐标 ，储存顶点的顺序会因为轮廓的不同而不同


	//与水平线的角度  
	float angle = rect.angle;
	cout << angle << endl;

	int line1 = sqrt((rectpoint[1].y - rectpoint[0].y)*(rectpoint[1].y - rectpoint[0].y) + (rectpoint[1].x - rectpoint[0].x)*(rectpoint[1].x - rectpoint[0].x));
	int line2 = sqrt((rectpoint[3].y - rectpoint[0].y)*(rectpoint[3].y - rectpoint[0].y) + (rectpoint[3].x - rectpoint[0].x)*(rectpoint[3].x - rectpoint[0].x));
	//rectangle(binImg, rectpoint[0], rectpoint[3], Scalar(255), 2);
	//面积太小的直接pass
	/*if (line1 * line2 < 600)
	{
		continue;
	}*/
	////为了让正方形横着放，所以旋转角度是不一样的。竖放的，给他加90度，翻过来  
	if (line1 > line2)
	{
		angle = 90 + angle;
	}



	//新建一个感兴趣的区域图，大小跟原图一样大  
	Mat RoiSrcImg(src.rows, src.cols, CV_8UC3); //注意这里必须选CV_8UC3
	RoiSrcImg.setTo(0); //颜色都设置为黑色  
	//imshow("新建的ROI", RoiSrcImg);
	//对得到的轮廓填充一下  
	drawContours(binimg, contours, -1, Scalar(255), CV_FILLED);
	//imshow("binimg", binimg);
	//抠图到RoiSrcImg
	src.copyTo(RoiSrcImg, binimg);
	//imshow("RoiSrcImg", RoiSrcImg);



	//创建一个旋转后的图像  
	Mat RatationedImg(RoiSrcImg.rows, RoiSrcImg.cols, CV_8UC1);
	RatationedImg.setTo(0);
	//对RoiSrcImg进行旋转  
	Point2f center = rect.center;  //中心点  
	Mat M2 = getRotationMatrix2D(center, angle, 1);//计算旋转加缩放的变换矩阵 
	warpAffine(RoiSrcImg, RatationedImg, M2, RoiSrcImg.size(), 1, 0, Scalar(0));//仿射变换 
	//imshow("旋转之后", RatationedImg);
	//imwrite("afterjiaozheng.jpg", RatationedImg); //将矫正后的图片保存下来



	//对ROI区域进行抠图
	//对旋转后的图片进行轮廓提取  
	vector<vector<Point> > contours2;
	Mat SecondFindImg;
	cvtColor(RatationedImg, SecondFindImg, COLOR_BGR2GRAY);  //灰度化  
	threshold(SecondFindImg, SecondFindImg, 80, 200, CV_THRESH_BINARY);
	findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//cout << "sec contour:" << contours2.size() << endl;

	for (int j = 0; j < contours2.size(); j++)
	{
		//这时候其实就是一个长方形了，所以获取rect  
		Rect rect = boundingRect(Mat(contours2[j]));
		//面积太小的轮廓直接pass,通过设置过滤面积大小，可以保证只拿到外框
		if (rect.area() < 600)
		{
			continue;
		}
		Mat dstImg = RatationedImg(rect);
		imshow("dst", dstImg);
		//imwrite("jiaozhengROI.jpg", dstImg);

	}
#if 0
		//对ROI区域进行抠图

		//对旋转后的图片进行轮廓提取  
		vector<vector<Point> > contours2;
		Mat raw = imread("afterjiaozheng.jpg");
		Mat SecondFindImg;
		//SecondFindImg.setTo(0);
		cvtColor(raw, SecondFindImg, COLOR_BGR2GRAY);  //灰度化  
		threshold(SecondFindImg, SecondFindImg, 80, 200, CV_THRESH_BINARY);
		findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		//cout << "sec contour:" << contours2.size() << endl;

		for (int j = 0; j < contours2.size(); j++)
		{
			//这时候其实就是一个长方形了，所以获取rect  
			Rect rect = boundingRect(Mat(contours2[j]));
			//面积太小的轮廓直接pass,通过设置过滤面积大小，可以保证只拿到外框
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
