#pragma once


#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>


struct DetectedObj {
	std::vector<cv::Rect> rects;
};


class FaceDetector {
public:
	FaceDetector(const std::string& caffe_config, const std::string& caffe_weights, float confidence = 0.5f);

	DetectedObj detect(const std::string& image_path);
	DetectedObj detect(const cv::Mat& image);
private:
	cv::dnn::Net net;
	float confidence;
};