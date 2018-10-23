#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProgressBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    myPlayer =new Player();
    QObject ::connect(myPlayer, SIGNAL(processedImage(QImage)),
                      this,SLOT(updatePlayerUI(QImage)));
    ui->setupUi(this);
    /*
    ui->setupUi(this);
    QPixmap pix(gambar);
    int w=ui->label->width();
    int h=ui->label->height();
    ui->label->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
*/

}
/*
void MainWindow :: setProgressBarValue()
{
    bar=new QProgressBar (this);
    button =new QPushButton(this);
    connect(button,SIGNAL(clicked()),this,SLOT(setProgressBarValue()));
    int value = 50;
    bar->setValue(value);
}
*/
void MainWindow::updatePlayerUI(QImage img)
{
    if(!img.isNull()){
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(),Qt::KeepAspectRatio,Qt::FastTransformation));
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
                                                    tr("Video Files(*.avi *.mpg *.mp4)"));
    if(!filename.isEmpty()){
        if(!myPlayer->loadVideo(filename.toLatin1().data()))
        {
        QMessageBox msgBox;
        msgBox.setText("The selected video could not be opened");
        msgBox.exec();
        }
       ui->lineEdit->setText(filename);
    }
}
void MainWindow :: on_pushButton_2_clicked()
{
    if(myPlayer->isStopped())
    {
        myPlayer->Play();
        ui->pushButton_2->setText(tr("Stop"));
    }else
    {
        myPlayer->Stop();
        ui->pushButton_2->setText(tr("Play"));
    }

}

void MainWindow::on_pushButton_3_clicked()
{

    QString d_filename = QFileDialog::getOpenFileName(this,tr("Open Data"),".",
                                                    tr("Video Files(*.m *.xlsx)"));
    ui->lineEdit_2->setText(d_filename);
    /*
    auto excel     = new QAxObject("Excel.Application");
    auto workbooks = excel->querySubObject("Workbooks");
    auto workbook  = workbooks->querySubObject("Open(const QString&)",d_filename);
    auto sheets    = workbook->querySubObject("Worksheets");
    auto sheet     = sheets->querySubObject("Item(int)", 1);
    for (int r = 1; (r <= 5); ++r)
    {
        auto cCell = sheet->querySubObject("Cells(int,int)",r,1);
        qDebug() << cCell->dynamicCall("Value()").toInt();
    }
*/
}

void MainWindow::on_pushButton_4_clicked()
{
    close();
}
