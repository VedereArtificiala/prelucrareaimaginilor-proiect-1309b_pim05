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

Mat changeBorderColor(Mat img) {
	Mat ret = img;
	for (int y = 0; y < img.size().height; y++) {
		for (int x = 0; x < img.size().width; x++) {
			Vec3b &color = img.at<Vec3b>(Point(y, x));
			if (color[0] == 255) {
				color[2] = 0;
				color[1] = 0;
			}
			img.at<Vec3b>(Point(x, y)) = color;
		}
	}
	return ret;
}
