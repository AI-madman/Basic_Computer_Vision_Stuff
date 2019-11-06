#include <opencv2/opencv.hpp> // Includes the whole of the opencv code base for C++
#include <iostream>
#include <math.h>
#include "HelperCode.h"

int main() {
	cv::Mat old_frame, old_gray, mask, img;
	std::vector<cv::Point2f> p0, p1, good_new;

	// Locate the conors in first frame
	Capture >> old_frame;
	cv::cvtColor(old_frame, old_gray, cv::COLOR_BGR2GRAY);
	cv::goodFeaturesToTrack(old_gray, p0, 100, 0.3, 7, cv::Mat(), 7, false, 0.04);

	// Make a mask to draw
	mask = cv::Mat::zeros(old_frame.size(), old_frame.type());

	while (true) {
		cv::Mat CurrentFrame, CurrentFrameGray;
		Capture >> CurrentFrame;
		if (CurrentFrame.empty()) {
			std::cout << "End of Video/n";
			break;
		};
		cv::cvtColor(CurrentFrame, CurrentFrameGray, cv::COLOR_BGR2GRAY);

		// The Fun Stuff
		std::vector<uchar> status;
		std::vector<float> error;
		cv::TermCriteria criteria = cv::TermCriteria((cv::TermCriteria::COUNT) + (cv::TermCriteria::EPS), 10, 0.03);
		cv::calcOpticalFlowPyrLK(old_gray, CurrentFrameGray, p0, p1, status, error, cv::Size(15, 15));
		
		for (int i = 0; i < p0.size(); i++) {
			if (status[i] == 1) {
				good_new.push_back(p1[i]);
				line(mask, p1[i], p0[i], colors[i], 2); // use the color function i made in HelperCode.h
				circle(CurrentFrame, p1[i], 5, colors[i], -1);
			};
		};

		cv::add(CurrentFrame, mask, img);
		cv::imshow("Frame", img);

		// Now update the previous frame and previous points
		old_gray = CurrentFrameGray.clone();
		p0 = good_new;
	};


	return 0;
}