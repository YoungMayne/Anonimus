#pragma once

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include "Utils.h"


struct DObj {
    cv::Rect rect;
    float    confidence;
};

typedef	std::vector<DObj> DetectedObj;


class Detector {
public:
    Detector           (const std::string& config, const std::string& weights, float confidence = 0.5f);

    void setProperties (const cv::Scalar& mean, const cv::Size& size, double scale, bool swap_rb, bool crop, int depth);
    DetectedObj detect (cv::Mat& image);
    DetectedObj detect (const std::string& image_path);

private:
    cv::dnn::Net       net;
    float              confidence;

    cv::Scalar         mean;
    cv::Size           size;
    double             scale;
    bool               swap_rb;
    bool               crop;
    int                depth;
};
