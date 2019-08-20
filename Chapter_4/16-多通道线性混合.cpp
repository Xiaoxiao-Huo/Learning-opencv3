/*
Learning notes for "opencv3 introduction to programming"
Created by Xiaoxiao
2019.8.14
*/

#include<opencv2/opencv.hpp>
#include<vector>

bool MultiChannelsBlending();

int main()
{
        MultiChannelsBlending();
        system("pause");
        return 0;
}

bool MultiChannelsBlending()
{
        cv::Mat src1 = cv::imread("H:\\猫5.jpg");
        cv::Mat src2 = cv::imread("H:\\black_white.jpg",0);
        //必须是灰度图
        cv::Mat image_ROI;
        cv::Mat BlueChannel;
        std::vector<cv::Mat> channels;

        if (!src1.data || !src2.data)
                return false;

        cv::split(src1, channels);
        BlueChannel = channels.at(0);
        /*或：BlueChannel = channels[0];
        channels.at(1); G channels.at(2); R
        */

        image_ROI = BlueChannel(cv::Rect(50, 20, src2.cols, src2.rows));

        cv::addWeighted(image_ROI, 1.0, src2, 0.5, 0.0, image_ROI);

        cv::merge(channels, src1);
        /*merge(InputArrayOfArrays mv,OutputArray dst)
        mv，填需要被合并的输入矩阵或vector容器的阵列，
        这个mv参数中所有的矩阵必须有着一样的尺寸和深度。
        dst，即输出矩阵，和mv[0]拥有一样的尺寸和深度，
        并且通道的数量是矩阵阵列中的通道的总数。*/

        cv::namedWindow("split_merge", 0);
        cv::imshow("split_merge", src1);
        cv::imwrite("split_merge.jpg", src1);
        cv::waitKey(0);
        return true;
}
