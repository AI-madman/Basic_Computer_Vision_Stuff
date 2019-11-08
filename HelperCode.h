#pragma once
#include <iostream>
#include <chrono>
#include <Vector>
#include <iomanip>
#include <opencv2/opencv.hpp>
#include <fstream>

cv::VideoCapture LoadVideo(std::string  a) {
	cv::VideoCapture Capture(a);
	if (!Capture.isOpened()) {
		std::cerr << "Can Not Open Video File\n";
		return 1;
	};
	return Capture;
};

std::vector<cv::Scalar>  GenRandomColors(int a) {
	std::vector<cv::Scalar> colors;
	cv::RNG rng;

	for (int i = 0; i < a; i++) {
		int r = rng.uniform(0, 256);
		int b = rng.uniform(0, 256);
		int g = rng.uniform(0, 256);
		colors.push_back(cv::Scalar(r, g, b));
	};
	return 	colors;
	
};


int ImageLoadingChecker(cv::Mat img) {
	if (img.empty()) {
		std::cerr << "Failure To Correctly Load Image" << img;
		return 1;
	}
};

int CorrectCommoandLineInput(int a, int b) {
	// pass argc as b for this to work right.
	if (b != a) {
		std::cout << "Error Please make sure the right inputs where pased /n";
		return 1;
	}
};



void LoadImages(const std::string& strPathToSequence, std::vector<std::string>& vstrImageLeft,
	std::vector<std::string>& vstrImageRight, std::vector<double>& vTimestamps)
{
	std::ifstream fTimes;
	std::string strPathTimeFile = strPathToSequence + "/times.txt";
	fTimes.open(strPathTimeFile.c_str());
	while (!fTimes.eof())
	{
		std::string s;
		getline(fTimes, s);
		if (!s.empty())
		{
			std::stringstream ss;
			ss << s;
			double t;
			ss >> t;
			vTimestamps.push_back(t);
		}
	}

	std::string strPrefixLeft = strPathToSequence + "/image_0/";
	std::string strPrefixRight = strPathToSequence + "/image_1/";

	const int nTimes = vTimestamps.size();
	vstrImageLeft.resize(nTimes);
	vstrImageRight.resize(nTimes);

	for(int i = 0; i < nTimes; i++){
		std::stringstream ss;
		ss << std::setfill('0') << std::setw(6) << i;
		vstrImageLeft[i] = strPrefixLeft + ss.str() + ".png";
		vstrImageRight[i] = strPrefixRight + ss.str() + ".png";
	}
}