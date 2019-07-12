#include "..\include\Anonimus.h"



Anonimus::Anonimus(const std::string& video_path, FaceDetector* detector, ImageChanger* changer) {
	this->detector = detector;
	this->changer  = changer;
	cap.open(video_path);
}


Anonimus::Anonimus(int camera, FaceDetector * detector, ImageChanger * changer) {
	this->detector = detector;
	this->changer  = changer;
	cap.open(camera);
}


void Anonimus::setVideo(const std::string & video_path) {
	cap.open(video_path);
}


void Anonimus::setVideo(int camera) {
	cap.open(camera);
}


void Anonimus::setDetector(FaceDetector * detector) {
	this->detector = detector;
}


void Anonimus::setChanger(ImageChanger * changer) {
	this->changer = changer;
}


bool Anonimus::join(int delay) {
	if (!cap.isOpened()) {
		return false;
	}

	cv::Mat frame;
	cv::Mat anonim;

	cv::namedWindow("Anonimus");
	for (cap >> anonim, cap >> frame; !frame.empty(); cap >> frame) {
		cv::flip(frame, frame, 0);
		alignBrightness(frame);
		DetectedObj obj = detector->detect(frame);

		if (!obj.empty()) {
			anonim = cvMat_copy(frame);
			for (const DObj& item : obj) {
				changer->process(anonim, item.rect);
			}
		}

		cv::imshow("Anonimus", anonim);
		if (cv::waitKey(delay) == 27) {
			return true;
		}
	}

	return true;
}
