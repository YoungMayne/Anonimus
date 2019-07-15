#pragma once


#include "BaseDetector.h"

#include "Utils.h"





class Detector : public BaseDetector {
public:
	Detector            (const std::string& config, const std::string& weights, float confidence = 0.5f);

	void setProperties  (const cv::Scalar& mean, const cv::Size& size, double scale, bool swap_rb, bool crop, int depth);
	void setProperties  (const std::string& config, const std::string& weights, float confidence = 0.5f);

	DetectedObj process (const cv::Mat& image);
private:
	cv::dnn::Net        net;
	float               confidence;

	cv::Scalar          mean;
	cv::Size            size;
	double              scale;
	bool                swap_rb;
	bool                crop;
	int                 depth;
};