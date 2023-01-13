#include "Operatii.h"
using namespace cv;
int main() {
	string image_path = samples::findFile("picior.jpg");
	Mat color = imread(image_path, IMREAD_COLOR),
		grayScale = imread(image_path, IMREAD_GRAYSCALE),
		binary = Mat(grayScale.size().height, grayScale.size().width, CV_8UC1, BinaryImage(grayScale.data, grayScale.size().width, grayScale.size().height, 170, 255)),
		thrsh, morph, kernel,
		interiors_8u, norm_components, components,
		final_markers, in_rgb, final_markers_8u,
		result;;
	
	imshow("", color);

	threshold(binary, thrsh, 100, 255, THRESH_BINARY);
	bitwise_not(thrsh, thrsh);

	kernel = getStructuringElement(MORPH_ELLIPSE, Size(50, 50));
	morphologyEx(thrsh, morph, MORPH_OPEN, kernel);

	Mat dilated(binary.rows, binary.cols, CV_8UC1);
	morphologyEx(morph, dilated, MORPH_DILATE, kernel);

	Mat distance(binary.rows, binary.cols, CV_8UC1);
	distanceTransform(morph, distance, DIST_L2, 5);
	normalize(distance, distance, 1, 0, NORM_INF);

	Mat interiors(binary.rows, binary.cols, CV_8UC1);
	double min, max;
	minMaxLoc(distance, &min, &max, NULL, NULL);
	threshold(distance, interiors, 0.05 * max, 255, THRESH_BINARY);

	interiors.convertTo(interiors_8u, CV_8U);
	int labels = connectedComponents(interiors_8u, components, 8);
	normalize(components, norm_components, 0, 255, NORM_MINMAX, CV_8U);
	norm_components.convertTo(norm_components, CV_8UC1);

	dilated.setTo(0, norm_components);

	final_markers = norm_components + 1;
	final_markers.setTo(0, dilated);

	cvtColor(binary, in_rgb, COLOR_GRAY2RGB);
	final_markers.convertTo(final_markers, CV_32SC1);
	watershed(in_rgb, final_markers);
	in_rgb.setTo(0, final_markers == -1);
	imshow("Identificare Tumori", in_rgb);

	final_markers.convertTo(final_markers_8u, CV_8U);
	bitwise_not(final_markers_8u, final_markers_8u);

	result = Mat::zeros(final_markers.size(), CV_8UC3);
	for (int i = 0; i < final_markers.rows; i++)
	{
		for (int j = 0; j < final_markers.cols; j++)
		{
			int index = final_markers.at<int>(i, j);
			if (index > 0 && index <= static_cast<int>(labels))
			{
				result.at<Vec3b>(i, j) = (165, 232, 154);
			}
		}
	}

	imshow("Rezultat Final", result);
	waitKey(0);
	return 0;
}
