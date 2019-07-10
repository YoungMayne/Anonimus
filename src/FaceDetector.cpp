#include "FaceDetector.h"


FaceDetector::FaceDetector(const std::string& config, const std::string& weights, float confidence) {
	net = cv::dnn::readNetFromCaffe(config, weights);
	this->confidence = confidence;
}



DetectedObj FaceDetector::detect(const std::string& image_path) {
	return detect(cv::imread(image_path));
}



DetectedObj FaceDetector::detect(const cv::Mat& image) {
	DetectedObj result;

	cv::Mat frame = cvMat_copy(image);
	float brightness = getBrightness(frame);
	if (brightness < 0.7f) {
		frame.convertTo(frame, -1, 1.32, brightness * 250.f);
	}

	net.setInput(cv::dnn::blobFromImage(frame, 1.0, { 300, 300 }, { 104.0, 177.0, 123.0 }));
	cv::Mat detection = net.forward();

	cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

	for (uint32_t i = 0; i < detectionMat.rows; ++i) {
		float temp_confidence = detectionMat.at<float>(i, 2);
		if (temp_confidence >= confidence) {
			int x1 = detectionMat.at<float>(i, 3) * frame.size().width;
			int y1 = detectionMat.at<float>(i, 4) * frame.size().height;
			int x2 = detectionMat.at<float>(i, 5) * frame.size().width;
			int y2 = detectionMat.at<float>(i, 6) * frame.size().height;

			if (x1 > 0 && y1 > 0 && x2 < frame.size().width && y2 < frame.size().height) {
				result.push_back({ x1, y1, x2 - x1, y2 - y1 });
			}
		}
	}

	return result;
}
