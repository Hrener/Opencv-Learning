//#####################
//����任
//#####################
#include <iostream>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
using namespace std;
using namespace cv;

int main()
{

	Mat src = imread("Lena.jpg");
	Mat dst_warp, dst_warpRotateScale;
	Point2f srcPoints[3];//ԭͼ�е�����  
	Point2f dstPoints[3];//Ŀ��ͼ�е�����  

	//��һ�ַ���任�ĵ��÷�ʽ�����㷨
	//������Ե�ֵ,����Ҳ˵�ˣ�ֻҪ֪������Ҫ�任��ͼ������������꣬�Ϳ���ʵ�ַ���任  
	srcPoints[0] = Point2f(0, 0);
	srcPoints[1] = Point2f(0, src.rows - 1);
	srcPoints[2] = Point2f(src.cols - 1, 0);
	//ӳ������������ֵ
	dstPoints[0] = Point2f(0, src.rows*0.3);
	dstPoints[1] = Point2f(src.cols*0.25, src.rows*0.75);
	dstPoints[2] = Point2f(src.cols*0.75, src.rows*0.25);

	Mat M1 = getAffineTransform(srcPoints, dstPoints);//��������Լ���任����  
	warpAffine(src, dst_warp, M1, src.size());//����任  


	//�ڶ��ַ���任�ĵ��÷�ʽ��ֱ��ָ���ǶȺͱ���                                          
	//��ת������  
	Point2f center(src.cols / 2, src.rows / 2);//��ת����  
	double angle = 60;//��ʱ����ת45��  
	double scale = 0.7;//���ű���  

	Mat M2 = getRotationMatrix2D(center, angle, scale);//������ת�����ŵı任����  
	warpAffine(dst_warp, dst_warpRotateScale, M2, src.size());//����任  
	
	////����ͼƬ
	//char file[1];
	//sprintf(file, "Lena_affine.jpg");  //��תͼƬ��1.jpg  2.jpg �����ָ�ʽ����
	//imwrite(file, dst_warpRotateScale);

	imshow("ԭʼͼ", src);
	imshow("����任1", dst_warp);
	imshow("����任2", dst_warpRotateScale);
	waitKey(0);
	return 0;
}
