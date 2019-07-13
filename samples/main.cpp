#include <opencv2\opencv.hpp>
#include <opencv2\dnn.hpp>
#include <list>

#include "Anonimus.h"


int main() {
	const std::string config  = "../../Anonimus/data/deploy.prototxt";
	const std::string weights = "../../Anonimus/data/res10_300x300_ssd_iter_140000.caffemodel";
	const std::string video   = "../../Anonimus/data/prank.mp4";

	Detector detector(config, weights, 0.4f);
	Anonimus anonimus(video, &detector, new Blur());
	
	if (!anonimus.join()) {
		std::cout << "Join error" << std::endl;
	}

	system("pause");
	return 0;
}
