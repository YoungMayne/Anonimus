#include <opencv2\opencv.hpp>
#include <opencv2\dnn.hpp>
#include <list>

#include "Detector.h"
#include "ImageChanger.h"


void loadFrames(cv::VideoCapture& cap, /* Classificator* classificator, */ double photo_delay = 0.5, int wait_delay = 1) {
	cv::namedWindow("Anonimus");
	clock_t start_time = clock();
	for (cv::Mat frame; cap >> frame, !frame.empty(); cap >> frame) {
		if ((double)(clock() - start_time) / CLOCKS_PER_SEC >= photo_delay) {
			/*classificator.addObject(frame);*/
			cv::rectangle(frame, { 0, 0, frame.size().width, frame.size().height }, { 0, 255, 0 }, 10);
			start_time = clock();
		}
		cv::imshow("Anonimus", frame);
		if (cv::waitKey(wait_delay) == 32) { //space = return			
			break;
		}
	}
	cv::destroyWindow("Anonimus");
}


int main() {
	const std::string config = "../../Anonimus/data/deploy.prototxt";
	const std::string weights = "../../Anonimus/data/res10_300x300_ssd_iter_140000.caffemodel";
	const std::string video = "../../Anonimus/data/prank.mp4";

	BaseDetector* detector = new Detector(config, weights, 0.4f);
	ImageChanger* changer = new Blur();

	while (true) {
		cv::VideoCapture cap;

		while (true/*ÂÛÁÎÐ ÍÀÑÒÐÎÅÊ*/) {
			//set changer
				/*delete changer;
				changer = new ...*/
			//
			//set video
					//cap.open(path or camera)
			//
			//set detector
					//delete detector;
					//detector = new ...
			//
			if (!cap.isOpened()) {
				//Error video/camera path
			}
		}
		//work
		cv::namedWindow("Anonimus");
		for (cv::Mat frame; cap >> frame, !frame.empty(); cap >> frame) {
			cv::Mat anonim = frame.clone();
			alignBrightness(frame);

			DetectedObj obj = detector->process(frame);
			if (!obj.empty()) {
				for (const DObj& item : obj) {
					changer->process(anonim, item.rect);
				}
			}
			else {
				cv::blur(anonim, anonim, { 64, 64 });
			}

			cv::imshow("Anonimus", anonim);
			if (cv::waitKey(1) == 27) {//escape
				cv::destroyWindow("Anonimus");
				break;
			}
		}
	}

	return 0;
}
