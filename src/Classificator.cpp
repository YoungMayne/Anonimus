#include "..\include\Classificator.h"


Classificator::Classificator(const std::string& bin, const std::string& xml, const std::string& config, const std::string& weights, float confidence) {
	this->confidence = confidence;
	this->detector   = new Detector(config, weights, confidence);
	this->net        = cv::dnn::readNet(bin, xml);

	net.setPreferableBackend(0);
	net.setPreferableTarget(0);
}


Classificator::~Classificator() {
	delete detector;
}


void Classificator::addObject(const cv::Mat& image) {
	for (const DObj& item : detector->process(image)) {
		net.setInput(cv::dnn::blobFromImage(image(item.rect), 1.0, cv::Size(128, 128), { 0, 0, 0 }));
		cv::Mat obj = net.forward().reshape(1, 1);
		normalize(obj);
		baseObjects.push_back(obj.clone());
	}
}


DetectedObj Classificator::process(const cv::Mat& image) {
	DetectedObj result;

	for (const DObj& item : detector->process(image)) {
		if (findSimilar(image(item.rect))) {
			result.push_back(item);
		}
	}

	return result;
}


bool Classificator::findSimilar(const cv::Mat& image) {
	net.setInput(cv::dnn::blobFromImage(image, 1.0, cv::Size(128, 128), { 0, 0, 0 }));
	cv::Mat faceFeatures = net.forward().reshape(1, 1);
	normalize(faceFeatures);

	for (const cv::Mat& mat : baseObjects) {
		if (scalar(faceFeatures, mat) > confidence) {
			return true;
		}
	}

	return false;
}
