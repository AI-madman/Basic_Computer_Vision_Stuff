// This Section of the code imports the required code libraries.
#include <opencv2/opencv.hpp> // Includes the whole of the opencv code base for C++
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

float**  EssentialFromCorrospondance(){




	return *E;
}

int main() {
	// This Section of code deals with declaring the variables taht will be used later on in the code.
	cv::Mat  img1_gray, img2_gray, discriptor1, discriptor2; // This makes the matrix holders for the image values.
	int K1[3][3] = { {0,0,0},{0,0,0},{0,0,0} };// This needs to be setup to form the kamrea intrestic matrix K1
	int K2[3][3] = { {0,0,0}, {0,0,0}, {0,0,0} };// This needs to be setup to form the kamrea intrestic matrix K2
	vector<cv::KeyPoint> Keypoints1; // This will store the keypoint locations for the first image
	vector<cv::KeyPoint> Keypoints2; // This will store the keypoint locations for the seconed image
	vector<DMatch> matches;

	// This Section of Code deals with reading in the two inital images.
	cv::Mat img1 = imread("C:\\Users\\adbg044\\Desktop\\Visual Odometry papers\\Assets\\IMG_20191014_111003.jpg", 0);
	cv::Mat img2 = imread("C:\\Users\\adbg044\\Desktop\\Visual Odometry papers\\Assets\\IMG_20191014_111011.jpg", 0);

	if (img1.empty()) {
		cout << "Error: img1 did not load as expected" << endl;
	}
	if (img2.empty()) {
		cout << "Error: img2 did not load as expected" << endl;
	}
	// This section of code will convert the full color images into black and white images
	cvtColor(img1, img1_gray, COLOR_BGR2GRAY);
	cvtColor(img2, img2_gray, COLOR_BGR2GRAY);

	if (img1_gray.empty()) {
		cout << "Error: img1 did not convert to black and white as expected" << endl;
	}
	if (img2_gray.empty()) {
		cout << "Error: img2 did not convert to black and white as expected" << endl;
	}

	// This Section of the code deals with detecting features.
	SiftFeatureDector Detector;
	Detector.detect(img1_gray, Keypoints1);
	Detector.detect(img2_gray, Keypoints2);

	SiftDescriptorExtractor extractor;
	extractor.compute(img1_gray, Keypoints1, discriptor1);
	extractor.compute(img2_gray, Keypoints2, discriptor2);

	// This section of the code deals with the matching the two keypoint sets
	BFMatcher matcher(NORM_L2);
	matcher.match(discriptor1, discriptor2, matches);

	// This section of the code computes the fundamental and essentail matixs
	E= EssentialFromCorrospondance()
	F= FundamentalFromEssentail(E, K1, K2);
	rotation,translation=motionFromEssential(E);

	cout << rotation << "\n" << translation << endl;

	return 0;
}

//TODO: DEFINE ROTATION AND TRANSLATION AS VECTORS
//TODO: WRITE UP ESSENTAIL MATRIX ALGO
//TODO: GET SIFT TO WORK
//TODO: FIGURE OUT HOW MATCHES ARE STORED