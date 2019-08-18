/*
Learning notes for "opencv3 introduction to programming"
Create by Xiaoxiao
2019.8.14
*/

#include<opencv2/opencv.hpp>

#define Window_name "程序窗口"

/*
回调函数
x,y为鼠标指针所在坐标，
param是用户传递到setMouseCallback的参数，
EVENT_MOUSEMOVE为鼠标移动消息
EVENT_LBUTTONDOWN为鼠标左键按下消息
*/
void mouseHandle(int event, int x, int y, int flag, void* param);
void Drawrectangle(cv::Mat &img, cv::Rect box);

cv::Rect g_rectangle;

bool Drawing = false;

//RNG类是opencv里C++的随机数产生器。它可产生一个64位的int随机数。
cv::RNG rng(12345);

int main(int argc, char** argv)
{
        //【1】准备参数
        g_rectangle = cv::Rect(-1, -1, 0, 0);
        cv::Mat src(680, 800, CV_8UC3), dst;
        //copyTo:将src复制到dst矩阵中
        src.copyTo(dst);
        /*
        scalar所有元素设置为0
        Scalar是一个由长度为4的数组作为元素构成的结构体，Scalar最多可以存储四个值
        例如：cv::Mat M(7,7,CV_32FC2,Scalar(1,3));
        上面的代码表示：创建一个2通道，且每个通道的值都为（1,3），深度为32，7行7列的图像矩阵。
        CV_32F表示每个元素的值的类型为32位浮点数，C2表示通道数为2，
        Scalar（1,3）表示对矩阵每个元素都赋值为（1,3），第一个通道中的值都是1，第二个通道中的值都是3.
        */
        src = cv::Scalar::all(0);

        //【2】设置鼠标操作回调函数
        cv::namedWindow(Window_name, 0);

        /*指定鼠标操作消息回调
        第一个参数const string& winname：窗口名字
        第二个参数MouseCallback onMouse：窗口每次鼠标事件发生时，被回调的函数指针
        这个函数的原型应该为void on_Mouse(int event, int x, int y, int flags, void* param);
        第三个参数void* userdata=0：传给回调函数的参数
        */
        cv::setMouseCallback(Window_name,mouseHandle,(void*)&src);

        //【3】程序主循环，当绘制标识符为真，开始绘制
        while (1)
        {
                src.copyTo(dst);
                if (Drawing)
                        Drawrectangle(dst, g_rectangle);
                imshow(Window_name, dst);
                //按下ESC(ASCII码为27),则跳出循环
                if (cv::waitKey(10) == 27)
                        break;
        }
        return 0;
}


void mouseHandle(int event, int x, int y, int flag, void * param)
{
        cv::Mat& image = *(cv::Mat*)param;
        switch (event)
        {
                //鼠标移动消息
                case cv::EVENT_MOUSEMOVE:
                {
                        if (Drawing)
                        {
                                g_rectangle.width = x - g_rectangle.x;
                                g_rectangle.height = y - g_rectangle.y;
                        }
                }
                break;

                //左键按下消息
                case cv::EVENT_LBUTTONDOWN:
                {
                        Drawing = true;
                        g_rectangle = cv::Rect(x, y, 0, 0);
                        //Rect:左上角xy坐标，矩形宽高
                }
                break;

                //左键抬起消息
                case cv::EVENT_LBUTTONUP:
                {
                        Drawing = false;
                        //对宽高小于0分别处理
                        if (g_rectangle.width < 0)
                        {
                                g_rectangle.x += g_rectangle.width;
                                g_rectangle.width *= -1;
                        }
                        if (g_rectangle.height < 0)
                        {
                                g_rectangle.y += g_rectangle.height;
                                g_rectangle.height *= -1;
                        }
                        //回调，绘制矩形
                        Drawrectangle(image, g_rectangle);
                }
                break;
        }
}

void Drawrectangle(cv::Mat &img,cv::Rect box)
{
        /*rectangle绘制矩形框，第二个参数：左上角坐标，第三个参数，右下角坐标，线宽默认为8*/
        cv::rectangle(img, box.tl(), box.br(), cv::Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0, 255)),10);
}
