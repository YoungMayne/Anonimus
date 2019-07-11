#include <opencv2\opencv.hpp>
#include <opencv2\dnn.hpp>
#include <list>

#include "FaceDetector.h"


void pixelize(cv::Mat& frame, const cv::Rect& rect, int size = 5) {
	cv::Mat rectIm = frame(rect);
	cv::Size def = frame(rect).size();
	resize(rectIm, rectIm, { size,size }, 0, 0, cv::INTER_NEAREST);
	resize(rectIm, frame(rect), def, 0, 0, cv::INTER_NEAREST);
}


void put_image(cv::Mat& frame, const cv::Mat& image, const cv::Rect& rect) {
	cv::Mat resized;
	cv::resize(image, resized, { rect.width, rect.height });
	resized.copyTo(frame(rect));
}


void prikolchik(cv::Mat& frame, const cv::Rect& rect) {
	cv::Mat temp = frame(rect);
}


int main() {
	const std::string config = "../../Anonimus/data/deploy.prototxt";
	const std::string weights = "../../Anonimus/data/res10_300x300_ssd_iter_140000.caffemodel";
	const std::string video = "../../Anonimus/data/prank.mp4";

	FaceDetector detector(config, weights);

	cv::Mat frame;
	cv::VideoCapture cap(0);
	cv::namedWindow("window");

	DetectedObj previous;
	for (cap >> frame; !frame.empty(); cap >> frame) {
		cv::flip(frame, frame, 1);

		DetectedObj current = detector.detect(frame);
		if (current.empty()) {
			for (const auto& item : previous) {
				put_image(frame, cv::imread("../../Anonimus/data/face.jpg"), item.rect);
			}
		}
		for (const auto& item : current) {
			//put_image(frame, cv::imread("../../Anonimus/data/face.jpg"), item.rect);
			prikolchik(frame, item.rect);
			previous = current;
		}

		cv::imshow("window", frame);
		cv::waitKey(1);
	}

	return 0;
}