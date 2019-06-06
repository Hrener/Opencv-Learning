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
	cvtColor(cannyout, houghout, CV_GRAY2BGR);//תBGR����Ϊ���Ҫ��ֱ�ߣ���ɫ��
	cvtColor(cannyout, houghout1, CV_GRAY2BGR);//תBGR����Ϊ���Ҫ��ֱ�ߣ���ɫ��
	imshow("��Ե�����ͼ", cannyout);

	//һ��HoughLines

	vector<Vec2f> lines;// ����ʸ���ṹ��ż�������ֱ��
	HoughLines(cannyout, lines, 1, CV_PI / 180, 150, 0, 0);
	/*����ע��������������ʾ��ֵ����ֵԽ�󣬱�������Խ��׼���ٶ�Խ�죬
	�õ���ֱ��Խ�٣��õ���ֱ�߶��Ǻ��а��յ�ֱ�ߣ�
	����õ���lines�ǰ���rho��theta�ģ���������ֱ���ϵĵ㣬����������Ҫ����
	�õ���rho��theta������һ��ֱ��*/

	//���λ���ÿ���߶�
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0]; //����Բ�İ뾶r
		float theta = lines[i][1]; //����ֱ�ߵĽǶ�
		float angle = theta / CV_PI * 180;//����ת�Ƕ�
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));//����1000�ӳ��ߵĳ���
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));

		line(houghout, pt1, pt2, Scalar(255, 0, 0), 1, LINE_AA); //Scalar�������ڵ����߶���ɫ�����������⵽���߶���ʾ����ʲô��ɫ

		imshow("HoughLines", houghout);
		//rho��ʾ������ԭ�㣨����ͼƬ���Ͻǵĵ㣩�ľ��룬theta��ֱ�ߵ���ת�Ƕȣ�0�ȱ�ʾ��ֱ�ߣ�90�ȱ�ʾˮƽ�ߣ���
		cout << "line " << i << ":" << "  rho:" << rho << "  theta:" << angle << endl;
	}


	//����HoughLinesP
	vector<Vec4i> lines1;
	//��HoughLines��ͬ���ǣ�HoughLinesP�õ�lines���Ǻ���ֱ���ϵ������ģ�����������л���ʱ�Ͳ�����Ҫ�Լ������������ȷ��Ψһ��ֱ����
	HoughLinesP(cannyout, lines1, 1, CV_PI / 180, 150, 50, 10);//ע������������Ϊ��ֵ

	//���λ���ÿ���߶�
	for (size_t i = 0; i < lines1.size(); i++)
	{
		Vec4i l = lines1[i];
		line(houghout1, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, LINE_AA); //Scalar�������ڵ����߶���ɫ
		imshow("HoughLinesP", houghout1);
	}
	waitKey(0);
	return 0;
}
