#pragma once


#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>


struct DObj {
	cv::Rect rect;
	float    confidence;
};

typedef	std::vector<DObj> DetectedObj;


class BaseDetector {
public:
	virtual DetectedObj process(const cv::Mat& image) = 0;
};