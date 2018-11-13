#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProgressBar>
#include <QPainter>
#include <QAxObject>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::
       MainWindow)
{
    myPlayer =new Player();
    QObject ::connect(myPlayer, SIGNAL(processedImage(QImage)),
                      this,SLOT(updatePlayerUI(QImage)));
    ui->setupUi(this);
    ui->pushButton_2->setEnabled(false); //pushbutton tidak aktif jika tidak file yang diunggah
    ui->horizontalSlider->setEnabled(false); //horizontal tidak aktif jika tidak file yang diunggah
}

void MainWindow::updatePlayerUI(QImage img)
{
    if(!img.isNull()){
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(),Qt::KeepAspectRatio,Qt::FastTransformation));
        ui->horizontalSlider->setValue(myPlayer->getCurrentFrame());
        ui->label_4->setText(getFormattedTime((int)myPlayer->getCurrentFrame()/(int)myPlayer->getFrameRate()));
    }
}

MainWindow::~MainWindow()
{
    delete myPlayer;
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open Video"),".",
                                                    tr("Video Files(*.avi *.mpg *.mp4)")); //membuka dokumen untuk memilih video yang sesuai ekstensi
    QFileInfo name = filename;
    //pesan dibawah ini akan keluar video tidak sesuai
    if(!filename.isEmpty()){
        if(!myPlayer->loadVideo(filename.toLatin1().data()))
        {
        QMessageBox msgBox;
        msgBox.setText("The selected video could not be opened");
        msgBox.exec();
        }
        //kalau ada video hal dibawah ini akan dilakukan
        else{
            this->setWindowTitle(name.fileName());
            ui->pushButton_2->setEnabled(true); //pushbutton menjadi aktif
            ui->horizontalSlider->setEnabled(true); //horizontal akan aktif
            ui->horizontalSlider->setMaximum(myPlayer->getNumberOfFrames()); //akan berjalan sampai ukuran max video
            ui->label_5->setText(getFormattedTime((int)myPlayer->getNumberOfFrames()/(int)myPlayer->getFrameRate()) ); //mencatat dan menampilkan durasi video
        }
       ui->lineEdit->setText(filename); //menampilkan alamat filename di lineedit (lokasi video)
    }
}
void MainWindow :: on_pushButton_2_clicked() //kalau pushbutton 2 sudah diklik maka hal dibawah ini akan terjadi
{
    if(myPlayer->isStopped())
    {
        myPlayer->Play(); //jika mplayer berputar
        ui->pushButton_2->setText(tr("Stop")); //tulisan pushbutton jadi stop
    }else
    {
        myPlayer->Stop(); //jika mplayer berhenti
        ui->pushButton_2->setText(tr("Play")); //tulisan puhbutton jadi play
    }

}

QString MainWindow::getFormattedTime(int timeInSeconds){
    int seconds =(int)(timeInSeconds)% 60;
    int minutes = (int)((timeInSeconds/60)% 60);
    int hours = (int)((timeInSeconds/3600)% 24);
    QTime t(hours,minutes,seconds);
    if(hours ==0)
        return t.toString("mm:ss");
    else
        return t.toString("hh:mm:ss");
}
void MainWindow::on_pushButton_3_clicked() //kalau di klik, hal dibawah ini akan dilakukan
{

    d_filename = QFileDialog::getOpenFileName(this,tr("Open Data"),".",
                                                  tr("Video Files(*.m *.xlsx *.csv)")); //membuka dokumen untuk memilih file yang tersedia(sesuai ekstensi)

    //kalau gak ada file pesan dibawah ini akan keluar
    if(!d_filename.isEmpty()){
        if(!myPlayer->loadData(d_filename.toLatin1().data())){
            QMessageBox msgBox;
            msgBox.setText("The selected data could not be opened");
            msgBox.exec();
                }
            }

    ui->lineEdit_2->setText(d_filename); //mencatat lokasi file d_filename di lineedit (lokasi berkas);
}

void MainWindow::on_pushButton_4_clicked() //kalau diklik akan keluar dari ui
{
    close();
}

void MainWindow::on_horizontalSlider_sliderPressed() //kalau di press video akan berhenti
{
    myPlayer->Stop();
}

