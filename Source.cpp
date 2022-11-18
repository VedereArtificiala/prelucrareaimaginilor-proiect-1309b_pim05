#include "Operatii.h"

int main() {
	string image_path = samples::findFile("23501-knee-x-ray.jpg");
	Mat color = imread(image_path, IMREAD_COLOR), 
		grayScale = imread(image_path, IMREAD_GRAYSCALE), 
		blurred = Mat(grayScale.size().height, grayScale.size().width, CV_8UC1, gaussianBlur(grayScale.data, grayScale.size().width, grayScale.size().height)),
		binary = Mat(blurred.size().height, blurred.size().width, CV_8UC1,BinaryImage(blurred.data, blurred.size().width, blurred.size().height, 115, 255)),
		muchii = Mat(binary.size().height, binary.size().width, CV_8UC1, DetectorMuchii(binary.data, binary.size().width, binary.size().height)), dest;
	imshow("Imagine Color", color);
	imshow("Imagine Grayscale", grayScale);
	imshow("Imagine Binarizata", binary);
	imshow("Imagine Blurata", blurred);
	imshow("Imagine cu Muchii", muchii);

	// Wait for any keystroke
	waitKey(0);
	return 0;
}