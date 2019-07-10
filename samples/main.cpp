#include <opencv2\opencv.hpp>
#include <opencv2\dnn.hpp>

#include "FaceDetector.h"


int main() {
	const std::string config = "../../Anonimus/data/deploy.prototxt";
	const std::string weights = "../../Anonimus/data/res10_300x300_ssd_iter_140000.caffemodel";
	const std::string video = "../../Anonimus/data/";

	FaceDetector detector(config, weights);

	cv::Mat frame;
	cv::VideoCapture cap(video);
	cv::namedWindow("window");
	
	DetectedObj previous;
	int previous_detected = 0;
	for (cap >> frame; !frame.empty(); cap >> frame) {

		DetectedObj current = detector.detect(frame);
		for (const cv::Rect& rect : current) {
			cv::rectangle(frame, rect, { 0, 255, 0 }, 3);
		}
		for (const cv::Rect& rect : previous) {
			cv::rectangle(frame, rect, { 0, 255, 0 }, 3);
		}

		if (!current.empty()) {
			previous_detected = 15;
		}
		else if (previous_detected) {
			--previous_detected;
		}
		else {
			previous.clear();
		}

		cv::imshow("window", frame);
		cv::waitKey(1);
	}

	return 0;
}