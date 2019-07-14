#include "Classificator.h"

Classificator::Classificator(const std::string& bin_path, const std::string& xml_path, const float conf){
	this->conf = conf;
	net = cv::dnn::readNet(bin_path, xml_path);
	net.setPreferableBackend(0);
	net.setPreferableTarget(0);
}


void Classificator::addNewObject(const cv::Mat& obj) {
	auto blob = cv::dnn::blobFromImage(obj, 1.0, cv::Size(128, 128), { 0,0,0 });
	net.setInput(blob);
	cv::Mat objFeatures = net.forward();
	objFeatures = objFeatures.reshape(1, 1);
	//::cout << objFeatures << std::endl << std::endl << std::endl;
	normalize(objFeatures);
	/*std::cout << objFeatures << std::endl;*/
	baseObjects.push_back(objFeatures.clone());
}


double Classificator::getNorm(const cv::Mat& vec) {
	double norm = 0;
	for (int i = 0; i < vec.cols; i++) {
		norm += vec.at<float>(0, i)*vec.at<float>(0, i);
	}
	return sqrt(norm);
}


void Classificator::normalize(cv::Mat& vec) {
	double norm = getNorm(vec);
	for (int i = 0; i < vec.cols; i++)
		vec.at<float>(0, i) = (vec.at<float>(0, i)/norm);
}


float Classificator::scalarProduct(const cv::Mat& vec1, const cv::Mat& vec2) {
	float res = 0;
	for (int i = 0; i < vec1.cols; i++) {
		res += vec1.at<float>(0, i)*vec2.at<float>(0, i);
	}
	return res;
}


bool Classificator::findSimilliar(const cv::Mat& faceFrame) {
	bool isObjFound = 0;


	float ff;
	
	auto blob = cv::dnn::blobFromImage(faceFrame, 1.0, cv::Size(128, 128), { 0,0,0 });
	net.setInput(blob);
	cv::Mat faceFeatures = net.forward();
	faceFeatures = faceFeatures.reshape(1, 1);
	normalize(faceFeatures);
	for (auto const& c : baseObjects) {
		ff = scalarProduct(faceFeatures, c);
		std::cout << ff << std::endl;
		if (ff > conf) {
			//std::cout << ;
			//std::cout << c << std::endl;
			//std::cout << faceFeatures << std::endl;
			isObjFound = 1;
			break;
		}
	}
	return isObjFound;
}
