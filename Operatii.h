#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;



unsigned char* BinaryImage(unsigned char* img, int w, int h, double th, double maxVal)
{
	unsigned char* result = new unsigned char[w*h];
	Mat inMat(h, w, CV_8UC1, img);
	Mat binaryMat(h, w, CV_8UC1, result);
	threshold(inMat, binaryMat, th, maxVal, cv::THRESH_BINARY);
	return result;
}

unsigned char* gaussianBlur(unsigned char* img, int w, int h)
{
	unsigned char* result = new unsigned char[w * h];

	Mat inMat(h, w, CV_8UC1, img);
	Mat outMat;
	GaussianBlur(inMat, outMat, Size(3,3), 3);
	Mat absMat(h, w, CV_8UC1, result);
	convertScaleAbs(outMat, absMat);
	return result;
}

unsigned char* DetectorMuchii(unsigned char* img, int w, int h)
{
	unsigned char* result = new unsigned char[w * h];
	Mat inMat(h, w, CV_8UC1, img);
	Mat outMat;
	Mat kernel = (Mat_<char>(3, 3) << -2, -1, 0, -1, 0, 1, 0, 1, 2);
	filter2D(inMat, outMat, inMat.depth(), kernel);
	Mat absMat(h, w, CV_8UC1, result);
	convertScaleAbs(outMat, absMat);
	return result;
}

void filled(Mat img) {
	Mat ret;
	Point seed(0,0);
	//floodFill(img, seed, Scalar(100));
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			unsigned char pixel = img.at<uchar>(i, j);
			if (pixel == 0 && (j - 50) > 0 && (j + 50) < img.cols && img.at<uchar>(i, j - 50) == 255 && img.at<uchar>(i, j + 50) == 255) {
				
			}
		}
	}
}



