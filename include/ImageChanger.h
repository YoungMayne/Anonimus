#pragma once


#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

#include "Utils.h"


class ImageChanger {
public:
	virtual void process(cv::Mat& image, const cv::Rect& rect) const {};
};


class Blur : public ImageChanger {
public:
	Blur(int intensity = 15) {
		this->intensity = intensity;
	}

	void process(cv::Mat& image, const cv::Rect& rect) const {
		cv::GaussianBlur(image(rect), image(rect), { 0, 0 }, intensity);
	}
private:
	int intensity;
};


class Pixelize : public ImageChanger {
public:
	Pixelize(int size = 5) {
		this->size = size;
	}

	void process(cv::Mat& image, const cv::Rect& rect) const {
		cv::Mat rectIm = image(rect);
		cv::Size def   = image(rect).size();
		resize(rectIm, rectIm, { size,size }, 0, 0, cv::INTER_NEAREST);
		resize(rectIm, image(rect), def, 0, 0, cv::INTER_NEAREST);
	}
private:
	int size;
};


class PutImage : public ImageChanger {
public:
	PutImage(const cv::Mat& image) {
		this->image = cvMat_copy(image);
	}
	PutImage(const std::string& img_path, int flag = 1) {
		this->image = cv::imread(img_path, flag);
	}

	void process(cv::Mat& image, const cv::Rect& rect) const {
		cv::Mat resized;
		cv::resize(this->image, resized, { rect.width, rect.height });
		resized.copyTo(image(rect));
	}
private:
	cv::Mat image;
};


class Kek : public ImageChanger {
public:
	Kek() {}

	void process(cv::Mat& image, const cv::Rect& rect) const {
		cv::Rect left_rect  = { rect.x, rect.y, rect.width / 2, rect.height };
		cv::Rect right_rect = { rect.x + left_rect.width, rect.y, left_rect.width, rect.height };

		cv::Mat left = cvMat_copy(image(left_rect));
		cv::flip(left, left, 1);
		cv::resize(left, left, { right_rect.width, right_rect.height });
		left.copyTo(image(right_rect));
	}
};


class Rectangle : public ImageChanger {
public:
	Rectangle(const cv::Scalar& color, int thickness = 1, int lineType = 8, int shift = 0) {
		this->color     = color;
		this->thickness = thickness;
		this->lineType  = lineType;
		this->shift     = shift;
	}

	void process(cv::Mat& image, const cv::Rect& rect) const {
		cv::rectangle(image, rect, color, thickness, lineType, shift);
	}
private:
	cv::Scalar color;
	int        thickness;
	int        lineType;
	int        shift;
};