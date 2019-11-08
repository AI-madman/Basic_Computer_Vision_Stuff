#pragma once
#include <iostream>
#include <chrono>
#include <Vector>
#include <iomanip>
#include <opencv2/opencv.hpp>




class StereoORB {
public:
	cv::Mat Fundemental, Essentail, Rotation, Translation, img1, img2, discriptor1, discriptor2, K1, K2;
	cv::Ptr<cv::FeatureDetector> Detector = cv::ORB::create();
	cv::Ptr<cv::DescriptorExtractor> extractor = cv::ORB::create();
	cv::BFMatcher matcher; 
	std::vector<cv::KeyPoint> Keypoints1, Keypoints2;
	std::vector<cv::DMatch> matches;
	

	 StereoORB() {}

	void SetKs(cv::Mat a, cv::Mat b) {
		this->K1 = a;
		this->K2 = b;
	}

	void SetIMG(cv::Mat Img1, cv::Mat Img2) {
		this->img1 = Img1;
		this->img2 = Img2;
	}

	void ComputeKeyPoints() {
		Detector->detect(this->img1, this->Keypoints1);
		Detector->detect(this->img2, this->Keypoints2);
	}

	void ComputeDiscriptors() {
		extractor->compute(this->img1, this->Keypoints1, this->discriptor1);
		extractor->compute(this->img2, this->Keypoints2, this->discriptor2);
	}

	void ComputeMatrixs() {
		cv::sfm::normalizedEightPointSolver(this->Keypoints1, this->Keypoints2, this->Fundemental);
		cv::sfm::essentialFromFundamental(this->Fundemental, this->K1, this->K2, this->Essentail);
		cv::sfm::motionFromEssential(this->Essentail, this->Rotation, this->Translation);
	}

	void PrintMotion() {
		std::cout << "The Rotation is:\t " << this->Rotation << "\n";
		std::cout << "The Translation is:\t " << this->Translation << "\n";
	}

	void FindMatches() {
		matcher.match(this->discriptor1, this->discriptor2, this->matches);
	}
};


class  MonoORB {
	cv::Mat Fundemental, Essentail, Rotation, Translation, img1, img2, K1, discriptor1, discriptor2;
	cv::Ptr<cv::FeatureDetector> Detector = cv::ORB::create();
	cv::Ptr<cv::DescriptorExtractor> extractor = cv::ORB::create();
	cv::BFMatcher matcher;
	std::vector<cv::KeyPoint> Keypoints1, Keypoints2;
	std::vector<cv::DMatch> matches;

	MonoORB() {	};

	void SetIMG(cv::Mat Img1, cv::Mat Img2) {
		this->img1 = Img1;
		this->img2 = Img2;
	};

	void SetK(cv::Mat a) {
		K1 = a;
	};

	void ComputeKeyPoints() {
		Detector->detect(this->img1, this->Keypoints1);
		Detector->detect(this->img2, this->Keypoints2);
	};

	void ComputeDiscriptors() {
		extractor->compute(this->img1, this->Keypoints1, this->discriptor1);
		extractor->compute(this->img2, this->Keypoints2, this->discriptor2);
	}

	void ComputeMatrixs() {
		cv::sfm::normalizedEightPointSolver(this->Keypoints1, this->Keypoints2, this->Fundemental);
		cv::sfm::essentialFromFundamental(this->Fundemental, this->K1, this->K1, this->Essentail);
		cv::sfm::motionFromEssential(this->Essentail, this->Rotation, this->Translation);
	}

	void PrintMotion() {
		std::cout << "The Rotation is:\t " << this->Rotation << "\n";
		std::cout << "The Translation is:\t " << this->Translation << "\n";
	}
};