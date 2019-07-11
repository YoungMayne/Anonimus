#include "FaceDetector.h"


FaceDetector::FaceDetector(const std::string& config, const std::string& weights, float confidence) {
	net = cv::dnn::readNetFromCaffe(config, weights);
	this->confidence = confidence;
}



DetectedObj FaceDetector::detect(const std::string& image_path) {
	return detect(cv::imread(image_path));
}



DetectedObj FaceDetector::detect(cv::Mat& image) {
	DetectedObj result;

	cv::Mat frame;
	float brightness = getBrightness(frame);
	if (brightness < 0.7f) {
		frame = cvMat_copy(image);
		frame.convertTo(frame, -1, 2.5, 1 / brightness * 20.f);
	}
	else {
		frame = cvMat_copy(image);
	}

	net.setInput(cv::dnn::blobFromImage(frame, 1.0, { 300, 300 }, { 104.0, 177.0, 123.0 }));
	cv::Mat detection = net.forward();

	cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

	for (uint32_t i = 0; i < detectionMat.rows; ++i) {
		DObj obj;
		obj.confidence = detectionMat.at<float>(i, 2);
		if (obj.confidence >= confidence) {
			int x1 = detectionMat.at<float>(i, 3) * frame.size().width;
			int y1 = detectionMat.at<float>(i, 4) * frame.size().height;
			int x2 = detectionMat.at<float>(i, 5) * frame.size().width;
			int y2 = detectionMat.at<float>(i, 6) * frame.size().height;

			float coef = 1.06f;
			if ((x1 /= coef) < 0) {
				x1 = 0;
			}
			if ((x2 *= coef) > frame.size().width) {
				x2 = frame.size().width - 1;
			}
			if ((y1 /= coef) < 0) {
				y1 = 0;
			}
			if ((y2 *= coef) > frame.size().height) {
				y2 = frame.size().height - 1;
			}

			obj.rect = { x1, y1, x2 - x1, y2 - y1 };
			result.push_back(obj);
		}
	}

	return result;
}
