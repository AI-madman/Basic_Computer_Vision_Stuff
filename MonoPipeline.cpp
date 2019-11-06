#pragma once
// This Section of the code imports the required code libraries.
#include <opencv2/opencv.hpp> // Includes the whole of the opencv code base for C++
#include <iostream>
#include <math.h>
#include "HelperCode.h"


int main() {
	// This Section of code deals with declaring the variables that will be used later on in the code.
	cv::Mat  img1_gray, img2_gray, discriptor1, discriptor2; // This makes the matrix holders for the image values.
	int K1[3][3] = { {0,0,0},{0,0,0},{0,0,0} };// This needs to be setup to form the kamrea intrestic matrix K1
	std::vector<cv::KeyPoint> Keypoints1, Keypoints2; // This will store the keypoint locations for the first image
	


	//TODO: Figure out what kind of example to put here






	return 0;
}