#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char* argv[])
{

  if (2 != argc) {
    std::cout << "Please enter the correct parameters" << std::endl;
    return -1;
  }
  
  std::string path = argv[1];
  std::string fx_str, fy_str, cx_str, cy_str, k1_str, k2_str, p1_str, p2_str, k3_str;
  double fx, fy, cx, cy, k1, k2, p1, p2, k3;

  for (int i = 1; i <= 4; ++i) {

    std::string cam_paras = path + "/" + std::to_string(i) + ".txt"; 
    std::ifstream infile(cam_paras);
    if (infile) {

      getline (infile, fx_str);
      getline (infile, fy_str);
      getline (infile, cx_str);
      getline (infile, cy_str);
      getline (infile, k1_str);
      getline (infile, k2_str);
      getline (infile, p1_str);
      getline (infile, p2_str);
      getline (infile, k3_str);
      
      fx = std::stod(fx_str);
      fy = std::stod(fy_str);
      cx = std::stod(cx_str);
      cy = std::stod(cy_str);
      k1 = std::stod(k1_str);
      k2 = std::stod(k2_str);
      p1 = std::stod(p1_str);
      p2 = std::stod(p2_str);
      k3 = std::stod(k3_str);

    }


    cv::Mat image_in;
    std::string image_str;
    std::ifstream image_txt(path + "/" + std::to_string(i) + "/image.txt");

    if (image_txt) {

      while (getline(image_txt, image_str)) {

        //image_in = cv::imread("/home/zhangying/data/headpose_test/11_19_703/1/1542609522.png");
        image_in = cv::imread(path + "/" + std::to_string(i) + "/" + image_str);
        if (image_in.empty()) {
          std::cout << "imread png error" << std::endl;
        }
        cv::Mat image_out;
        cv::Mat_<double> cameraMatrix(3,3,0.0);
        cv::Mat_<double> distCoeffs(5,1,0.0);

        cameraMatrix(0, 0) = fx; 
        cameraMatrix(0, 1) = 0;
        cameraMatrix(0, 2) = cx;
        cameraMatrix(1, 0) = 0;
        cameraMatrix(1, 1) = fy;
        cameraMatrix(1, 2) = cy;
        cameraMatrix(2, 0) = 0;
        cameraMatrix(2, 1) = 0;
        cameraMatrix(2, 2) = 1;

        distCoeffs(0,0) = k1;
        distCoeffs(1,0) = k2;
        distCoeffs(2,0) = p1;
        distCoeffs(3,0) = p2;
        distCoeffs(4,0) = k3;

        cv::Mat_<double> newCameraMatrix = cameraMatrix;

        cv::undistort(image_in, image_out, cameraMatrix, distCoeffs, newCameraMatrix);
        cv::imwrite(path + "/undistort/" + std::to_string(i) + "/" + image_str, image_out);
        //cv::namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
        //cv::imshow("MyWindow", image_out);
        //cv::waitKey(500);


      }

    }
    
  }
  
  return 0;
}


