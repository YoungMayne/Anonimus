#pragma once


#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

#include "BaseDetector.h"
#include "Detector.h"
#include "Utils.h"


class Classificator : public BaseDetector {
public:
	Classificator(const std::string& bin, const std::string& xml, const std::string& config, const std::string& weights, float confidence = 0.5f);
	~Classificator();

	void addObject(const cv::Mat& image);

	DetectedObj process(const cv::Mat& image);
private:
	bool findSimilar(const cv::Mat& image);
private:
	cv::dnn::Net net;
	Detector* detector;
	float confidence;
	std::vector<cv::Mat> baseObjects;
};