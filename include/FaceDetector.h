#pragma once


#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

#include "Utils.h"


typedef	std::vector<cv::Rect> DetectedObj;


class FaceDetector {
public:
	FaceDetector(const std::string& config, const std::string& weights, float confidence = 0.5f);

	DetectedObj detect(const std::string& image_path);
	DetectedObj detect(const cv::Mat& image);
private:
	cv::dnn::Net net;
	float confidence;
};