/*
Learning notes for "opencv3 introduction to programming"
Created by Xiaoxiao
2019.8.14
*/

#include<opencv2/opencv.hpp>

//第二个参数：0—99>0,100-199>1,200-255>2
void createLUT(cv::Mat& table, int divide)
{
        table.create(1, 256, CV_8UC1);

        uchar* p = table.data;

        for (int i = 0; i < 256; i++)
        {
                //利用c++自动截余功能，减少颜色数
                p[i] = divide*(i / divide);
                //或者p[i] = divide*(i / divide)+ divide / 2;
        }
}
int main(int argc,char* argv[])
{
        cv::Mat src = cv::imread("H:\\猫1.jpg");

        cv::Mat dst, table;

        createLUT(table,32);

        cv::LUT(src, table, dst);

        cv::imshow("LUT", dst);

        cv::waitKey();

        return 0;

}
/*
对图像中的像素表达进行量化。如常见的RGB24图像有256×256×256中颜色，
通过Reduce Color将每个通道的像素减少8倍至256/8=32种，
则图像只有32×32×32种颜色。假设量化减少的倍数是N，
则代码实现时就是简单的value/N*N，
通常我们会再加上N/2以得到相邻的N的倍数的中间值，
最后图像被量化为(256/N)×(256/N)×(256/N)种颜色.

计算机是使用二进制来进行运算，
所以2的N次方的运算是最快的。
2^N 的输出也是色彩损失最小的方向。
这是文件尺寸和输出效果之间的最佳平衡点。*/

/* LINK : warning LNK4075: 忽略”/EDITANDCONTINUE”(由于”/INCREMENTAL:NO”规范)
选择项目 属性->配置属性->c/c++
  修改 “调试信息格式” 为 程序数据库（/zi）

参考：
https://blog.csdn.net/jameshater/article/details/50759650 */
