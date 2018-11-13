#include "player.h"
#include <QPainter>
#include <QDebug>
#include <QtCore>
#include <iostream>
#include <fstream>
#include <QString>
#include <string>
#include <QCheckBox>
#include <QMessageBox>
#include <QAxObject>
using namespace std;

// Variabel Array untuk menampung data penerbangan


Player::Player(QObject *parent) : QThread(parent)
{
    stop =true;
}

bool Player :: loadVideo(String filename){
    capture.open(filename);
    if(capture.isOpened())
    {
        frameRate = (int) capture.get(CV_CAP_PROP_FPS);
        totalframe = (int) capture.get(CV_CAP_PROP_FRAME_COUNT);
        qDebug() << "framerate" <<frameRate << "jmlh:" << totalframe;

        return true;
    } else{
        return false;
    }


}
void Player::Play()
{
    if (!isRunning()){
        if(isStopped()){
            stop=false;
        }
        start(LowPriority);
    }
}

double Player::getCurrentFrame(){
    return capture.get(CV_CAP_PROP_POS_FRAMES);

}
double Player::getNumberOfFrames(){
    return double(capture.get(CV_CAP_PROP_FRAME_COUNT));
}
double Player :: getFrameRate(){
    return frameRate;
}

void Player::setCurrentFrame(int frameNumber){
    capture.set(CV_CAP_PROP_POS_FRAMES,frameNumber);
}
bool Player :: loadData(String d_filename){
    QString qstr = QString::fromStdString(d_filename);
// Baca data file CSV dan simpan dalam array (2 dimensi)
//    QFile inputfile (qstr);
     FileStorage inputfile = (qstr, FileStorage::READ);
    inputfile.open(QIODevice::ReadOnly);
    if (!inputfile.isOpen())
        return true;

    QTextStream stream (&inputfile);
    QString line = stream.readLine();
    if (!line.isNull()){
    int baris=1;
    while (baris <=totalframe){
        line = stream.readLine();
        QByteArray hhh = line.toLocal8Bit();
        const char *line1= hhh.data();
                   sscanf(line1,"%f ,%f ,%f ,%f, %f,%f,%f,%f",&ko[baris][1],&ko[baris][2],&ko[baris][3],&ko[baris][4],&ko[baris][5],&ko[baris][6],&ko[baris][7],&ko[baris][8]);
                   qDebug() << "baris" << baris <<"hayo ke:" <<line << "jadinya: " <<ko[baris][1]<< " " << ko[baris][2] << " " << ko[baris][3] << " " << ko[baris][6] << " " << ko[baris][7] << " " << ko[baris][8];

                   baris++;
    }
    // Linearisasi



 }
    else {
        inputfile.close();
    }

/*
    QCheckBox *checkbox = new QCheckBox();
    //checkbox->setChecked(false);
    if (!checkbox->isChecked()){
        putText(frame,line,Point2f(100,100),FONT_HERSHEY_PLAIN,2,  Scalar(0,0,255), 2 , 8 , false);
    }else{
        QMessageBox msgeBox;
        msgeBox.setText("Anda tidak menampilkan data");
        msgeBox.exec();
    }
*/


    return true;

}
bool Player :: lokasiVideo(String lokasi){
     lokvideo = QString::fromStdString(lokasi);
    //qDebug()<<lokvideo<<endl;
    lokasivideo = lokvideo.toLocal8Bit().constData(); //Qstring to std string
   // cout<<lokasivideo<<endl;
    return true;

}
bool Player :: loadWaktu(String datawaktu){
//    waktu = QString ::fromStdString(datawaktu);
//    DataWaktu = waktu.toLocal8Bit().constData();

    QString ok = QString::fromStdString(datawaktu);
    float maka= ok.toInt();
//    int oi;
    if (maka >0){
        DataWaktu= "Waktu: ";
        wak =1;
    }
   else {
        DataWaktu= "";
        wak =0;
    }
//    wak = oi;
    return true;
}
bool Player :: loadKeceptan(String datakecepatan){
//    kecepatan =QString ::fromStdString(datakecepatan);
//    DataKecepatan = kecepatan.toLocal8Bit().constData();
    QString ok1 = QString::fromStdString(datakecepatan);
    int moka = ok1.toInt();;
    if (moka >0){
        DataKecepatan= "Kecepatan: ";
        kec =1;
    }
    else {
        DataKecepatan= "";
        kec =0;
    }
    qDebug() << " " <<kec;
     return true;
}
bool Player ::loadAltitude(String dataaltitude){
    QString ok2 = QString::fromStdString(dataaltitude);
    int mika = ok2.toInt();;
    if (mika>0){
        DataAltitude= "Altitude: ";
        alt =1;
    }
    else {
        DataAltitude= "";
        alt =0;
    }

    return true;
}
bool Player :: loadRoll(String dataroll){
    QString ok3 = QString::fromStdString(dataroll);
    int mina = ok3.toInt();;
    if (mina >0){
        DataRoll= "Roll: ";
        rol =1;
    }
    else {
        DataRoll= "";
        rol =0;
    }
    return true;
}
bool Player :: loadLongitude(String datalongitude){
    QString ok4 = QString::fromStdString(datalongitude);
    int minu = ok4.toInt();;
    if (minu >0){
        DataLongitude= "Longitude: ";
        log =1;
    }
    else {
        DataLongitude= "";
        log =0;
    }
    return true;
}
bool Player :: loadPitch(String datapitch){
    QString ok5 = QString::fromStdString(datapitch);
    int mona = ok5.toInt();;
    if (mona >0){
        DataPitch= "Pitch: ";
        pit =1;
    }
    else {
        DataPitch= "";
        pit =0;
    }
    return true;
}
bool Player :: loadLatitude(String datalatitude){
    QString ok6 = QString::fromStdString(datalatitude);
    int mono = ok6.toInt();;
    if (mono >0){
        DataLatitude= "Latitude: ";
        lat =1;
    }
    else {
        DataLatitude= "";
        lat =0;
    }
    qDebug() << " " << lat;
    qDebug() << " " << DataLatitude;
    return true;
}
bool Player :: loadYaw(String datayaw){
    QString ok7 = QString::fromStdString(datayaw);
    int melu = ok7.toInt();;
    if (melu >0){
        DataYaw= "Yaw: ";
        yaw =1;
    }
    else {
        DataYaw= "";
        yaw =0;
    }
    return true;
}
void Player :: run()
{
    kunci =1;
    int frame_width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
    int frame_height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
    video.open(lokasivideo,CV_FOURCC('M','J','P','G'),frameRate,Size(frame_width,frame_height),true);
    if (!video.isOpened()) {
            qDebug() << "Could not open the output video file for write\n"<<endl;
        }
    int delay =(1000/frameRate);
    while (!stop) {
        if(!capture.read(frame))
        {
            stop=true;
            break;

        }
        image2 = imread("C:\\Users\\User\\Documents\\MATLAB\\B100.png");
        image4 = imread("C:\\Users\\User\\Documents\\MATLAB\\skala1.png");
        resize(image4, enlarged, cv::Size(image4.cols*2, image4.rows*2), cv::INTER_NEAREST);
//        int panjangk = frame.cols*0.125;
//        int lebarkh   = frame.rows*0.75;
//        int panj = frame.cols*0.0625;
//        int lbr  = frame.rows*0.1;
//        resize(enlarged,image5,Size(panjangk, lebarkh ),0,0);
//        resize(image2,image3,Size(panj,lbr ),0,0);
        resize(enlarged,image5,Size(),0.5,0.5);
        resize(image2,image3,Size(),0.5,0.5);

        Rect ROI (0,0,image3.cols,image3.rows);
        baru= frame(ROI);
       //grayscale
         cvtColor(image3,gray,CV_BGR2GRAY);
         double thresh = 10;
         double maxValue = 255;
         threshold(gray,tress, thresh, maxValue, THRESH_BINARY);
         bitwise_not(tress,maskInv);
         bitwise_and(baru,baru,imgbg,maskInv);
         bitwise_and(image3,image3,imgfg,tress);
          add(imgbg,imgfg,sum);
            frame=frame.clone();
          for(int i=0;i<image3.rows;i++){
              for(int j=0;j<image3.cols;j++){

                  {
                          frame.at<Vec3b>(i,j)[0]= sum.at<Vec3b>(i,j)[0];
                          frame.at<Vec3b>(i,j)[1]= sum.at<Vec3b>(i,j)[1];
                          frame.at<Vec3b>(i,j)[2]= sum.at<Vec3b>(i,j)[2];
              }

          }
        }
          Rect ROI1 (frame.cols-image5.cols,image5.rows,image5.cols,image5.rows);
          Mat baru1= frame(ROI1);
          Mat mask(image5);
          image5.copyTo(baru1,mask);
        video.write(frame);
        // Masukkan data penerbangan
        // Spesifikasi tulisan
        int fontface  = cv::FONT_HERSHEY_SIMPLEX;
        double scale  = 0.6;
        int thickness = 1  ;
//        int baseline  = 0  ;
        // waktu
        QString Time;
        float omo;
        if (wak > 0){
            omo = ko[kunci][1];
            QString angka = QString::number(omo);

             Time = DataWaktu + angka;
        }
        else {
            Time = DataWaktu;
            omo= 0;
        }
        string waktu1 = Time.toLocal8Bit().constData();

        // kec
        QString fast;
        if (kec > 0){
            float om1 = ko[kunci][2];
            QString angku = QString::number(om1);
            fast = DataKecepatan + angku;
        }
        else {
            fast = DataKecepatan;
        }
        string kecepatan1 = fast.toLocal8Bit().constData();

        // alt
        QString ALT;
        if (alt > 0){
            float om2 = ko[kunci][3];
            QString angkk = QString::number(om2);
             ALT = DataAltitude + angkk;
        }
        else {
            ALT = DataAltitude;
        }
        string Altitude1 = ALT.toLocal8Bit().constData();

        // Roll
        QString Rol;
        if (rol > 0){
            float om3 = ko[kunci][4];
            QString angk = QString::number(om3);
             Rol = DataRoll + angk;
        }
        else {
            Rol = DataRoll;
        }
        string Roll1 = Rol.toLocal8Bit().constData();
        // longitude
        QString Long;
        if (log > 0){
            float om4 = ko[kunci][5];
            QString angkl = QString::number(om4);
             Long = DataLongitude + angkl;
        }
        else {
             Long = DataLongitude;
        }
        string Longitude1 = Long.toLocal8Bit().constData();
        // pitch
        QString Pitc;
        if (pit > 0){
            float om5 = ko[kunci][6];
            QString ang = QString::number(om5);
            Pitc = DataPitch + ang;
        }
        else {
            Pitc = DataPitch;
        }
        string Pitch1 = Pitc.toLocal8Bit().constData();
        // latitude
        QString Lat;
        if (lat > 0){
            float om6 = ko[kunci][7];
            QString anka = QString::number(om6);
            Lat = DataLatitude + anka;
        }
        else {
            Lat = DataLatitude;
        }
        string Latitude1 = Lat.toLocal8Bit().constData();
//        qDebug() << " " << Latitude1;
        // Yaw
        QString Yaw;
        if (yaw > 0){
            float om7 = ko[kunci][8];
            QString angko = QString::number(om7);
            Yaw = DataYaw + angko;
        }
        else {
            Yaw = DataYaw;
        }
        string Yaw1 = Yaw.toLocal8Bit().constData();
        // menambahkan background
        int x = frame.cols*0.2 ;
        int y = frame.rows*0.67;
        int lebar = frame.cols*0.6;
        int tinggi= frame.rows*0.3;
        Mat roi =frame(cv::Rect(x,y,lebar,tinggi));
        Mat color (roi.size(),CV_8UC3,cv::Scalar(0,0,0));
        double alpha =0.3;
        addWeighted(color,alpha,roi,1.0 - alpha,0.0,roi);
        //Posisi
        int x1 = frame.cols*0.2 +10;
        int y1 = frame.rows*0.67 +20;
        int x2 = lebar/2 +x1 +10;

    putText(frame,waktu1,Point2f(x1,y1),fontface,scale,cv:: Scalar(255,255,255,0),thickness,8);
    putText(frame,kecepatan1,Point2f(x1,y1+40),fontface,scale,cv:: Scalar(255,255,255,0),thickness,8);
    putText(frame,Altitude1,Point2f(x1,y1+80),fontface,scale,cv:: Scalar(255,255,255,0),thickness,8);
    putText(frame,Roll1,Point2f(x1,y1+120),fontface,scale,cv:: Scalar(255,255,255,0),thickness,8);
    putText(frame,Longitude1,Point2f(x2,y1),fontface,scale,cv:: Scalar(255,255,255,0),thickness,8);
    putText(frame,Pitch1,Point2f(x2,y1+40),fontface,scale,cv:: Scalar(255,255,255,0),thickness,8);
    putText(frame,Latitude1,Point2f(x2,y1+80),fontface,scale,cv:: Scalar(255,255,255,0),thickness,8);
    putText(frame,Yaw1,Point2f(x2,y1+120),fontface,scale,cv:: Scalar(255,255,255,0),thickness,8);
        if (frame.channels()==3){
            cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
            img = QImage((const unsigned char*)(RGBframe.data),
                         RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
        }
        else
        {
            img =QImage((const unsigned char*)(frame.data),
                    frame.cols,frame.rows,QImage::Format_Indexed8);

        }
        /*
        QPainter p(&img);
        p.setPen(QPen(Qt::red));
        p.setFont(QFont("Times",100,QFont::Bold));
        p.drawText(img.rect(),Qt::AlignCenter,qstr);
        */
        emit processedImage(img);
        this->msleep(delay);

        kunci ++;

    }


}


Player ::~Player()
{
    mutex.lock();
    stop =true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}
void Player::Stop()
{
    stop = true;
}
void Player ::msleep(int ms){
    struct timespec ts = {ms/1000,(ms % 1000)*1000*1000};
    nanosleep(&ts,NULL);
}
bool Player::isStopped() const{
    return this->stop;
}

