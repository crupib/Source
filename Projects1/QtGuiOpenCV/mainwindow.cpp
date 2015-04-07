#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace cv;

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

void MainWindow::on_PBLoadImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    image= cv::imread(fileName.toStdString().data());
//    cv::namedWindow("Original Image"); cv::imshow("Original Image", image);
}

void MainWindow::on_PBOpenImage_clicked()
{
 //   cv::flip(image,image,1);
 //   cv::namedWindow("Output Image");
 //   cv::imshow("Output Image", image);
     cv::resize(image, image,cv::Size(),1.0,1.0,cv::INTER_NEAREST);
     image2= image.clone();
     cvtColor(image2,image2,CV_BGR2RGB);
     flip(image,image,1);
     cvtColor(image,image,CV_BGR2RGB);
     salt(image,3000);
     colorReduce(image,64);
     QImage img= QImage((const unsigned char*)(image.data), image.cols,image.rows,image.step,QImage::Format_RGB888);
     ui->label->setPixmap(QPixmap::fromImage(img));
     ui->label->resize(ui->label->pixmap()->size());
     QImage img2= QImage((const unsigned char*)(image2.data), image2.cols,image2.rows,image2.step,QImage::Format_RGB888);
     ui->label_2->setPixmap(QPixmap::fromImage(img2));
     ui->label_2->resize(ui->label_2->pixmap()->size());
}
void MainWindow::salt(cv::Mat &image, int n)
{ for (int k=0; k<n; k++)
    { // rand() is the MFC random number generator // try qrand() with Qt
        int i= rand()%image.cols;
        int j= rand()%image.rows;
        if (image.channels() == 1)
        { // gray-level image
            image.at<uchar>(j,i)= 255; }
        else if
                (image.channels() == 3)
        { // color image
            image.at<cv::Vec3b>(j,i)[0]= 255; image.at<cv::Vec3b>(j,i)[1]= 255; image.at<cv::Vec3b>(j,i)[2]= 255;
        }
    }
}
/*
void MainWindow::colorReduce(cv::Mat &image, int div = 64)
{
    int nl= image.rows; // number of lines // total number of elements per line
    int nc= image.cols * image.channels();
    for (int j=0; j<nl; j++)
    { // get the address of row j
        uchar* data= image.ptr<uchar>(j);
        for (int i=0; i<nc; i++)
        { // process each pixel ---------------------
            data[i]= data[i]/div*div + div/2; // end of pixel processing ----------------
        } // end of line
    }
}
*/
void MainWindow::colorReduce(cv::Mat &image, int div=64)
{
    int nl= image.rows;
    // number of lines
    int nc= image.cols ;
    // number of columns
    // is it a continous image?
    if (image.isContinuous())
    {
        // then no padded pixels
        nc= nc*nl;
        nl= 1;
        // it is now a 1D array
    }
    int n = static_cast<int>(
                log(static_cast<double>(div))/log(2.0));
    // mask used to round the pixel value
    uchar mask= 0xFF<<n;
    // e.g. for div=16, mask= 0xF0
    // for all pixels
    for (int j=0; j<nl; j++)
    {
        // pointer to first column of line j
        uchar* data= image.ptr<uchar>(j);
        for (int i=0; i<nc; i++)
        { // process each pixel ---------------------
            *data++= *data&mask + div/2;
            *data++= *data&mask + div/2;
            *data++= *data&mask + div/2;
            // end of pixel processing ----------------
        }
       // end of line
     }
}



