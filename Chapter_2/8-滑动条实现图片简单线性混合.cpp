/*
Learning notes for "opencv3 introduction to programming"
Created by Xiaoxiao
2019.8.14
*/

//Warning:忽略“/EDITANDCONTINUE”(由于“/OPT:LBR”规范)
//解决：项目属性->配置属性->c/c++修改 “调试信息格式” 为 程序数据库


//经过摸索尝试，发现进行图像线性混合需要满足：宽高完全相同

#include<opencv2/opencv.hpp>
#include<vector>

#pragma warning(disable:4996)
#define Window_name  "线性混合" //窗口标题

//声明存储图像的变量
cv::Mat src1;
cv::Mat src2;
cv::Mat dst;

//线性混合两个参数
double AlphaValue, BetaValue;
//当前滑动条对应的变量
int Alphaslider;
//Alpha值的最大值
const int Maxslider = 100;

/*
        轨迹条的回调函数（通过函数指针调用的函数）：
        函数原型必须是：void XXXX(int, void*);
        第一个参数为轨迹条的位置，第二个参数为用户数据
*/
void on_Trackbar(int, void*)
{
        AlphaValue = (double)Alphaslider / Maxslider;

        BetaValue = 1.0 - AlphaValue;

        //线性混合
        addWeighted(src1 , AlphaValue , src2 , BetaValue , 0.0 , dst);

        cv::imshow(Window_name, dst);
}

int main(int argc,char** argv)
{
        src1 = cv::imread("H:\\猫1.jpg");
        src2 = cv::imread("H:\\猫5.jpg");

        if ((!src1.data) || (!src2.data))
        {
                std::cout << "Can not load image" << "\n";
                return -1;
        }
        //return 0 正常退出 return -1 异常退出

        Alphaslider = 70;

        cv::namedWindow(Window_name,0);
        //namedWindow第二个参数flag = 0即CV_WINDOW_NORMAL,flag = 1即CV_WINDOW_AUTOSIZE

        char cvtrackbar[50];
        sprintf(cvtrackbar,"透明值 %d ",Maxslider);
        /*
        防止sprintf报错的方法：
        1.程序开头添加#pragma warning(disable:4996)
        2.项目属性里关闭SDL
        3.将sprintf改成sprintf_s

        sprintf的作用是将一个格式化的字符串输出到一个目的字符串中，
        而printf是将一个格式化的字符串输出到屏幕。

        实例：
        char a = 'a';
        char buf[80];
        sprintf(buf, "%d", a);
        printf("%s", buf);
        输出：97
        */

        cv::createTrackbar(cvtrackbar,Window_name,&Alphaslider,Maxslider,on_Trackbar);
        /*
        创建轨迹条
        参数一、trackbarname：滑动空间的名称；
        参数二、winname：滑动空间用于依附的图像窗口的名称；必须和cvNameWindow的
		第一个参数完全一致
        参数三、value：初始化阈值；
        参数四、count：滑动控件的刻度范围；
        参数五、TrackbarCallback是回调函数
        */
        cv::getTrackbarPos(cvtrackbar,Window_name);
        /*
        获取当前轨迹条的位置
        参数一、trackbarname：滑动空间的名称；
        参数二、winname：滑动空间用于依附的图像窗口的名称；
        */
        on_Trackbar(Alphaslider,0);

        cv::waitKey();

        system("pause");
        return 0;
}
