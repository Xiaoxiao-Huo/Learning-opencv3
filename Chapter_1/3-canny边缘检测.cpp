#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

int main()
{
    //canny边缘检测：载入，转灰度图，降噪，运行canny
    cv::Mat srcImg, grayImg,edge;
    srcImg = cv::imread("H:/test.jpg");
	
    //创建与srcImg同类型和大小的矩阵
    grayImg.create(srcImg.size(), srcImg.type());
	
    //转为灰度图
    cv::cvtColor(srcImg, grayImg,cv::COLOR_BGR2GRAY);
	
    //用3*3内核降噪
    cv::blur( grayImg,edge, cv::Size(3, 3));
	
    //运行canny算子
    cv::Canny(edge, edge, 3, 9, 3);
    /*canny:1 输入图像，单通道灰度图 2 输出图像，单通道黑白图
    3 下阈值 4 上阈值 一般上阈值/下阈值=2~3 5 算子大小，默认为3，表示3*3的矩阵*/
	
    cv::namedWindow("edge",0); //第二参数为0时可调整窗口大小，1为自动调整，不可修改
    cv::imshow("边缘检测", edge);
    cv::waitKey(0);
}
