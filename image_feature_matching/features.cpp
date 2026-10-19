#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Timer.h"

using namespace cv;
using namespace std;
int main(int argc, char* argv[]) {
	std::cout << "Program started" << std::endl;
	
	Timer myTimer;

	cv::Mat image1 = cv::imread("viewpoint_2/img2.ppm");
	cv::Mat image2 = cv::imread("viewpoint_2/img1.ppm");

	if (image1.empty()) {
		std::cerr << "Could not load image from image1.jpg" << std::endl;
		return -1;
	}
	if (image2.empty()) {
		std::cerr << "Could not load image from image2.jpg" << std::endl;
		return -1;
	}

	Ptr<SIFT> sift = SIFT::create();
	std::vector<cv::KeyPoint> keypoints1;
	cv::Mat descriptors1;
	std::vector<cv::KeyPoint> keypoints2;
	cv::Mat descriptors2;

	cv::Ptr<cv::DescriptorMatcher> matcher = cv::FlannBasedMatcher::create(); 

	
	sift->detectAndCompute(image1, cv::noArray(), keypoints1, descriptors1);
	std::cout << "Found " << keypoints1.size() << " features" << std::endl;

	sift->detectAndCompute(image2, cv::noArray(), keypoints2, descriptors2);
	std::cout << "Found " << keypoints2.size() << " features" << std::endl;

	

	std::vector<std::vector<cv::DMatch>> matches;
	matcher->knnMatch(descriptors1, descriptors2, matches, 2);

	
	std::vector<cv::DMatch> goodMatches;
	std::vector<cv::Point2f> goodPts1, goodPts2;
	for (const auto& match : matches) {
		if (match[0].distance < 0.8 * match[1].distance) {
			goodMatches.push_back(match[0]);
			goodPts1.push_back(keypoints1[match[0].queryIdx].pt);
			goodPts2.push_back(keypoints2[match[0].trainIdx].pt);
		}
	}

	
	std::vector<unsigned char> inliers;
	myTimer.reset();
	cv::Mat H = cv::findHomography(goodPts2, goodPts1, inliers, cv::RANSAC, 1000);
	double timeTaken = myTimer.read();
	int numInliers = cv::countNonZero(inliers);
	
	double matrix_data[9];

	// Read the matrix data from the file
	std::string line;
	int index = 0;
	std::ifstream file("viewpoint_2/H1to2p");
	while (std::getline(file, line) && index < 9) {
		std::istringstream iss(line);
		double value;
		while (iss >> value && index < 9) {
			matrix_data[index++] = value;
		}
	}

	cv::Mat trueH(3, 3, CV_64F);
	trueH.at<double>(0, 0) = matrix_data[0];
	trueH.at<double>(0, 1) = matrix_data[1];
	trueH.at<double>(0, 2) = matrix_data[2];
	trueH.at<double>(1, 0) = matrix_data[3];
	trueH.at<double>(1, 1) = matrix_data[4];
	trueH.at<double>(1, 2) = matrix_data[5];
	trueH.at<double>(2, 0) = matrix_data[6];
	trueH.at<double>(2, 1) = matrix_data[7];
	trueH.at<double>(2, 2) = matrix_data[8];
	
	double error = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			error += abs(H.at<double>(i, j) - trueH.at<double>(i, j));
		}
	}

	//std::cout << H << std::endl;
	std::cout << "Time: " << timeTaken << std::endl; 
	std::cout << "Errors: " << error << std::endl;
	std::cout << "Inliers:" << numInliers << std::endl; 

	

	cv::Mat kptImage1;
	cv::Mat kptImage2;

	cv::drawKeypoints(image1, keypoints1, kptImage1, cv::Scalar(0, 255, 0),
		cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	cv::drawKeypoints(image2, keypoints2, kptImage2, cv::Scalar(0, 255, 0),
		cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	cv::Mat matchImg;
	cv::drawMatches(image1, keypoints1, image2, keypoints2, goodMatches, matchImg);
	cv::imshow("Matches", matchImg);
	
	
	
	cv::Mat mosaic = image1.clone();
	cv::warpPerspective(image2, mosaic, H, mosaic.size(), cv::INTER_NEAREST, cv::BORDER_TRANSPARENT);
	cv::namedWindow("Mosaic");
	cv::imshow("Mosaic", mosaic);
	cv::imwrite("images/mosaic.png", mosaic);


	cv::namedWindow("Display 1");
	cv::imshow("Display 1", image1);
	cv::imshow("Display 2", image2);
	cv::waitKey();
	

	return 0;
}
