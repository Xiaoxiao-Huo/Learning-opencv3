/*
Learning notes for "opencv3 introduction to programming"
Created by Xiaoxiao
2019.8.14
*/

#include<opencv2/opencv.hpp>

#define Window_name1 "绘制图【1】"
#define Window_name2 "绘制图【2】"
#define WINDOW_WIDTH 600

//【1】绘制相同尺寸，不同角度的椭圆
void DrawEllipse(cv::Mat img,double angle)
{
        int thickness = 2;
        int lineType = 8;
        cv::ellipse(
                img,
                cv::Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2), //center,中心点位置
                cv::Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16), //axes,大小位于矩阵内，Size(width,height)
                angle,
                0, //startAngle
                360, //endAngle
                cv::Scalar(255, 129, 0), //蓝色
                thickness,
                lineType
        );
}

//【2】绘制实心圆
void DrawFilledCircle(cv::Mat img,cv::Point center)
{
        int thickness = -1;
        int lineType = 8;
        circle(
                img,
                center,
                WINDOW_WIDTH / 32, //半径radius
                cv::Scalar(0, 0, 255), //红色
                thickness,
                lineType
        );
}

//【3】绘制凸多边形
void DrawPolygon(cv::Mat img)
{
        int lineType = 8;
        cv::Point rookPoints[1][20];
        rookPoints[0][0] = cv::Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
        rookPoints[0][1] = cv::Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
        rookPoints[0][2] = cv::Point(3 * WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);
        rookPoints[0][3] = cv::Point(11 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
        rookPoints[0][4] = cv::Point(19 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
        rookPoints[0][5] = cv::Point(3 * WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
        rookPoints[0][6] = cv::Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
        rookPoints[0][7] = cv::Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
        rookPoints[0][8] = cv::Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
        rookPoints[0][9] = cv::Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
        rookPoints[0][10] = cv::Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
        rookPoints[0][11] = cv::Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
        rookPoints[0][12] = cv::Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
        rookPoints[0][13] = cv::Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
        rookPoints[0][14] = cv::Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
        rookPoints[0][15] = cv::Point(WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
        rookPoints[0][16] = cv::Point(WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
        rookPoints[0][17] = cv::Point(13 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
        rookPoints[0][18] = cv::Point(5 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
        rookPoints[0][19] = cv::Point(WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);

        const cv::Point* ppt[1] = { rookPoints[0] };
        int npt[] = { 20 };

        fillPoly(img,
                ppt, //顶点集
                npt, //顶点数目
                1, //contours 轮廓
                cv::Scalar(255, 255, 255), //白色
                lineType
        );
}
//【4】绘制线条
void DrawLine(cv::Mat img, cv::Point start, cv::Point end)
{
        int thickness = 2;
        int lineType = 8;
        line(
                img,
                start,
                end,
                cv::Scalar(0,0,0), //黑色
                thickness,
                lineType
        );
}

int main(void)
{
        cv::Mat atom = cv::Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH,CV_8UC3);
        cv::Mat rook = cv::Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

        //【1】绘制椭圆>原子图
        DrawEllipse(atom, 90); //垂直
        DrawEllipse(atom, 0); //水平
        DrawEllipse(atom, 45); //左上右下
        DrawEllipse(atom, -45);
        //【2】绘制实心圆
        DrawFilledCircle(atom, cv::Point( WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));

        //【3】绘制多边形
        DrawPolygon(rook);
        //【4】绘制矩形
        rectangle(
                rook,
                cv::Point(0,7*WINDOW_WIDTH/8),
                cv::Point(WINDOW_WIDTH,WINDOW_WIDTH),
                cv::Scalar(0,255,255), //黄色
                -1,
                8
        );
        //【5】绘制线条
        DrawLine(rook, cv::Point(0, 15 * WINDOW_WIDTH / 16), cv::Point(WINDOW_WIDTH, 15 * WINDOW_WIDTH / 16));
        DrawLine(rook, cv::Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), cv::Point(WINDOW_WIDTH / 4, WINDOW_WIDTH));
        DrawLine(rook, cv::Point(WINDOW_WIDTH / 2, 7 * WINDOW_WIDTH / 8), cv::Point(WINDOW_WIDTH / 2, WINDOW_WIDTH));
        DrawLine(rook, cv::Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), cv::Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH));

        cv::imshow("Window_name1", atom);
        cv::imshow("Window_name2", rook);
        cv::imwrite("ellipse_atom.jpg", atom);
        cv::imwrite("rook.jpg", rook);

        cv::waitKey();
}
