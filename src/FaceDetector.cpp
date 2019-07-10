#include "FaceDetector.h"


FaceDetector::FaceDetector(const std::string& caffe_config, const std::string& caffe_weights, float confidence) {
	net = cv::dnn::readNetFromCaffe(caffe_config, caffe_weights);
	this->confidence = confidence;
}



DetectedObj FaceDetector::detect(const std::string& image_path) {
	return detect(cv::imread(image_path));
}



DetectedObj FaceDetector::detect(const cv::Mat& image) {
	DetectedObj result;

	cv::Mat resized;
	cv::resize(image, resized, { 300, 300 });
	cv::Mat blob = cv::dnn::blobFromImage(resized, 1.0, { 300, 300 }, { 104.0, 177.0, 123.0 }, false, false);

	net.setInput(blob);
	cv::Mat detection = net.forward();

	cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

	for (uint32_t i = 0; i < detectionMat.rows; ++i) {
		float temp_confidence = detectionMat.at<float>(i, 2);
		if (temp_confidence >= confidence) {
			int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * image.size().width);
			int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * image.size().height);
			int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * image.size().width);
			int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * image.size().height);

			result.rects.push_back({ x1, y1, x2 - x1, y2 - y1 });
		}
	}

	return result;
}
