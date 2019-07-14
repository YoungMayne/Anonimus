#include <opencv2\opencv.hpp>
#include <opencv2\dnn.hpp>
#include <list>

#include "Anonimus.h"


int main() {

	std::string test = "../../Anonimus/data/";
	std::string jpg = ".jpg";


	const std::string config  = "../../Anonimus/data/deploy.prototxt";
	const std::string weights = "../../Anonimus/data/res10_300x300_ssd_iter_140000.caffemodel";
	const std::string video   = "../../Anonimus/data/prank.mp4";
	const std::string pic = "../../Anonimus/data/mface1.jpg";
	const std::string model_bin = "../../Anonimus/data/face-reidentification-retail-0095.bin";
	const std::string weights_xml = "../../Anonimus/data/face-reidentification-retail-0095.xml";
	
	Detector detector(config, weights, 0.4f);
	Classificator classificator(model_bin, weights_xml,0.6f);
	Anonimus anonimus(0, &detector, &classificator, new Blur());
	cv::Mat img1, img2, img3, img4, img5;
	img1 = cv::imread(pic);
	img2 = cv::imread(test+"mface"+jpg);
	img3 = cv::imread(test + "3" + jpg);
	img4 = cv::imread(test + "4" + jpg);
	img5 = cv::imread(test + "5" + jpg);
	classificator.addNewObject(img1);
	
	/*std::cout << classificator.findSimilliar(img1) << std::endl;
	std::cout << classificator.findSimilliar(img2) << std::endl;
	std::cout << classificator.findSimilliar(img3) << std::endl;
	std::cout << classificator.findSimilliar(img4) << std::endl;*/
	std::cout << classificator.findSimilliar(img1) << std::endl;
	std::cout << classificator.findSimilliar(img2) << std::endl;
	//anonimus.addNewObj(img1);




	if (!anonimus.joinTrack()) {
		std::cout << "Join error" << std::endl;
	}

	system("pause");
	return 0;
}
