#include "ImageChanger.h"
#include "Detector.h"


class Anonimus {
public:
	Anonimus         (const std::string& video_path, Detector* detector, ImageChanger* changer = new ImageChanger());
	Anonimus         (int camera, Detector* detector, ImageChanger* changer = new ImageChanger());

	void setVideo    (const std::string& video_path);
	void setVideo    (int camera);

	void setDetector (Detector* detector);
	void setChanger  (ImageChanger* changer);

	bool join        (int delay = 1);
private:
	Detector*        detector;
	ImageChanger*    changer;
	cv::VideoCapture cap;
};