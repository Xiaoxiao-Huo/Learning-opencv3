/*
Learning notes for "opencv3 introduction to programming"
Create by Xiaoxiao
2019.8.14
*/

#include<opencv2/opencv.hpp>
#include<vector>

int main()
{

        cv::Mat img = cv::imread("H:\\test.jpg", 1);
        cv::namedWindow("image", CV_WINDOW_NORMAL);

        //using namespace std;
        using std::vector;

        vector<int> compression_params;

        //push_back方法：在vector尾部添加一个数据
        //转成jpeg形式:参数范围0-100
        compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
        compression_params.push_back(100);

        //转成png形式:参数范围：0-9
        //compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
        //compression_params.push_back(5);

        cv::imwrite("1.jpg", img,compression_params);
        //cv::imwrite("2.png", img, img,compression_params);

        cv::imshow("image", img);
        cv::waitKey();
}
