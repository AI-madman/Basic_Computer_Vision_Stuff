#include <opencv2/opencv.hpp> // Includes the whole of the opencv code base for C++
#include <iostream>
#include "HelperCode.h"

int main() {
	cv::Mat Frame1, Frame2, Frame1Gray, Frame2Gray;
	cv::VideoCapture Capture;
	Capture.open(0);
	if (!Capture.isOpened()) {
		std::cerr << "Can Not Open Video File\n";
		return 1;
	};
	Capture.read(Frame1);
	cv::cvtColor(Frame1, Frame2, cv::COLOR_BayerBG2BGR);

	while (true) {
		Capture.read(Frame2);
		if (Frame2.empty()) {
			break;
		};
		cv::cvtColor(Frame2, Frame2Gray, cv::COLOR_BGR2GRAY);
		//cv::Mat	flow(Frame1Gray.size(), CV_32FC2);

		cv::Mat flow(Frame1Gray.size(), CV_32FC2);
		calcOpticalFlowFarneback(Frame1Gray, Frame2Gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);

		// visualization
		cv::Mat flow_parts[2];
		cv::split(flow, flow_parts);
		cv::Mat magnitude, angle, magn_norm;
		cartToPolar(flow_parts[0], flow_parts[1], magnitude, angle, true);
		cv::normalize(magnitude, magn_norm, 0.0f, 1.0f, cv::NORM_MINMAX);
		angle *= ((1.f / 360.f) * (180.f / 255.f));

		//build hsv image
		cv::Mat _hsv[3], hsv, hsv8, bgr;
		_hsv[0] = angle;
		_hsv[1] = cv::Mat::ones(angle.size(), CV_32F);
		_hsv[2] = magn_norm;
		cv::merge(_hsv, 3, hsv);
		hsv.convertTo(hsv8, CV_8U, 255.0);
		cv::cvtColor(hsv8, bgr, cv::COLOR_HSV2BGR);
		cv::imshow("frame2", bgr);

		Frame1Gray = Frame2Gray;
	};
	return 0;
}