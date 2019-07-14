#include "..\include\Anonimus.h"



Anonimus::Anonimus(const std::string& video_path, Detector* detector, ImageChanger* changer) {
	this->detector = detector;
	this->changer  = changer;
	cap.open(video_path);
}


Anonimus::Anonimus(int camera, Detector * detector, ImageChanger * changer) {
	this->detector = detector;
	this->changer  = changer;
	cap.open(camera);
}
Anonimus::Anonimus(int camera, Detector* detector, Classificator* classificator, ImageChanger* changer) {
	this->detector = detector;
	this->classificator = classificator;
	this->changer = changer;
	cap.open(camera);
}


void Anonimus::setVideo(const std::string & video_path) {
	cap.open(video_path);
}


void Anonimus::setVideo(int camera) {
	cap.open(camera);
}


void Anonimus::addNewObj(const cv::Mat& faceFrame) {
	classificator->addNewObject(faceFrame);
}

void Anonimus::setDetector(Detector * detector) {
	this->detector = detector;
}


void Anonimus::setChanger(ImageChanger * changer) {
	this->changer = changer;
}


void Anonimus::setClassificator(Classificator* classificator) {
	this->classificator = classificator;
}


bool Anonimus::join(int delay) {
	if (!cap.isOpened()) {
		return false;
	}

	cv::Mat frame;
	cv::Mat anonim;
	cv::namedWindow("Anonimus");

	for (cap >> frame; !frame.empty(); cap >> frame)	{
		anonim = cvMat_copy(frame);
		alignBrightness(frame);

		DetectedObj obj = detector->detect(frame);
		if (!obj.empty()) {
			for (const DObj& item : obj) {
				changer->process(anonim, item.rect);
			}
		}
		else {
			cv::blur(anonim, anonim, { 64, 64 });
		}

		cv::imshow("Anonimus", anonim);
		if (cv::waitKey(delay) == 27) {
			cv::destroyWindow("Anonimus");
			return true;
		}
	}

	return true;
}


bool Anonimus::joinTrack(int delay) {
	if (!cap.isOpened()) {
		return false;
	}

	cv::Mat frame;
	cv::Mat anonim;
	cv::namedWindow("Anonimus");

	for (cap >> frame; !frame.empty(); cap >> frame) {
		anonim = cvMat_copy(frame);
		alignBrightness(frame);

		DetectedObj obj = detector->detect(frame);
		if (!obj.empty()) {
			for (const DObj& item : obj) {
				cv::Mat crop = frame(item.rect);
				cv::imshow("kk", crop);
				if (classificator->findSimilliar(crop))
					changer->process(anonim, item.rect);
			}
		}
		else {
			//cv::blur(anonim, anonim, { 64, 64 });
		}

		cv::imshow("Anonimus", anonim);
		if (cv::waitKey(delay) == 27) {
			cv::destroyWindow("Anonimus");
			return true;
		}
	}

	return true;
}