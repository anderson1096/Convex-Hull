#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <time.h>
#include <iostream>

using namespace std;
using namespace cv;


int main(){

  Mat img1, img2, dst;
  img1 = imread("/home/anderson/Documentos/ConvexHull/Prueba2/mano.jpg");
  img2 = imread("/home/anderson/Documentos/ConvexHull/Prueba2/normal.jpg");
  dst = Mat::zeros(img1.size(), CV_8UC3);
  blur(img1,img1, cv::Size(3,3));
  absdiff(img1,img2,dst);
  cvtColor(dst,dst, CV_BGR2GRAY);
  threshold(dst, dst, 10, 255, THRESH_BINARY);
  imshow("Normal", dst);
  waitKey();





}
