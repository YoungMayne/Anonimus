#include <opencv2\opencv.hpp>
#include <opencv2\dnn.hpp>
#include <list>

#include "Detector.h"
#include "ImageChanger.h"


ImageChanger* getChangerFromName(const char* name, const char* image_path) {
	if (std::strcmp(name, "blur") == 0) {
		return new Blur();
	}
	if (std::strcmp(name, "pixelize") == 0) {
		return new Pixelize();
	}
	if (std::strcmp(name, "image") == 0) {
		return new PutImage(cv::imread(image_path));
	}
	if (std::strcmp(name, "kek") == 0) {
		return new Kek();
	}
	if (std::strcmp(name, "rectangle") == 0) {
		return new Rectangle({ 0, 255, 0 }, 3);
	}
}


void loadFrames(/* Classificator* classificator, */ double photo_delay = 0.5, int wait_delay = 1) {
	cv::VideoCapture cap(0);
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


int main(int argc, char** argv) {
	const std::string detector_config = "../../Anonimus/data/deploy.prototxt";
	const std::string detector_weights = "../../Anonimus/data/res10_300x300_ssd_iter_140000.caffemodel";

	BaseDetector* detector;
	ImageChanger* changer;
	cv::VideoCapture cap;

	if (std::strcmp(argv[1], "classificator") == 0) {
		const std::string classificator_config = "";
		const std::string classificator_weights = "";
		//detector = new Classificator
		changer = getChangerFromName(argv[2], argv[3]);
		loadFrames(/*&detector*/);
	}
	else if (std::strcmp(argv[1], "detector") == 0) {
		detector = new Detector(detector_config, detector_weights);
		changer = getChangerFromName(argv[2], "");
	}
	else {
		return -1;
	}

	cv::namedWindow("Anonimus");
	if (std::strcmp(argv[0], "0") == 0) {
		cap.open(0);
	}
	else {
		cap.open(argv[0]);
	}

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

	//run menu
	return 0;
}
