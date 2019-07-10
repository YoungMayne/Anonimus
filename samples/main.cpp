#include <opencv2\opencv.hpp>
#include <opencv2\dnn.hpp>

#include "FaceDetector.h"


int main() {
	std::string caffe_config = "../../Anonimus/data/deploy.prototxt";
	std::string caffe_weights = "../../Anonimus/data/res10_300x300_ssd_iter_140000.caffemodel";

	cv::Mat image = cv::imread("../../Anonimus/data/1.jpg");

	FaceDetector detector(caffe_config, caffe_weights);

	DetectedObj obj = detector.detect(image);
	for (const auto& rect : obj.rects) {
		cv::rectangle(image, rect, { 0, 255, 0 }, 3);
	}


	cv::namedWindow("window");
	cv::imshow("window", image);
	cv::waitKey(0);

	return 0;
}