void MainWindow::on_horizontalSlider_sliderReleased() //kalau ngk dipress video akan berjalan
{
    myPlayer->Play();
}
void MainWindow::on_horizontalSlider_sliderMoved(int position){
    myPlayer->setCurrentFrame(position);
    ui->label_4->setText(getFormattedTime(position/(int)myPlayer->getFrameRate()));
}



void MainWindow::on_pushButton_5_clicked()
{
QString lokasi = QString("D:\\videohasil.avi");
if(!myPlayer->lokasiVideo(lokasi.toLatin1().data())){
    QMessageBox msgBox;
    msgBox.setText("The selected data could not be opened");
    msgBox.exec();
        }
ui->lineEdit_3->setText(lokasi);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    int alma;;
    if(arg1){
        alma =1;
    }
    else{
            alma =0;
 //       qDebug()<<"Data waktu tidak ada"<<endl;

    }
    datawaktu = QString::number(alma);
    qDebug() << " " << datawaktu;
    if(!myPlayer->loadWaktu(datawaktu.toLatin1().data())){
        QMessageBox msgBox;
        msgBox.setText("The selected data could not be opened");
        msgBox.exec();
            }

//    myPlayer->loadData()
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    int omo;
    if(arg1){
        omo = 1;
    }
    else{
        qDebug()<<"Data kecepatan tidak ada"<<endl;
        omo = 0;
    }
    datakecepatan = QString::number(omo);
    if(!myPlayer->loadKeceptan( datakecepatan.toLatin1().data())){
        QMessageBox msgBox;
        msgBox.setText("The selected data could not be opened");
        msgBox.exec();
            }
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    int ini;
    if(arg1){
        ini = 1;
    }
    else{
        qDebug()<<"Data altitude tidak ada"<<endl;
        ini = 0;
    }
    dataaltitude = QString::number(ini);
    if(!myPlayer->loadAltitude(dataaltitude.toLatin1().data())){
        QMessageBox msgBox;
        msgBox.setText("The selected data could not be opened");
        msgBox.exec();
            }
}

void MainWindow::on_checkBox_6_stateChanged(int arg1)
{
    int imu;
    if(arg1){
        imu = 1;
    }
    else{
        qDebug()<<"Data roll tidak ada"<<endl;
        imu = 0;
    }
    dataroll = QString::number(imu);
    if(!myPlayer->loadRoll(dataroll.toLatin1().data())){
        QMessageBox msgBox;
        msgBox.setText("The selected data could not be opened");
        msgBox.exec();
            }
}

void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    int ina;
    if(arg1){
       ina = 1;
    }
    else{
        qDebug()<<"Data longitude tidak ada"<<endl;
        ina = 0;
    }
    datalongitude = QString::number(ina);
    if(!myPlayer->loadLongitude(datalongitude.toLatin1().data())){
        QMessageBox msgBox;
        msgBox.setText("The selected data could not be opened");
        msgBox.exec();
            }
}

void MainWindow::on_checkBox_7_stateChanged(int arg1)
{
    int iny;
    if(arg1){
        iny = 1;
    }
    else{
        qDebug()<<"Data pitch tidak ada"<<endl;
        iny = 0;
    }
    datapitch = QString::number(iny);
    if(!myPlayer->loadPitch(datapitch.toLatin1().data())){
        QMessageBox msgBox;
        msgBox.setText("The selected data could not be opened");
        msgBox.exec();
            }
}

void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    int inl;
    if(arg1){
        inl = 1;
    }
    else{
        qDebug()<<"Data latitude tidak ada"<<endl;
        inl = 0;
    }
    datalatitude = QString::number(inl);
    if(!myPlayer->loadLatitude(datalatitude.toLatin1().data())){
        QMessageBox msgBox;
        msgBox.setText("The selected data could not be opened");
        msgBox.exec();
            }
}

void MainWindow::on_checkBox_8_stateChanged(int arg1)
{
    int loh;
    if(arg1){
        loh = 1;
    }else{
        qDebug()<<"Data yaw tidak ada"<<endl;
        loh= 0;
    }
    datayaw = QString::number(loh);
    if(!myPlayer->loadYaw(datayaw.toLatin1().data())){
        QMessageBox msgBox;
        msgBox.setText("The selected data could not be opened");
        msgBox.exec();
            }
}
