#pragma once


#include <opencv2/opencv.hpp>


inline float getBrightness(const cv::Mat& image) {
	cv::Mat color[3];

	cv::split(image, color);

	color[0] = color[0] * 0.299f;
	color[1] = color[1] * 0.587f;
	color[2] = color[2] * 0.114f;

	cv::Scalar summ = cv::sum(color[0] + color[1] + color[2]);

	return summ[0] / (255 * image.rows * image.cols) * 2;
}


inline cv::Mat cvMat_copy(const cv::Mat& mat) {
	cv::Mat result;
	mat.copyTo(result);
	return result;
}