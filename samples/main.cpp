#include <opencv2\opencv.hpp>
#include <opencv2\dnn.hpp>
#include <list>

#include "Anonimus.h"


int main() {
	const std::string config  = "../../Anonimus/data/pose_deploy.prototxt";
	const std::string weights = "../../Anonimus/data/haarcascade_frontalface_alt.xml";
	const std::string video   = "../../Anonimus/data/prank.mp4";

	Detector detector(config, weights, 0.4f);
	Anonimus anonimus(video, &detector, new Blur());
	
	if (!anonimus.join()) {
		std::cout << "Join error" << std::endl;
	}

	system("pause");
	return 0;
}
