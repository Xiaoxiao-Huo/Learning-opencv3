/*
Learning notes for "opencv3 introduction to programming"
Created by Xiaoxiao
2019.8.14
*/

#include<opencv2/opencv.hpp>
#include<vector>

void createAlphaMat(cv::Mat &mat)
{
        for (int i = 0; i < mat.rows; ++i) {
                for (int j = 0; j < mat.cols; ++j) {
                        cv::Vec4b&rgba = mat.at<cv::Vec4b>(i, j);
                        rgba[0] = UCHAR_MAX;
                        //B,赋值255
                        //saturate_cast防溢出函数，大于255则为255，小于0则为0
                        rgba[1] = cv::saturate_cast<uchar>((float(mat.cols - j)) / ((float)mat.cols) *UCHAR_MAX);
                        //G
                        rgba[2] = cv::saturate_cast<uchar>((float(mat.rows - i)) / ((float)mat.rows) *UCHAR_MAX);
                        //R
                        rgba[3] = cv::saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
                        //Alpha：第四（透明）通道是值的范围是0-255（因为是uchar类型的），0代表透明，255代表不透明。
                }
        }
}

int main()
{

        //创建带alpha通道的Mat
        cv::Mat mat(480, 640, CV_8UC4); //CV_8UC4：8位 unsigned 4通道
        createAlphaMat(mat);

        using std::vector;
        //vector<vector<int> > compression_params;
        vector<int> compression_params;

        //push_back方法：在vector尾部添加一个数据
        //转成jpeg形式:参数范围0-100
        /*compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
        compression_params.push_back(100);*/

        //转成png形式:参数范围：0-9
        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
        compression_params.push_back(100);

        try
        {
                cv::imwrite("透明图片.jpg", mat, compression_params);
                //cv::imwrite("透明图片.png", mat, compression_params);

                cv::imshow("image", mat);
                cv::waitKey();
        }

        catch(std::runtime_error& ex)
        {
                fprintf(stderr, ex.what());
                return 1;
        }

}
