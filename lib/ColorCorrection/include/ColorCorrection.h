// ColorCorrection.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。
//#pragma once
//#include <iostream>
// TODO: 在此处引用程序需要的其他标头。


#pragma once
#include "windows.h"
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#define MY_LIB_API __declspec(dllexport)


class MY_LIB_API ColorCorrection {
public:
	~ColorCorrection() = default;
	void CorrectImage(cv::Mat& srcImage, std::string parameter_path);

	cv::Mat calibrated_image_sBGR_uint8;
	
	cv::Scalar mean_image_BGR_uint8;
	cv::Scalar mean_image_lab;
	cv::Scalar mean_image_xyz;
	cv::Scalar mean_image_xyY;


	//std::string parameter_path = R"(D:\CodeC_Plus_Plus\ColorCorrection\ColorCorrection\parameter.txt)";

private:
	void getParameter(std::string parameter_path);
	cv::Mat ccm = cv::Mat_<float>(3, 3);
	float wb_gain[3];

	cv::Mat calibrated_image_linearBGR;
	cv::Mat calibrated_image_sBGR;
	cv::Mat calibrated_image_lab;
	cv::Mat calibrated_image_xyz;



	//cv::Mat ccm = (cv::Mat_<float>(3, 3) <<
	//	0.78858558, 0.14877791, - 0.01191134,
	//	-0.08375074, 1.2687146, - 0.08628086,
	//	0.05152792, 0.07755652, 0.8863206);

	//cv::Mat ccm = (cv::Mat_<double>(3, 3) <<
	//	0.78858558, -0.08375074, 0.05152792,
	//	0.14877791, 1.2687146, 0.07755652,
	//	-0.01191134, -0.08628086, 0.8863206);


	//cv::Mat ccm = (cv::Mat_<double>(3, 3) <<
	//	1.0, 0.0, 0.0,
	//	0.0, 1.0, 0.0,
	//	0.0, 0.0, 1.0);

	//float wb_gain[3] = { 4.02722348, 1.0, 3.46835962};


};
