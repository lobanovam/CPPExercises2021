#pragma once

#include <opencv2/highgui.hpp> // подключили часть библиотеки OpenCV, теперь мы можем работать с картинками (знаем про тип cv::Mat)

cv::Mat makeAllBlackPixelsBlue(cv::Mat image);

cv::Mat invertImageColors(cv::Mat image);

cv::Mat addBackgroundInsteadOfBlackPixels(cv::Mat object, cv::Mat background);

cv::Mat addBackgroundInsteadOfBlackPixelsLargeBackground(cv::Mat object, cv::Mat largeBackground);

cv::Mat multiplyUnicorns(cv::Mat object, cv::Mat largeBackground, int n);

cv::Mat randomColors(cv::Mat object);

cv::Mat NewFrame(std::vector<int>x, std::vector<int>y, cv:: Mat frame);

cv::Mat rFrame(std::vector<int>x, std::vector<int>y, cv:: Mat frame);
