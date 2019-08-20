#include<opencv2/opencv.hpp>

int main()
{

	//【1】以灰度模式读取原始图像并显示
	cv::Mat src = cv::imread("H:\\black_white.jpg", 0);
	if (!src.data) 
		return false; 

	//【2】将输入图像延扩到最佳的尺寸，边界用0补充
	int m = cv::getOptimalDFTSize(src.rows);
	int n = cv::getOptimalDFTSize(src.cols);

	//在右边和下边扩展，将添加的像素初始化为0.
	cv::Mat padded;
	copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols, \
		cv::BORDER_CONSTANT, cv::Scalar::all(0));
	/*copyMakeBorder(
	src,dst,top,button,left,right,
	bordertType{
    BORDER_CONSTANT: 使用常数填充边界 (默认黑色即value = 0)
    BORDER_REPLICATE: 复制原图中最临近的行或者列。}
	Scalar,有BORDER_CONSTANT时表示边界值
	)*/

	//【3】为傅立叶变换的结果(实部和虚部)分配存储空间。
	//将planes数组组合合并成一个多通道的数组complexI
	cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
	//新建一个两页的array，其中第一页用扩展后的图像初始化，第二页初始化为0
	cv::Mat complexI;
	merge(planes, 2, complexI);
	//把两页合成一个2通道的mat


	//【4】进行就地离散傅里叶变换
	dft(complexI, complexI);
	//src,dst,默认flags为0表示正向变换，默认nonzeroRows为0

	//【5】将复数转换为幅值，即=> log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	split(complexI, planes); 
	// 将多通道数组complexI分离成几个单通道数组，planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
	//magnitude(src x实部,src y虚部,dst)
	cv::Mat magnitudeImage = planes[0];

	//【6】进行对数尺度(logarithmic scale)缩放
	magnitudeImage += cv::Scalar::all(1);
	log(magnitudeImage, magnitudeImage);//求自然对数

	//【7】剪切和重分布幅度图象限
	//若有奇数行或奇数列，进行频谱裁剪      
	magnitudeImage = magnitudeImage(cv::Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));
	//重新排列傅立叶图像中的象限，使得原点位于图像中心  
	//傅里叶变换之前要对源图像乘以（-1）^(x+y)进行中心化。
	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;
	cv::Mat q0(magnitudeImage, cv::Rect(0, 0, cx, cy));   // ROI区域的左上
	cv::Mat q1(magnitudeImage, cv::Rect(cx, 0, cx, cy));  // ROI区域的右上
	cv::Mat q2(magnitudeImage, cv::Rect(0, cy, cx, cy));  // ROI区域的左下
	cv::Mat q3(magnitudeImage, cv::Rect(cx, cy, cx, cy)); // ROI区域的右下
	//交换象限（左上与右下进行交换）
	cv::Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	//交换象限（右上与左下进行交换）
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//【8】归一化，用0到1之间的浮点值将矩阵变换为可视的图像格式
	normalize(magnitudeImage, magnitudeImage, 0, 1, CV_MINMAX);
	/*src,dst,归一化后的最小值，归一化的最大值，
	归一化类型NORM_MINMAX:数组的数值被平移或缩放到一个指定的范围，线性归一化*/

	//【9】显示效果图
	cv::namedWindow("频谱幅值", 0);
	cv::imshow("频谱幅值", magnitudeImage);
	cv::imwrite("频谱幅值.jpg", magnitudeImage);
	cv::waitKey();

	return 0;
}
//参考：https://blog.csdn.net/ubunfans/article/details/24787569