/*
Learning notes for "opencv3 introduction to programming"
Created by Xiaoxiao
2019.8.14
*/

#include<opencv2/opencv.hpp>

int main()
{

        //经过摸索尝试，发现进行初级图像混合需要满足：
        //1.宽高比相同 2.被叠加的原图大于叠加上去的图片大小
        cv::Mat image = cv::imread("H:\\猫1.jpg");
        cv::Mat image4 = cv::imread("H:\\猫4.jpg");

        printf("猫1宽高与高宽比：%d %d %f\n", image.cols, (double)image.rows,image.rows/image.cols);
        printf("猫4宽高：%d %d %f\n", image4.cols, image4.rows, (double)image4.rows/image4.cols);

         //定义一个cv::Mat类型，用于存放，图像的ROI(ROI 感兴趣领域)
        cv::Mat imageROI;
        //方法一 rect先宽后高：通过定义矩形左上角坐标和矩形的宽和高来确定一个矩形。
        /*typedef struct CvRect
　　	{
　　	int x; //方形的左上角的x-坐标
　　	int y; //方形的左上角的y-坐标
　　	int width;   //宽
　　	int height;  //高
　　	} */
        imageROI = image(cv::Rect(80, 35, image4.cols, image4.rows));

        //方法二 range先高后宽 Range截取image的第30行到30+image4.rows行，第20列到第image4.rows+20列
        //imageROI= image(cv::Range(30,30+image4.rows),Range(20,20+image4.cols));

        //将image4加到原图image上
        /* addWeighted函数
        void addWeighted(InputArray src1, double alpha, InputArray src2, double beta,
        double gamma, OutputArray dst, int dtype=-1)

        第一个参数，InputArray类型的src1，表示需要加权的第一个数组，常常填一个Mat。
        第二个参数，alpha，表示第一个数组的权重
        第三个参数，src2，表示第二个数组，它需要和第一个数组拥有相同的尺寸和通道数。
        第四个参数，beta，表示第二个数组的权重值。
        第五个参数，dst，输出的数组，它和输入的两个数组拥有相同的尺寸和通道数。
        第六个参数，gamma，一个加到权重总和上的标量值。（微调）
        第七个参数，dtype，输出阵列的可选深度，有默认值-1。;
        当两个输入数组具有相同的深度时，这个参数设置为-1（默认值），即等同于src1.depth（）。 */
        addWeighted(imageROI, 0.5, image4, 0.5, 0., imageROI);

        //显示结果
        cv::namedWindow("image",CV_WINDOW_NORMAL);
        imshow("image", image);

        //输出一张jpg图片到工程目录下
        imwrite("图片叠加.jpg", image);

        cv::waitKey();

        return 0;
}
