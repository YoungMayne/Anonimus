#include <opencv2\opencv.hpp>
#include <opencv2\dnn.hpp>
#include <list>

#include "FaceDetector.h"
#include "Anonimus.h"


int main() {
	const std::string config = "../../Anonimus/data/deploy.prototxt";
	const std::string weights = "../../Anonimus/data/res10_300x300_ssd_iter_140000.caffemodel";
	const std::string video = "../../Anonimus/data/face.jpg";

	FaceDetector detector(config, weights, 0.4f);
	Anonimus anomimus(0, &detector, new Blur());
	
	if (!anomimus.join()) {
		std::cout << "Join error" << std::endl;
	}

	system("pause");
	return 0;
}
