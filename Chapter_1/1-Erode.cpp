#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

int main()
{
		cv::Mat srcImg, desImg;
		srcImg = cv::imread("H:/test.jpg");
        //getStructuringElement:指定形状和尺寸的结构元素（内核矩阵）
        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(15,15));
        //erode:腐蚀操作
        cv::erode(srcImg, desImg, element);
        cv::imshow("after eroding", desImg);
        cv::waitKey(0);
}
