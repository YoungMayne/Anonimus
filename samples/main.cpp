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


void kek(cv::Mat& frame, const cv::Rect& rect) {
	cv::Rect left_rect(rect.x, rect.y, rect.width / 2, rect.height);
	cv::Rect right_rect = { rect.x + left_rect.width, rect.y, left_rect.width, rect.height };

	cv::Mat left = cvMat_copy(frame(left_rect));
	cv::flip(left, left, 1);
	cv::resize(left, left, { right_rect.width, right_rect.height });
	left.copyTo(frame(right_rect));
}


int main() {
	const std::string config  = "../../Anonimus/data/deploy.prototxt";
	const std::string weights = "../../Anonimus/data/res10_300x300_ssd_iter_140000.caffemodel";
	const std::string video   = "../../Anonimus/data/prank.mp4";

	FaceDetector detector(config, weights, 0.4f);

	cv::Mat frame;
	cv::Mat anonim;
	cv::VideoCapture cap(video);
	cap.set(cv::CAP_PROP_POS_FRAMES, 200);

	DetectedObj obj;
	cv::namedWindow("window");
	for (cap >> anonim, cap >> frame; !frame.empty(); cap >> frame) {
		float brightness = getBrightness(frame);
		if (brightness < 0.7f) {
			cv::Mat temp = cvMat_copy(frame);
			frame.convertTo(temp, -1, 1.0, 1 / brightness * 20.f);
			obj = detector.detect(temp);
		}
		else {
			obj = detector.detect(frame);
		}

		if (!obj.empty()) {
			anonim = cvMat_copy(frame);
			for (const DObj& item : obj) {
				kek(anonim, item.rect);
				//cv::rectangle(frame, item.rect, { 0, 255, 0 }, 3);
			}
		}

		cv::imshow("window", anonim);
		cv::waitKey(1);
	}

	return 0;
}
