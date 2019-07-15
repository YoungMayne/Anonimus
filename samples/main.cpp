#include <opencv2\opencv.hpp>
#include <opencv2\dnn.hpp>
#include <list>

#include "Detector.h"
#include "ImageChanger.h"
#include "Classificator.h"


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


void loadFrames(Classificator* classificator, double photo_delay = 1.0, int wait_delay = 1) {
	cv::VideoCapture cap(0);
	cv::namedWindow("Press 'space' for return");
	clock_t start_time = clock();
	for (cv::Mat frame; cap >> frame, !frame.empty(); cap >> frame) {
		if ((double)(clock() - start_time) / CLOCKS_PER_SEC >= photo_delay) {
			classificator->addObject(frame);
			cv::rectangle(frame, { 0, 0, frame.size().width, frame.size().height }, { 0, 255, 0 }, 50);
			start_time = clock();
		}
		cv::imshow("Press 'space' for return", frame);
		if (cv::waitKey(wait_delay) == 32) { //space = return			
			break;
		}
	}
	cv::destroyWindow("Press 'space' for return");
}


int main(int argc, char** argv) {
	const std::string config  = "../../Anonimus/data/deploy.prototxt";
	const std::string weights = "../../Anonimus/data/res10_300x300_ssd_iter_140000.caffemodel";
	const std::string bin     = "../../Anonimus/data/";
	const std::string xml     = "../../Anonimus/data/";

	BaseDetector*    detector;
	ImageChanger*    changer;
	cv::VideoCapture cap;

	if (std::strcmp(argv[2], "classificator") == 0) {
		detector = new Classificator(bin, xml, config, weights);
		changer = getChangerFromName(argv[3], argv[4]);
		loadFrames((Classificator*)detector);
	}
	else if (std::strcmp(argv[2], "detector") == 0) {
		detector = new Detector(config, weights);
		changer = getChangerFromName(argv[3], "");
	}
	else {
		return -1;
	}


	if (std::strcmp(argv[1], "0") == 0) {
		cap.open(0);
	}
	else {
		cap.open(argv[1]);
	}
	if (!cap.isOpened()) {
		return -1;
	}

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

	delete detector;
	delete changer;
	//run menu
	return 0;
}
