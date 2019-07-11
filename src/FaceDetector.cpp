#include "FaceDetector.h"


FaceDetector::FaceDetector(const std::string& config, const std::string& weights, float confidence) {
	net = cv::dnn::readNet(config, weights);
	this->confidence = confidence;
}



DetectedObj FaceDetector::detect(const std::string& image_path) {
	return detect(cv::imread(image_path));
}



DetectedObj FaceDetector::detect(cv::Mat& image) {
	DetectedObj result;

	net.setInput(cv::dnn::blobFromImage(image, 1.0, { 300, 300 }, { 104.0, 177.0, 123.0 }));

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

			if (x1 < 0)  x1 = 0;
			if (y1 < 0)  y1 = 0;
			if (x2 > image.size().width)   x2 = image.size().width - 1;
			if (y2 > image.size().height)  y2 = image.size().height - 1;

			obj.rect = { x1, y1, x2 - x1, y2 - y1 };
			result.push_back(obj);
		}
	}

	return result;
}
