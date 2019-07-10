
#include <opencv2\opencv.hpp>
#include <opencv2\dnn.hpp>

#include <string>

int main() {
	std::string caffe_config = "C:/practice/Anonimus/data/deploy.prototxt";
	std::string caffe_weights = "C:/practice/Anonimus/data/res10_300x300_ssd_iter_140000.caffemodel";

	cv::dnn::Net net = cv::dnn::readNetFromCaffe(caffe_config, caffe_weights);

	cv::Mat image = cv::imread("C:/practice/Anonimus/data/1.jpg");
	cv::Mat resized;
	cv::resize(image, resized, { 300, 300 });
	cv::Mat blob = cv::dnn::blobFromImage(resized, 1.0, { 300, 300 }, { 104.0, 177.0, 123.0 }, false, false);

	net.setInput(blob, "data");
	cv::Mat detection = net.forward();

	cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

	for (uint32_t i = 0; i < detectionMat.rows; ++i) {
		float confidence = detectionMat.at<float>(i, 2);
		if (confidence > 0.5) {
			int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * image.size().width);
			int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * image.size().height);
			int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * image.size().width);
			int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * image.size().height);

			cv::Rect rect(x1, y1, x2 - x1, y2 - y1);
			//cv::rectangle(image, { x1, y1 }, { x2, y2 }, { 0, 255, 0 }, 2, 4);
			cv::GaussianBlur(image(rect), image(rect), { 0, 0 }, 15);
		}
	}


	cv::namedWindow("window");
	cv::imshow("window", image);
	cv::waitKey(0);

	return 0;
}