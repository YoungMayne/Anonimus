#include "FaceDetector.h"
#include "ImageChanger.h"


class Anonimus {
public:
	Anonimus         (const std::string& video_path, FaceDetector* detector, ImageChanger* changer = new ImageChanger());
	Anonimus         (int camera, FaceDetector* detector, ImageChanger* changer = new ImageChanger());

	void setVideo    (const std::string& video_path);
	void setVideo    (int camera);

	void setDetector (FaceDetector* detector);
	void setChanger  (ImageChanger* changer);

	bool join        (int delay = 1);
private:
	FaceDetector*    detector;
	ImageChanger*    changer;
	cv::VideoCapture cap;
};