
#include <opencv2\opencv.hpp>
#include <opencv2\dnn.hpp>

#include <string>

int main() {
	std::string caffe_config = "C:/practice/Anonimus/data/deploy.prototxt";
	std::string caffe_weights = "C:/practice/Anonimus/data/mobilenet-ssd.caffemodel";

	cv::dnn::Net net = cv::dnn::readNetFromCaffe(caffe_config, caffe_weights);

	cv::Mat image = cv::imread("C:/practice/Anonimus/data/lobachevsky.jpg");
	cv::Mat blob = cv::dnn::blobFromImage(image, 1.0, { 300, 300 }, (0, 0, 0), false, false);

	net.setInput(blob, "data");
	cv::Mat detection = net.forward("detection_out");
	
	cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

	for (uint32_t i = 0; i < detectionMat.rows; ++i) {
		float confidence = detectionMat.at<float>(i, 2);

		if (confidence > 0.2) {
			int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * image.size().width);
			int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * image.size().height);
			int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * image.size().width);
			int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * image.size().height);

			cv::rectangle(image, { x1, y1 }, { x2, y2 }, { 0, 255, 0 }, 2, 4);
		}
	}

	cv::namedWindow("window");
	cv::imshow("window", image);

	system("pause");
	return 0;
}