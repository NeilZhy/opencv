// Summary: 利用OpenCV的LBF算法进行人脸关键点检测
// Author:  Amusi
// Date:    2018-03-20
// Reference:
//		[1]Tutorial: https://www.learnopencv.com/facemark-facial-landmark-detection-using-opencv/
//		[2]Code: https://github.com/spmallick/learnopencv/tree/master/FacialLandmarkDetection

// Note: OpenCV3.4以及上支持Facemark

#include<opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/face.hpp>
#include <opencv4/opencv2/face/facemark.hpp>
#include <opencv4/opencv2/face/facemarkLBF.hpp>
#include <opencv4/opencv2/face/facemark_train.hpp>
#include "./drawLandmarks.hpp"


using namespace std;
using namespace cv;
using namespace cv::face;


int main(int argc,char** argv)
{
    // 加载人脸检测器（Face Detector）
	// [1]Haar Face Detector
    //CascadeClassifier faceDetector("haarcascade_frontalface_alt2.xml");
	// [2]LBP Face Detector
	CascadeClassifier faceDetector("/home/zhangying/graduation_project/opencv/data/lbpcascades/lbpcascade_frontalface.xml");

    // 创建Facemark类的对象
    Ptr<Facemark> facemark = FacemarkLBF::create();

    // 加载人脸检测器模型
    facemark->loadModel("../data/lbfmodel.yaml");

    // 设置网络摄像头用来捕获视频
    VideoCapture cam(0);
    
    // 存储视频帧和灰度图的变量
    Mat frame, gray;
    

    VideoWriter write;

    string outFlie = "./aa.avi";
    int codec = CV_FOURCC('M','J','P','G');
    double fps = 25.0;
    int w = static_cast<int>(cam.get(CV_CAP_PROP_FRAME_WIDTH));
    int h = static_cast<int>(cam.get(CV_CAP_PROP_FRAME_HEIGHT));
    Size S(w,h);
    double r = cam.get(CV_CAP_PROP_FPS);
    cam >> frame;
    write.open(outFlie, codec, fps, frame.size(), true);
    if (!write.isOpened()) {
      cerr << "could not open the output video file for write.\n";
      return -1;
    }
    if (!cam.isOpened())
    {
        return 1;
    }

    bool stop = false;

    // 读取帧
    while(!stop)
    {
      cam.read(frame);
      
      // 存储人脸矩形框的容器
      vector<Rect> faces;
	  // 将视频帧转换至灰度图, 因为Face Detector的输入是灰度图
      cvtColor(frame, gray, COLOR_BGR2GRAY);

      // 人脸检测
      faceDetector.detectMultiScale(gray, faces);
      
	  // 人脸关键点的容器
      vector< vector<Point2f> > landmarks;
      
	  // 运行人脸关键点检测器（landmark detector）
      bool success = facemark->fit(frame,faces,landmarks);
      
      if(success)
      {
        // 如果成功, 在视频帧上绘制关键点
        for(int i = 0; i < landmarks.size(); i++)
        {
			// 自定义绘制人脸特征点函数, 可绘制人脸特征点形状/轮廓
			drawLandmarks(frame, landmarks[i]);
			// OpenCV自带绘制人脸关键点函数: drawFacemarks
			drawFacemarks(frame, landmarks[i], Scalar(0, 0, 255));
        }
	
      }

      // 显示结果
      imshow("Facial Landmark Detection", frame);

      write.write(frame);

      // 如果按下ESC键, 则退出程序
      if (waitKey(1) == 27) break;
      
    }

    write.release();
    return 0;
}
