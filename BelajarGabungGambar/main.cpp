#include "mainwindow.h"
#include <QApplication>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/opencv.hpp"
#include "iostream"
using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Mat image =imread("D:/Magang/Belajar_Qt/icon_shutdown.png");    
    if (image.empty()) {
                      cout << "Error" << endl;
                      return -1;
             }
    namedWindow("image",CV_WINDOW_FREERATIO);
    imshow("image",image);
    cout << "image channels: " << image.channels() <<  endl;
      //waitKey(0);
    /*
      if (image.channels() == 1) {
                         Scalar pixel = image.at<uchar>(10, 10);
                         cout << "Pixel value at 5,6 cordinate : " << pixel.val[0] << endl;
                }
      else if (image.channels() == 3) {
          for (int i=0;i<image.rows;i++){
              for (int j=0;j<image.cols;j++){
                  image.at<Vec3b>(i,j)[0]=0;
                  image.at<Vec3b>(i,j)[1]=0;
                  image.at<Vec3b>(i,j)[2]=0;
              }
          }

                }
      else {
               cout << "this is not a single channel image" << endl;
      }
*/
      waitKey(0);

    for (int i=0;i<image.rows;i++){
        for (int j=0;j<image.cols;j++){
            if(image.at<Vec3b>(i,j)[0]==52 && image.at<Vec3b>(i,j)[1]==152 && image.at<Vec3b>(i,j)[2]==219){
                image.at<Vec3b>(i,j)[0]=0;
                image.at<Vec3b>(i,j)[1]=0;
                image.at<Vec3b>(i,j)[2]=0;
            }

            else{
                image.at<Vec3b>(i,j)[0]=225;
                image.at<Vec3b>(i,j)[1]=225;
                image.at<Vec3b>(i,j)[2]=225;
            }

           }
        }
    namedWindow("output",CV_WINDOW_FREERATIO);
    imshow("output",image);
    waitKey(0);
  return a.exec();
      }
//












