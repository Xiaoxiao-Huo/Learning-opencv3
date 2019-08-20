/*
Learning notes for "opencv3 introduction to programming"
Created by Xiaoxiao
2019.8.14
*/

#include<opencv2/opencv.hpp>
#include<vector>

#pragma warning(disable:4996)
#define Window_name  "调整对比度和亮度"

//声明存储图像的变量
cv::Mat src,dst;

//对比度和亮度
int ContrastValue, BrightValue;

void ContrastAndBright(int, void*)
{
        for (int y = 0; y < src.rows; y++)
        {
                for (int x = 0; x < src.cols; x++)
                {
                        for (int c = 0; c < 3; c++)
                        {
                                dst.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>((ContrastValue*0.01)\
                                        *(src.at<cv::Vec3b>(y, x)[c]) + BrightValue);
                                //saturate_cast溢出保护
                        }
                }
        }
        cv::imshow(Window_name, dst);
}

int main(int argc, char** argv)
{
        src = cv::imread("H:\\猫1.jpg");
        dst = cv::Mat::zeros(src.size(), src.type());

        if ((!src.data))
        {
                std::cout << "Can not load image" << "\n";
                return -1;
        }

        ContrastValue = 80;
        BrightValue = 80;

        cv::namedWindow(Window_name, 0);

        cv::createTrackbar("对比度：", Window_name, &ContrastValue, 300, ContrastAndBright);
        cv::createTrackbar("亮度：", Window_name, &BrightValue, 200, ContrastAndBright);

        ContrastAndBright(ContrastValue, 0);
        ContrastAndBright(BrightValue, 0);

        cv::waitKey();

        system("pause");
        return 0;
}
