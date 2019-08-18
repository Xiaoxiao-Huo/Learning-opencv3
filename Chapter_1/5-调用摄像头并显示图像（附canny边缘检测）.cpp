
#One
#include<opencv2/opencv.hpp>

int main()
{

	cv::VideoCapture capture(0);
	//参数0表示摄像头

	while (1) 
	{
		cv::Mat frame; //定义一个Mat变量，存储帧
		capture >> frame; //读取当前帧
		cv::imshow("avi", frame); //显示当前帧
		cv::waitKey(300); //延时300ms
	}
	return 0;
}

#Two
#include<opencv2/opencv.hpp>

int main()
{

	cv::VideoCapture capture(0);
	//参数0表示摄像头
	cv::Mat edge;

	while (1) 
	{
		cv::Mat frame; //定义一个Mat变量，存储帧
		capture >> frame; //读取当前帧
		cvtColor(frame,edge,CV_BGR2GRAY); //转为灰度图
		blur(edge, edge, cv::Size(7, 7)); //均值模糊
		cv::Canny(edge, edge,0,30,3); //运行canny算子
		cv::imshow("edge", edge); //显示当前图像
		cv::waitKey(30); //延时30ms
	}
	return 0;
}