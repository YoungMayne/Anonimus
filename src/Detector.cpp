#include "Detector.h"


Detector::Detector(const std::string& config, const std::string& weights, float confidence) {
	net = cv::dnn::readNet(config, weights);
	this->confidence = confidence;

	this->mean    = { 104.0, 177.0, 123.0 };
	this->size    = { 300, 300 };
	this->scale   = 1.0;
	this->swap_rb = false;
	this->crop    = false;
	this->depth   = 5;
}


void Detector::setProperties(const cv::Scalar& mean, const cv::Size& size, double scale, bool swap_rb, bool crop, int depth) {
	this->mean    = mean;
	this->size    = size;
	this->scale   = scale;
	this->swap_rb = swap_rb;
	this->crop    = crop;
	this->depth   = depth;
}


void Detector::setProperties(const std::string& config, const std::string& weights, float confidence) {
	net = cv::dnn::readNet(config, weights);
	this->confidence = confidence;
}


DetectedObj Detector::process(const cv::Mat& image) {
	DetectedObj result;

	net.setInput(cv::dnn::blobFromImage(image, scale, size, mean, swap_rb, crop, depth));

	cv::Mat detection = net.forward();
	cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

	DObj obj;
	for (int i = 0; i < detectionMat.rows; ++i) {
		obj.confidence = detectionMat.at<float>(i, 2);
		if (obj.confidence >= confidence) {
			int x1 = detectionMat.at<float>(i, 3) * image.size().width;
			int y1 = detectionMat.at<float>(i, 4) * image.size().height;
			int x2 = detectionMat.at<float>(i, 5) * image.size().width;
			int y2 = detectionMat.at<float>(i, 6) * image.size().height;

			if (x1 < 0 || x1 > image.size().width) {
				continue;
			}
			if (y1 < 0 || y1 > image.size().height) {
				continue;
			}
			if (x2 < 0 || x2 > image.size().width) {
				continue;
			}
			if (y2 < 0 || y2 > image.size().height) {
				continue;
			}

			obj.rect = { x1, y1, x2 - x1, y2 - y1 };
			result.push_back(obj);
		}
	}

	return result;
}
