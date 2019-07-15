#pragma once

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>


class Classificator {
public:
    Classificator(const std::string& bin_path, const std::string& xml_path, const float conf = 0.5f);

    void addNewObject(const cv::Mat& obj);
    bool findSimilliar(const cv::Mat& faceFrame);




    void testfunc(const cv::Mat& test) {
        /*auto blob = cv::dnn::blobFromImage(test, 0, cv::Size(128, 128), { 0,0,0 });
        net.setInput(blob);
        cv::Mat res = net.forward();
        res = res.reshape(1, 1);*/


        cv::Mat res(1, 5, CV_32F);
        std::cout << res.rows << res.cols << std::endl;
        res.at<float>(0, 0) = 4;
        res.at<float>(0, 1) = 1;
        res.at<float>(0, 2) = 2;
        res.at<float>(0, 3) = 3;
        res.at<float>(0, 4) = 4;
        std::cout << std::endl << "---CALC NORM---" << std::endl;
        double norm = 0;
        for (int i = 0; i < res.cols; i++) {
            std::cout << "a[" << i << "] = " << res.at<float>(0, i) << ", a[i]*a[i] = " << static_cast<double>(res.at<float>(0, i))*static_cast<double>(res.at<float>(0, i)) << " /// ";
            norm += static_cast<double>(res.at<float>(0, i))*static_cast<double>(res.at<float>(0, i));
            std::cout << "NORM[" << i << "] = " << norm << std::endl;;
        }
        norm = sqrt(norm);
        std::cout << std::endl << "---NORMALAZING---" << std::endl;
        for (int i = 0; i < res.cols; i++) {
            std::cout << res.at<float>(0, i) <<" / "<< norm << " = ";
            res.at<float>(0, i) = static_cast<float> ((static_cast<double> (res.at<float>(0, i)) / norm));
            std::cout << res.at<float>(0, i) << std::endl;
        }
        std::cout << std::endl << "---CALCULATE NORM AFTER NORMALAZING---" << std::endl;
        double norm1 = 0;
        for (int i = 0; i < res.cols; i++) {
            std::cout << "a[" << i << "] = " << res.at<float>(0, i) << ", a[i]*a[i] = " << static_cast<double>(res.at<float>(0, i))*static_cast<double>(res.at<float>(0, i)) << " /// ";
            norm1 += static_cast<double>(res.at<float>(0, i))*static_cast<double>(res.at<float>(0, i));
            std::cout << "NORM[" << i << "] = " << norm1 << std::endl;;
        }
        norm1 = sqrt(norm1);
    }

private:
    cv::dnn::Net net;
    std::vector<cv::Mat> baseObjects;
    float conf;


    double getNorm(const cv::Mat& vec);
    void normalize(cv::Mat& vec);
    float scalarProduct(const cv::Mat& vec1, const cv::Mat& vec2);
};
