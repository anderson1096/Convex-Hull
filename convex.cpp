#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace std;
using namespace cv;



Mat convex_hull(Mat &thresh){

  int largest_area = 0, largest_area_index = 0;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  Scalar verde(0,255,0);
  Scalar azul(255,0,0);

  //Sacando el contorno de la imagen
  cv::findContours(thresh, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
  vector<vector<Point> > hull (contours.size());
  //Dibujando el contorno anterior almacenado en el vector countours
  cv::Mat drawing = cv::Mat::zeros(thresh.size(), CV_8UC3);
  // Buscando el convex hull
  for (int i = 0; i < contours.size(); i++) {
    convexHull(Mat(contours[i]), hull[i], false);
  }
  // Buscando el contorno mas largo
  for (int i = 0; i < contours.size(); i++) {
    double a = contourArea(contours[i], false);
    if(a > largest_area){
      largest_area = a;
      largest_area_index = i;
    }

  }
  //Dibujando contorno y convexHull
  if(contours.size() > 20){
    drawContours(drawing, contours, largest_area_index, azul, 1, 8, hierarchy);
    drawContours(drawing, hull, largest_area_index, verde, 1, 8, hierarchy);

  }

  return drawing;

}


Mat threshold(Mat gray){
  cv::Mat draw;
  Mat back = imread("/home/anderson/Documentos/ConvexHull/fondo.jpg");
  cvtColor(back, back, CV_BGR2GRAY);
  //Funcion para detectar bordes en una imagen usando threshold
  //cv::inRange(gray, Scalar(0, 55, 90, 255), Scalar(28, 175, 230, 255), draw);
  //inRange(gray, Scalar(33,33,43), Scalar(175,199,251), gray);
  draw = Mat::zeros(gray.size(), CV_8UC3);
  //blur(gray,gray, cv::Size(3,3));
  //cvtColor(gray,gray, CV_BGR2GRAY);
  absdiff(gray,back,draw);
  //cvtColor(draw, draw, CV_BGR2GRAY);
  threshold(draw, draw, 15, 255, THRESH_BINARY_INV);
  return draw;
}


int main(int argc, char **argv){

  //Declarando las imagenes que utilizaremos
  cv::Mat src, frame, draw, src_gray, dst, firstFrame;
  //Definiendo que argumento será la entrada
  //char *imageName = argv[1];
  //frame = cv::imread(imageName);
  cv::VideoCapture cap(0);

  if(!cap.isOpened()){
    printf("Error no se encontró ninguna cámara\n");
    return -1;
  }
  cap >> frame;
  frame.copyTo(firstFrame);
  imwrite("/home/anderson/Documentos/ConvexHull/fondo.jpg",firstFrame);
  while(true){
    //Convirtiendo imagen a escala de grises y eliminando el ruido
    cap >> frame;
    cv::blur(frame,frame, cv::Size(3,3));
    cv::cvtColor(frame, src_gray, CV_BGR2GRAY);
    draw = threshold(src_gray);
    dst = convex_hull(draw);
    //cv::namedWindow("Contornos", CV_WINDOW_AUTOSIZE);
    //cv::imshow("Normal", firstFrame);
    cv::imshow("Contornos", dst);
    //cv::waitKey();
    if(cv::waitKey(30) >= 0){
      break;
    }
  }


  return 0;
}
