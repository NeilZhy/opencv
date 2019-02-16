#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define PI 3.1415

void vec2lola(cv::Mat_<double> vec, double &lo, double &la){
  lo = -asin(vec(0,0)/sqrt(vec(0,0)*vec(0,0)+vec(2,0)*vec(2,0)))*180.0/PI;
  la = -asin(vec(1,0)) * 180.0 / PI;
}

int main(int argc, char *argv[])
{
  if (4 != argc) {
    cout << "Please enter the correct parameters" << endl;
    return -1;
  }
  
  string filename = argv[1];
  string path1 = argv[2];
  string path2 = argv[3];
  string path = path1 + "/" + path2 + "/";
  string outfilename = path1 + "." + path2 + ".";
  ifstream infile(argv[1]);
  ofstream outfile;
  outfile.open(outfilename + "headpose.gt.txt");
  string image;
  string x_str;
  string y_str;
  string z_str;
  string labelline;
  double x = 0;
  double y = 0;
  double z = 0;
  double yaw = 0;
  double pitch = 0;
  
  if(infile) {
    while (getline (infile, image))
    { 
      getline(infile, x_str);
      getline(infile, y_str);
      getline(infile, z_str);
      x = stod(x_str);
      y = stod(y_str);
      z = stod(z_str);

      cv::Mat_<double> dbmat(3,1,0.0);
      dbmat(0, 0) = x;
      dbmat(1, 0) = y;
      dbmat(2, 0) = z;
      vec2lola(dbmat, yaw, pitch);

      outfile << "{\"image\": \"" << path << image << "\", \"yaw\": " 
        << yaw << ", \"pitch\": " << pitch << "}" << endl;
    }
  } else {
    cout << "no such file" << endl;
  }

  outfile.close();
  infile.close();
  return 0;
}
