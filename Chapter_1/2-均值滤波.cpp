#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

int main()
{
        cv::Mat srcImg, desImg;
		srcImg = cv::imread("H:/test.jpg");
        //blur:均值滤波 内核Size越大越模糊
        cv::blur(srcImg, desImg, cv::Size(15, 15));
        cv::imshow("after blur", desImg);
        cv::waitKey(0);
}
