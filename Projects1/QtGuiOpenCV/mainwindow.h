#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include <QFileDialog>

using namespace cv;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_PBLoadImage_clicked();

    void on_PBOpenImage_clicked();

private:
    Ui::MainWindow *ui;
    Mat image; // the image variable
    Mat image2; // the image variable
    void salt(cv::Mat &image, int n);
    void colorReduce(cv::Mat &image, int div);
};

#endif // MAINWINDOW_H
