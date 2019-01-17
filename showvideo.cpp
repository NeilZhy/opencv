#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;

int main()
{
  cv::VideoCapture capture(0);
  while (true) {
    cv::Mat frame;
    capture >> frame;
    cv::imshow("frame", frame);
    cv::waitKey(30);
  }
  return 0;
}
