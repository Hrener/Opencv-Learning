//#####################
//模板匹配
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
		matchTemplate(imgcopy, templ, result, CV_TM_SQDIFF_NORMED);//这里我们使用的匹配算法是标准平方差匹配 method=CV_TM_SQDIFF_NORMED，数值越小匹配度越好
		normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
		imshow("res", result);
		double minVal = -1;
		double maxVal;
		Point minLoc;
		Point maxLoc;
		Point matchLoc;
		Point oldmatchLoc;
		minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
		cout << "匹配度：" << minVal << endl;

		if (minLoc == oldmatchLoc)//已经匹配过的位置不再进行匹配
		{
			break;
		}
		matchLoc = minLoc;//匹配方法对应最小或最大位置
		rectangle(img, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(0, 255, 0), 2, 8, 0);
		imshow("img", img);
	
		Rect r1(matchLoc.x , matchLoc.y, templ.rows , templ.cols);
		try {
			imgcopy(r1).setTo(0);//将原图上已成功匹配区域用零填充，此后便在此区域匹配不到
		}
		catch (exception err) {//若作掩码失败（匹配到的区域过小），即结束匹配
			//cout << err.what() << endl;
			cout <<"匹配个数："<< matchnum << endl;
			waitKey(0);
			return 0;
		}
		imshow("imgcopy", imgcopy);
		
	}
	waitKey(0);
	return 0;
}