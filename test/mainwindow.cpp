#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include<QMessageBox>
#include "anonimus.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
   auto QfileName = QFileDialog::getOpenFileName(this,tr("Open Video"), "", tr("Video Files (*.avi,*mp4)"));
  VideoPath=QfileName.toLocal8Bit().constData();

  if(VideoPath.size()==0)
        return;
  ui->checkBox->setEnabled(false);
  ui->pushButton_2->setEnabled(true);

}

void MainWindow::on_pushButton_2_clicked()
{  std::string test = "../../Anonimus/data/";
    std::string jpg = ".jpg";


    const std::string config  = "../../Anonimus/data/deploy.prototxt";
    const std::string weights = "../../Anonimus/data/res10_300x300_ssd_iter_140000.caffemodel";
    const std::string video   = "../../Anonimus/data/prank.mp4";
    const std::string pic = "../../Anonimus/data/mface1.jpg";
    const std::string model_bin = "../../Anonimus/data/face-reidentification-retail-0095.bin";
    const std::string weights_xml = "../../Anonimus/data/face-reidentification-retail-0095.xml";
    Detector detector(config, weights, 0.4f);
    Classificator classificator(model_bin, weights_xml,0.6f);
    Anonimus anonimus(0, &detector, &classificator, new Blur());
    cv::Mat img1, img2, img3, img4, img5;
    img1 = cv::imread(pic);
    img2 = cv::imread(test+"mface"+jpg);
    img3 = cv::imread(test + "3" + jpg);
    img4 = cv::imread(test + "4" + jpg);
    img5 = cv::imread(test + "5" + jpg);
    classificator.addNewObject(img1);
   ImageChanger* changer;


  if(ui->checkBox->isChecked())
  {
     Anonimus();
  }
  else
  {
     Anonimus();
  }

    while(true)
    {
//обрабатываем кадры в соответсвии с выбранным radio_button
        if(ui->radioButton->isChecked())//blur all faces
        {

        }
        if(ui->radioButton_2->isChecked())//
        {

        }
        if(ui->radioButton_3->isChecked())//
        {

        }
       if(ui->radioButton_4->isChecked())//
        {

        }
    }

}

void MainWindow::on_checkBox_clicked()
{
    if(ui->pushButton->isEnabled())
    {
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(true);
    }
    else
    {
      ui->pushButton->setEnabled(true);
      ui->pushButton_2->setEnabled(false);
    }
}

void MainWindow::on_radioButton_3_clicked()
{
    auto QfileName = QFileDialog::getOpenFileName(this,tr("Open Picture"), "", tr("Pictures Files (*.png,*jpeg,*.bmp)"));
   PicturePath=QfileName.toLocal8Bit().constData();

}
