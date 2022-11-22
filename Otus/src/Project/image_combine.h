#pragma once


#include <opencv2/opencv.hpp>



void GetSomeImages_andMerge(const cv::Mat& Image_RGB, const cv::Mat& Image_Alpha, cv::Mat& Image_RGBA);
//cv::Mat CombineToRgba(const cv::Mat& Image_RGB, const cv::Mat& Image_Alpha);
