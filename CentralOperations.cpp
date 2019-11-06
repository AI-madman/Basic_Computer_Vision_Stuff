#include<iostream>
#include<algorithm>
#include<fstream>
#include<iomanip>
#include<chrono>
#include<vector>
#include<string>
#include <opencv2/opencv.hpp>
#include "HelperCode.h"
#include "Trackers.cpp"
#include "VO.cpp"


void LoadImages(const std::string& strPathLeft, const std::string& strPathRight, const std::string& strPathTimes,
	std::vector<std::string>& vstrImageLeft, std::vector<std::string>& vstrImageRight, std::vector<double>& vTimeStamps);

int main(int argc, char** argv) {


	Timer TotalRunTime;
	CorrectCommoandLineInput(4, argc);

	// This section of code will make the image paths and the times at which they where taken
	std::vector<std::string> ImagePathLeft, ImagePathRight;
	std::vector<double> TimeStamps;
	LoadImages(std::string(argv[3]), ImagePathLeft, ImagePathRight, TimeStamps);
	const int NumberOfImages = ImagePathLeft.size();
	std::tuple<int> ImageSize[2];
	ImagePathLeft[0].size();
	cv::Mat K1, K2;

	// This Section Will make the Time Tracker
	std::vector<float> TimeTracker; 
	TimeTracker.resize(NumberOfImages);

	// Main Loop (the Real Deal)
	// SETTING THINGS UP

	cv::Mat LeftImage, RightImage;
	StereoORB ORB();
	ORB.Setks(K1, K2);
	TrajectoryTracker TT();
		for (int t = 0; t < NumberOfImages, t++;) {
		LeftImage = cv::imread(ImagePathLeft[t], cv::IMREAD_UNCHANGED);
		ImageLoadingChecker(LeftImage); 
		RightImage = cv::imread(ImagePathRight[t], cv::IMREAD_UNCHANGED);
		ImageLoadingChecker(RightImage);
		double tframe = TimeStamps[t];

		std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
		ORB.SetImg( LeftImage, RightImage);
		ORB.ComputeKeyPoints();
		ORB.ComputeDiscriptors();
		ORB.ComputeMatrixs();

		std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
		double RunTime = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count();
		TimeTracker[t] = RunTime;	
		
		TT.AddTranslation(t, ORB.Translation);
		TT.AddRotation(t, ORB.Rotation);

	}
	TotalRunTime.~Timer();

	//TODO: MAKE A STATISTICS ANALYSIS SECTION SOMEWHERE


	return 0;
}

