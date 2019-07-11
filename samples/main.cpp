#include <opencv2\opencv.hpp>
#include <opencv2\dnn.hpp>
#include <list>

#include "FaceDetector.h"


bool the_same(const cv::Rect& rect1, const cv::Rect& rect2, float epsilon = 10.0f) {
	if (abs(rect1.x - rect2.x) < epsilon || abs(rect1.y - rect2.y) < epsilon || abs(rect1.width - rect2.width) < epsilon || abs(rect1.height - rect2.height) < epsilon) {
		return true;
	}
	return false;
}


void check(std::list<PObj>& list) {
	for (auto i = list.begin(); i != list.end(); ++i) {
		auto j = i;
		for (j++; j != list.end(); ++j) {
			if (the_same(i->rect, j->rect)) {
				list.erase(j--);
			}
		}
	}
}


int main() {
	const std::string config = "../../Anonimus/data/deploy.prototxt";
	const std::string weights = "../../Anonimus/data/res10_300x300_ssd_iter_140000.caffemodel";
	const std::string video = "../../Anonimus/data/prank.mp4";

	FaceDetector detector(config, weights, 0.3f);

	cv::Mat frame;
	cv::VideoCapture cap(video);
	cv::namedWindow("window");

	std::list<PObj> previous;
	int previous_detected = 0;
	bool skip = false;
	for (cap >> frame; !frame.empty(); cap >> frame) {

		if (!skip) {
			for (const auto& item : detector.detect(frame)) {
				PObj temp;
				temp.rect = item.rect;
				temp.draw = item.confidence * 20;
				previous.push_front(temp);
			}
			skip = true;
		}
		else {
			check(previous);
			skip = false;
		}

		for (auto item = previous.begin(); item != previous.end(); ++item) {
			if (item->draw) {
				--item->draw;
				cv::rectangle(frame, item->rect, { 0, 255, 0 }, 3);
			}
			if (!item->draw) {
				previous.erase(item--);
			}
		}

		cv::imshow("window", frame);
		cv::waitKey(1);
	}

	return 0;
}