#include "opencv2/opencv.hpp"
#include "face_detect.h"

int TestLandmark(int argc, char* argv[]) {
	cv::Mat img_src = cv::imread("../images/4.jpg");
	const char* root_path = "../models";

	FaceDetector face_detector;
	face_detector.LoadModel(root_path);
	std::vector<FaceInfo> faces;
	face_detector.Detect(img_src, &faces);
	for (int i = 0; i < static_cast<int>(faces.size()); ++i) {
		cv::Rect face = faces.at(i).face_;
		cv::rectangle(img_src, face, cv::Scalar(0, 255, 0), 2);
		std::vector<cv::Point> keypoints;
		face_detector.ExtractKeypoints(img_src, face, &keypoints);
		for (int j = 0; j < static_cast<int>(keypoints.size()); ++j) {
			cv::circle(img_src, keypoints[j], 1, cv::Scalar(0, 0, 255), 1);
		}
	}
	cv::imwrite("../images/result.jpg", img_src);
	cv::imshow("result", img_src);
	cv::waitKey(0);

	return 0;

}

int TestRecognize(int argc, char* argv[]) {
	cv::Mat img_src = cv::imread("../images/4.jpg");
	const char* root_path = "../models";

	FaceDetector face_detector;
	face_detector.LoadModel(root_path);
	std::vector<FaceInfo> faces;
	face_detector.Detect(img_src, &faces);


	cv::Mat face1 = img_src(faces[0].face_).clone();
	cv::Mat face2 = img_src(faces[1].face_).clone();
	std::vector<float> feature1, feature2;
	face_detector.ExtractFeature(face1, &feature1);
	face_detector.ExtractFeature(face2, &feature2);
	float sim = CalculSimilarity(feature1, feature2);

	for (int i = 0; i < static_cast<int>(faces.size()); ++i) {
		cv::Rect face = faces.at(i).face_;
		cv::rectangle(img_src, face, cv::Scalar(0, 255, 0), 2);		
	}
	cv::imwrite("../images/face1.jpg", face1);
	cv::imwrite("../images/face2.jpg", face2);
	cv::imwrite("result.jpg", img_src);
	std::cout << "similarity is: " << sim << std::endl;

	return 0;

}

int main(int argc, char* argv[]) {
	// return TestLandmark(argc, argv);
	return TestRecognize(argc, argv);
}
