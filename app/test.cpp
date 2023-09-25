#include <iostream>
#include "ColorCorrection.h"
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	ColorCorrection cc = ColorCorrection();
	cv::Mat srcImage = cv::imread(R"(./BK19862AAK00060_230214155726.png)");

	// define file path of parameter
	std::string parameter_path = R"(./parameter.txt)";
	cc.CorrectImage(srcImage, parameter_path);

	// get corrected img
	cv::Mat img_sBGR = cc.calibrated_image_sBGR_uint8;
	cv::imwrite(R"(./BK19862AAK00060_230214155726_res.png)", img_sBGR);

	// get mean value
	//cout << cc.mean_image_BGR_uint8 << endl;
	cout << "sRGB: " << cc.mean_image_BGR_uint8.val[2] << "," << cc.mean_image_BGR_uint8.val[1] << "," << cc.mean_image_BGR_uint8.val[0] << endl;

	cout << "L*a*b: " << cc.mean_image_lab << endl;
	cout << "XYZ: " << cc.mean_image_xyz << endl;
	cout << "xyY: " << cc.mean_image_xyY << endl;



}
