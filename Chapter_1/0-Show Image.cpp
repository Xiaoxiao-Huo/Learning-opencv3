#One

#include<opencv2/opencv.hpp>
using namespace cv;
//包含cv命名空间

int main()
{
        //读入一张图片
        Mat img = imread("H:\\test.jpg");
        //Mat img = imread("H:/test.jpg");
        //在窗口中显示载入的图片
        imshow("test", img);
        //等待6000 ms后窗口自动关闭
        waitKey(6000);

}

#Two

#include<opencv2/opencv.hpp>

int main()
{
        cv::Mat img = cv::imread("H:\\test.jpg");
        cv::namedWindow("image", CV_WINDOW_NORMAL);
        //CV_WINDOW_NORMAL参数可调整窗口大小
        //默认参数为CV_WINDOW_AUTOSIZE不可调整窗口大小
        cv::imshow("test", img);
        cv::waitKey(0); //等待任意键按下
}
