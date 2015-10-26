#include <opencv2/opencv.hpp>
void cartoonifyImage(cv::Mat srcColor, cv::Mat &dst,bool sketch)
{
	cv::Mat srcGray;
	cv::cvtColor(srcColor, srcGray, CV_BGR2GRAY);
	cv::medianBlur(srcGray, srcGray, 7);
	cv::Size size = srcColor.size();
	cv::Mat mask = cv::Mat(size, CV_8U);
	cv::Mat edges = cv::Mat(size, CV_8U);
	cv::Laplacian(srcGray, edges, CV_8U, 5);
	cv::threshold(edges, mask, 80, 255, CV_THRESH_BINARY_INV);
	if(sketch)
	{
		cv::cvtColor(mask, dst, CV_GRAY2BGR);
		return;
	}
	else {
		cv::Mat tmp;
		cv::medianBlur(srcColor, tmp, 3);
		cv::medianBlur(tmp, srcColor, 3);

		srcColor.copyTo(dst, mask);
	}
	
	
}
int main()
{
	cv::VideoCapture cap(0);
	cv::Mat frame;
	cv::Mat dst;
	
	for (;;)
	{
		cap >> frame;
		cartoonifyImage(frame, dst,true);
		cv::imshow("Sketch", dst);
		std::cout << dst.channels();
		cv::waitKey(100);
	}
}
