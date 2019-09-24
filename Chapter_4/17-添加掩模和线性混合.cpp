/*
Learning notes for "opencv3 introduction to programming"
Created by Xiaoxiao
2019.8.14
*/

#include<opencv2/opencv.hpp>

bool addImage();
bool LinearBlending();
int main()
{

        addImage();
        LinearBlending();
        system("pause");
        return 0;
}

bool addImage()
{

        cv::Mat image = cv::imread("H:\\猫1.jpg");
        cv::Mat image3 = cv::imread("H:\\猫4.jpg");

        if(!image.data||!image3.data)
        return false;

        cv::Mat imageROI = image(cv::Rect(0, 0, image3.cols, image3.rows));

        //必须是灰度图
        cv::Mat mask = cv::imread("H:\\猫4.jpg",0);

        //把mask复制到imageROI
        //把mask中像素值为0（black）的点对应的image中的点变为透明，而保留其他点
        image3.copyTo(imageROI,mask);

        cv::namedWindow("ROI", 0);
        cv::imshow("ROI", image);
        cv::imwrite("ROI_addImage.jpg", image);
        cv::waitKey(0);
        return true;
}

bool LinearBlending()
{
        double alphaValue = 0.5;
        double betaValue = 1.0 - alphaValue;

        //再次强调图片尺寸必须相同
        cv::Mat src1 = cv::imread("H:\\猫1.jpg");
        cv::Mat src2 = cv::imread("H:\\猫5.jpg");
        cv::Mat dst;

        if (!src1.data || !src2.data)
                return false;

        cv::addWeighted(src1, alphaValue, src2, betaValue, 0.0, dst);

        cv::namedWindow("LinearBlending", 0);
        cv::imshow("LinearBlending", dst);
        cv::imwrite("LinearBlending.jpg", dst);
        cv::waitKey(0);

        return true;
}
