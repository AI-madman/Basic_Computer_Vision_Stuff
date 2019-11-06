#pragma once
// This Section of the code imports the required code libraries.
#include <opencv2/opencv.hpp> // Includes the whole of the opencv code base for C++
#include <iostream>
#include <math.h>
#include "HelperCode.h"
#include <opencv2/sfm/fundamental.hpp>

using namespace cv;
using namespace std;



int main() {
	// This Section of code deals with declaring the variables that will be used later on in the code.
	cv::Mat  img1_gray, img2_gray, discriptor1, discriptor2; // This makes the matrix holders for the image values.
	int K1[3][3] = { {0,0,0},{0,0,0},{0,0,0} };// This needs to be setup to form the kamrea intrestic matrix K1
	int K2[3][3] = { {0,0,0}, {0,0,0}, {0,0,0} };// This needs to be setup to form the kamrea intrestic matrix K2
	vector<cv::KeyPoint> Keypoints1; // This will store the keypoint locations for the first image
	vector<cv::KeyPoint> Keypoints2; // This will store the keypoint locations for the seconed image
	vector<DMatch> matches;

	// This Section of Code deals with reading in the two inital images.
	cv::Mat img1 = imread("C:\\Users\\adbg044\\Desktop\\Visual Odometry papers\\Assets\\IMG_20191014_111003.jpg", 0);
	ImageLoadingChecker(img1);
	cv::Mat img2 = imread("C:\\Users\\adbg044\\Desktop\\Visual Odometry papers\\Assets\\IMG_20191014_111011.jpg", 0);
	ImageLoadingChecker(img2);

	
	// This section of code will convert the full color images into black and white images
	cvtColor(img1, img1_gray, COLOR_BGR2GRAY);
	ImageLoadingChecker(img1_gray);
	cvtColor(img2, img2_gray, COLOR_BGR2GRAY);
	ImageLoadingChecker(img2_gray);

	

	// This Section of the code deals with detecting features.
	Ptr<cv::FeatureDetector> Detector = cv::ORB::create();
	Detector->detect(img1_gray, Keypoints1);
	Detector->detect(img2_gray, Keypoints2);

	Ptr<cv::DescriptorExtractor> extractor = cv::ORB::create();
	(*extractor).compute(img1_gray, Keypoints1, discriptor1);
	(*extractor).compute(img2_gray, Keypoints2, discriptor2);

	// This section of the code deals with the matching the two keypoint sets
	BFMatcher matcher(NORM_L2);
	matcher.match(discriptor1, discriptor2, matches);

	// This section of the code computes the fundamental and essentail matixs
	cv::Mat Fundemental, Essentail, Rotation, Translation;
	cv::sfm::normalizedEightPointSolver(Keypoints1, Keypoints2, Fundemental);
	cv::sfm::essentialFromFundamental(Fundemental,K1 ,K2 ,Essentail);
	cv::sfm::motionFromEssential(Essentail,Rotation,Translation);

	cout << Rotation << "\n" << Translation << endl;

	return 0;
}

