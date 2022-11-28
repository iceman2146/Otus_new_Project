#include "image_combine.h"
#include <vector>
#include <iostream>

void GetSomeImages_andMerge(const cv::Mat& Image_RGB, const cv::Mat& Image_Alpha, cv::Mat& Image_RGBA)
{
	//Image_RGB.copyTo()
	cv::Size Image_Size = cv::Size(Image_RGB.cols, Image_RGB.rows);
	//CV_Assert(Image_RGB.rows == Image_Alpha.rows && Image_RGB.cols == Image_Alpha.cols);
	//CV_Assert(Image_RGB.channels() == Image_Alpha.channels());
	if (Image_RGB.rows != Image_Alpha.rows || Image_RGB.cols != Image_Alpha.cols)
	{
		cv::resize(Image_RGB, Image_Alpha, Image_Size);

	}
	//std::cout <<Image_RGB.TYPE_MASK<< Image_RGB.channels()<<std::endl;
	//std::cout << Image_Alpha.channels() << std::endl;
	//const int channels = Image_RGB.channels();

	//cv::resize(Image_RGB, Image_RGBA, Image_Size);
   // 
	//cv::cvtColor()
	//cv::cvtColor(Image_RGBA, Image_RGBA, cv::COLOR_BGR2RGBA);//ÃÎÒÎÂÎ:)))
	cv::resize(Image_RGB, Image_RGBA, Image_Size);
	std::vector<cv::Mat> srcChannels;
	std::vector<cv::Mat> AlphaChannels;
	std::vector<cv::Mat> dstChannels;
	cv::split(Image_RGB, srcChannels);
	cv::split(Image_Alpha, AlphaChannels);
	dstChannels.push_back(srcChannels[0]);
	dstChannels.push_back(srcChannels[1]);
	dstChannels.push_back(srcChannels[2]);
	
	//cv::cvtColor(Image_Alpha, Image_Alpha, cv::COLOR_RGBA2GRAY);
	dstChannels.push_back(AlphaChannels[0]);
	cv::merge(dstChannels, Image_RGBA);
	//cv::imwrite("C://test//testttt.png", Image_RGBA);


}
//cv::Mat CombineToRgba(const cv::Mat& Image_RGB, const cv::Mat& Image_Alpha);
