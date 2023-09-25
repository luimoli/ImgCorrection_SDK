#include "ColorCorrection.h"
#include "windows.h"
#include <opencv2/opencv.hpp>

void ColorCorrection::getParameter(std::string parameter_path)
{
    std::fstream f(parameter_path);
    std::vector<std::string> parameter; 
    std::string line; 
    while (getline(f, line))
    {
        parameter.push_back(line);
    }
    wb_gain[0] = std::stof(parameter[0]);
    wb_gain[1] = std::stof(parameter[1]);
    wb_gain[2] = std::stof(parameter[2]);
    ccm.at<float>(0, 0) = std::stof(parameter[3]);
    ccm.at<float>(0, 1) = std::stof(parameter[4]);
    ccm.at<float>(0, 2) = std::stof(parameter[5]);
    ccm.at<float>(1, 0) = std::stof(parameter[6]);
    ccm.at<float>(1, 1) = std::stof(parameter[7]);
    ccm.at<float>(1, 2) = std::stof(parameter[8]);
    ccm.at<float>(2, 0) = std::stof(parameter[9]);
    ccm.at<float>(2, 1) = std::stof(parameter[10]);
    ccm.at<float>(2, 2) = std::stof(parameter[11]);
}


void ColorCorrection::CorrectImage(cv::Mat& srcImage, std::string parameter_path)
{
    ColorCorrection::getParameter(parameter_path);
    //std::cout << wb_gain[0] << wb_gain[1] << wb_gain[2] << std::endl;
    cv::Mat image;
    srcImage.convertTo(image, CV_32F, (float(1.0) / float(255.0)));

    int rows = image.rows;
    int cols = image.cols;
    calibrated_image_linearBGR = image.clone();
    calibrated_image_sBGR = image.clone();
    cv::Mat calibrated_image_wb = image.clone();


    float overlimit = 1.0;
    float underlimit = 0.0;

    for (auto row = 0; row < rows; row++) {
        for (auto col = 0; col < cols; col++) {
            auto r = image.at<cv::Vec3f>(row, col)[2];
            auto g = image.at<cv::Vec3f>(row, col)[1];
            auto b = image.at<cv::Vec3f>(row, col)[0];

            r = r * wb_gain[0];
            g = g * wb_gain[1];
            b = b * wb_gain[2];
            r = std::min(overlimit, r);
            g = std::min(overlimit, g);
            b = std::min(overlimit, b);

            r = std::max(underlimit, r);
            g = std::max(underlimit, g);
            b = std::max(underlimit, b);

            //r = r * Y_gain;
            //g = g * Y_gain;
            //b = b * Y_gain;
            //r = std::min(overlimit, r);
            //g = std::min(overlimit, g);
            //b = std::min(overlimit, b);

            calibrated_image_wb.at<cv::Vec3f>(row, col)[2] = float(r);
            calibrated_image_wb.at<cv::Vec3f>(row, col)[1] = float(g);
            calibrated_image_wb.at<cv::Vec3f>(row, col)[0] = float(b);

            float temp_r, temp_g, temp_b;
            if (ccm.rows == 4)
            {
                temp_r = float(ccm.at<float>(0, 0) * r + ccm.at<float>(1, 0) * g + ccm.at<float>(2, 0) * b + ccm.at<float>(3, 0));
                temp_g = float(ccm.at<float>(0, 1) * r + ccm.at<float>(1, 1) * g + ccm.at<float>(2, 1) * b + ccm.at<float>(3, 1));
                temp_b = float(ccm.at<float>(0, 2) * r + ccm.at<float>(1, 2) * g + ccm.at<float>(2, 2) * b + ccm.at<float>(3, 2));
            }
            else
            {
                temp_r = float(ccm.at<float>(0, 0) * r + ccm.at<float>(0, 1) * g + ccm.at<float>(0, 2) * b);
                temp_g = float(ccm.at<float>(1, 0) * r + ccm.at<float>(1, 1) * g + ccm.at<float>(1, 2) * b);
                temp_b = float(ccm.at<float>(2, 0) * r + ccm.at<float>(2, 1) * g + ccm.at<float>(2, 2) * b);
                //temp_r = float(ccm.at<double>(0, 0) * r + ccm.at<double>(1, 0) * g + ccm.at<double>(2, 0) * b);
                //temp_g = float(ccm.at<double>(0, 1) * r + ccm.at<double>(1, 1) * g + ccm.at<double>(2, 1) * b);
                //temp_b = float(ccm.at<double>(0, 2) * r + ccm.at<double>(1, 2) * g + ccm.at<double>(2, 2) * b);
            }

            r = temp_r;
            g = temp_g;
            b = temp_b;
            r = std::min(overlimit, r);
            g = std::min(overlimit, g);
            b = std::min(overlimit, b);
            r = std::max(underlimit, r);
            g = std::max(underlimit, g);
            b = std::max(underlimit, b);

            calibrated_image_linearBGR.at<cv::Vec3f>(row, col)[2] = float(r);
            calibrated_image_linearBGR.at<cv::Vec3f>(row, col)[1] = float(g);
            calibrated_image_linearBGR.at<cv::Vec3f>(row, col)[0] = float(b);

            r = pow(r, (1 / 2.2));
            g = pow(g, (1 / 2.2));
            b = pow(b, (1 / 2.2));
            r = std::min(overlimit, r);
            g = std::min(overlimit, g);
            b = std::min(overlimit, b);
            r = std::max(underlimit, r);
            g = std::max(underlimit, g);
            b = std::max(underlimit, b);

            calibrated_image_sBGR.at<cv::Vec3f>(row, col)[2] = float(r);
            calibrated_image_sBGR.at<cv::Vec3f>(row, col)[1] = float(g);
            calibrated_image_sBGR.at<cv::Vec3f>(row, col)[0] = float(b);
        }
    }
    //cv::imwrite(R"(D:\Data\BK19862AAK00060_230214155726_wb.png)", calibrated_image_wb * 255.0);
    //if (do_exposure_gain)
    //{ 
    //    calibrated_image = calibrated_image * exposure_gain;
    //}

    calibrated_image_sBGR.convertTo(calibrated_image_sBGR_uint8, CV_8U, float(255.0));


    cv::cvtColor(calibrated_image_linearBGR, calibrated_image_lab, cv::COLOR_BGR2Lab);
    cv::cvtColor(calibrated_image_linearBGR, calibrated_image_xyz, cv::COLOR_BGR2XYZ);

    mean_image_BGR_uint8 = cv::mean(calibrated_image_sBGR_uint8(cv::Rect(160, 100, 400, 280)));
    mean_image_xyz = cv::mean(calibrated_image_xyz(cv::Rect(160, 100, 400, 280)));
    mean_image_lab = cv::mean(calibrated_image_lab(cv::Rect(160, 100, 400, 280)));

    float image_x = mean_image_xyz.val[0] / (mean_image_xyz.val[0] + mean_image_xyz.val[1] + mean_image_xyz.val[2]);
    float image_y = mean_image_xyz.val[1] / (mean_image_xyz.val[0] + mean_image_xyz.val[1] + mean_image_xyz.val[2]);

    mean_image_xyY = cv::Scalar(image_x, image_y, mean_image_xyz.val[1]);
    //cv::imwrite(R"(D:\Data\BK19862AAK00060_230214155726_test.png)", calibrated_image_sBGR_uint8(cv::Rect(160, 100, 400, 280)));


    //mean_image_BGR_uint8 = cv::mean(calibrated_image_sBGR_uint8);
    //mean_image_xyz = cv::mean(calibrated_image_xyz);
    //mean_image_lab = cv::mean(calibrated_image_lab);



}




