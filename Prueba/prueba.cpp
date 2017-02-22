#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace std;
using namespace cv;



Mat threshold(Mat gray){
  cv::Mat draw;
  Mat back = imread("/home/anderson/Documentos/ConvexHull/fondo.jpg");
  cvtColor(back, back, CV_BGR2GRAY);
	// Create a structuring element
	int erosion_size = 6;
	Mat element = getStructuringElement(cv::MORPH_CROSS,
						 cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
						 cv::Point(erosion_size, erosion_size) );

	// Apply erosion or dilation on the image

	absdiff(gray,back,draw);
  threshold(draw, draw, 25, 255, THRESH_BINARY_INV);
	erode(draw,draw,element);
	//dilate(draw,draw,element);
	return draw;
}


int main(int argc, char **argv){

  //Declarando las imagenes que utilizaremos
  cv::Mat src, frame, draw, src_gray, dst, firstFrame;
  //Definiendo que argumento será la entrada
  char *imageName = argv[1];
  frame = cv::imread(imageName);
  cv::VideoCapture cap(0);
	Mat back = imread("/home/anderson/Documentos/ConvexHull/fondo.jpg");
  /*if(!cap.isOpened()){
    printf("Error no se encontró ninguna cámara\n");
    return -1;
  }
  cap >> frame;
  frame.copyTo(firstFrame);
  imwrite("/home/anderson/Documentos/ConvexHull/fondo.jpg",firstFrame);
  while(true){
    //Convirtiendo imagen a escala de grises y eliminando el ruido
    cap >> frame;
    //cv::blur(frame,frame, cv::Size(3,3));*/
    cv::cvtColor(frame, src_gray, CV_BGR2GRAY);
    draw = threshold(src_gray);
    //cv::namedWindow("Contornos", CV_WINDOW_AUTOSIZE);
    cv::imshow("Normal", back);
    cv::imshow("Contornos", draw);
    cv::waitKey();
    /*if(cv::waitKey(30) >= 0){
      break;
    }*
  }*/


  return 0;
}
