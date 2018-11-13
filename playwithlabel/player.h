#ifndef PLAYER_H
#define PLAYER_H
#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QPaintEvent>
#include <iostream>
#include <fstream>
#include <QString>
#include <string>

using namespace cv;
using namespace std;

class Player : public QThread
{
    Q_OBJECT
private:
    bool stop;
    QMutex mutex;
    QWaitCondition condition;
    Mat frame;
   // int fps;
    int frameRate;
    int totalframe;
    VideoCapture capture;
    VideoWriter video;
    Mat RGBframe;
    QImage img;
    QImage gambar;
    Mat gray,tress,maskInv,imgbg,imgfg,sum,image2,baru,vect,image3,image4,enlarged,image5;
  // string line; //jika ingin menggunakan putText via opencv
   // QString qstr = QString::fromStdString(line); //jika ingin ditampilkan dalam Drawtext via QPainter
    float ko[10000][10000];
    int ini=1;
    QString lokvideo;
    string lokasivideo;
    QString DataWaktu,DataKecepatan,DataAltitude,DataRoll,DataLongitude,DataPitch,DataLatitude,DataYaw;
    int kunci;
public:
    //explicit Player(QWidget *parent = nullptr);
    Player(QObject *parent = 0);
    ~Player();
    bool loadVideo(String filename);    //memanggil filename dari mainwindow.cpp
    bool loadData (String d_filename); //memanggil d_filename dari mainwindow.cpp
    bool loadWaktu (String datawaktu);
    bool loadKeceptan(String datakecepatan);
    bool loadAltitude (String dataaltitude);
    bool loadRoll(String dataroll);
    bool loadLongitude(String datalongitude);
    bool loadPitch(String datapitch);
    bool loadLatitude(String datalatitude);
    bool loadYaw(String datayaw);
    bool lokasiVideo(String lokasi);
    void Play();
    void Stop();
    bool isStopped() const;
    void setCurrentFrame(int frameNumber);
    double getFrameRate();
    double getCurrentFrame();
    double getNumberOfFrames();
        int wak =0 ;
        int kec, alt,bat,rol,pit,yaw,log,lat;
signals:
void processedImage(const QImage &image);
protected:
void run();
void msleep(int ms);
};
#endif // PLAYER_H
