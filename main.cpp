#include <opencv2/opencv.hpp>
void cartoonifyImage(cv::Mat srcColor, cv::Mat &dst,bool sketch)
{
	cv::Mat srcGray;
	cv::cvtColor(srcColor, srcGray, CV_BGR2GRAY);//GrayScale Image
	cv::medianBlur(srcGray, srcGray, 7);//Removing Noise From Image
	cv::Size size = srcColor.size();
	cv::Mat mask = cv::Mat(size, CV_8U);
	cv::Mat edges = cv::Mat(size, CV_8U);
	cv::Laplacian(srcGray, edges, CV_8U, 5);
	cv::threshold(edges, mask, 80, 255, CV_THRESH_BINARY_INV);
	if(sketch)
	{	//this is enough for sketch image
		cv::cvtColor(mask, dst, CV_GRAY2BGR);
		return;
	}
	else {
		//Median blur is more fast than bilateral,I would suggest medianBlur for realtiming
		cv::Mat tmp;
		cv::medianBlur(srcColor, tmp, 3);
		cv::medianBlur(tmp, srcColor, 3);

		srcColor.copyTo(dst, mask);
	}
	
	
}
int main()
{
	cv::VideoCapture cap(0);//Open VideoCapture Device
	cv::Mat frame;//frame
	cv::Mat dst;//Destination Frame
	
	for (;;)
	{
		cap >> frame;//Read frame from device
		cartoonifyImage(frame, dst,true);//Cartoonify image using function cartoonifyImage implemented in file
		cv::imshow("Sketch", dst);//show img
		
		cv::waitKey(100);//wait 100ms and then do for loop again
	}
}
