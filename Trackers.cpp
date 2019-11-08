#pragma once
#include <iostream>
#include <chrono>
#include <Vector>
#include <iomanip>
#include <opencv2/opencv.hpp>



class Timer {
public:
		std::chrono::time_point<std::chrono::steady_clock> start, end;
		std::chrono::duration<float>  duration;

		Timer() {
			start = std::chrono::high_resolution_clock::now();
		};

		~Timer() {
			end = std::chrono::high_resolution_clock::now();
			duration = end - start;
		};
};

class TimeTracker {
public:
	// This struct aims to make a tracker object that can be used to model time propagation
	int TrackerSize = 0;
	std::vector<float> TT;


	TimeTracker() {};

	void ReShape(int a) {
		this->TT.resize(a);
		this->TrackerSize = a;
	};

	void Append(float a) {
		TT[TrackerSize] = a;
		TrackerSize++;
	};

};

class TrajectoryTracker {
public:
	int TranslationSize, RotationSize;
	std::vector<cv::Mat> Rotation, Translation;
	cv::Mat FinalR, FinalT;

	TrajectoryTracker() {
		cv::Mat FinalT(cv::Size(3, 3), CV_64FC1, cv::Scalar(1));
		cv::Mat FinalR(cv::Size(3, 3), CV_64FC1, cv::Scalar(1));
		
	};

	void ReSize(int a) {
		Rotation.resize(a);
		RotationSize = a;
		Translation.resize(a);
		TranslationSize = a;
	};

	void AddTranslation(int time, cv::Mat val) {
		Translation[time] = val;
	}

	void AddRotation(int time, cv::Mat val) {
		Rotation[time] = val;
	}

	cv::Mat ComputeFinalRotation() {
		for (int i = 0; i < TranslationSize; i++) {
			this->FinalR *= this->Rotation[i];
		}
		return this->FinalR;
	};

	cv::Mat ComputeFinalTranslation() {
		for (int i = 0; i < this->TranslationSize; i++) {
			this->FinalT *= this->Translation[i];
		}
		return this->FinalT;
	};

};
