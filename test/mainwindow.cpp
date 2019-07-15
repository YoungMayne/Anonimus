#include "mainwindow.h"
#include "ui_mainwindow.h"


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
{   std::string detector_name;
    std::string image_changer_name;


    if(ui->checkBox_2->isChecked())
        detector_name="detector";
    else
        detector_name="classificator";


        if(ui->radioButton->isChecked())
        {
            image_changer_name="Blur"   ;
        }
        if(ui->radioButton_2->isChecked())
        {
            image_changer_name="Pixelize";
        }
        if(ui->radioButton_3->isChecked())
        {

            image_changer_name="Kek";
        }
       if(ui->radioButton_4->isChecked())
        {
            image_changer_name="rectangle";
        }
    execl("main.exe",VideoPath,detector_name,image_changer_name,PicturePath,NULL);

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
