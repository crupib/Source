#include <QCoreApplication>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
using namespace cv;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Mat image = imread("C:\\Users\\crupib\\Pictures\\thegang.jpg");
    namedWindow("My Image");
    imshow("My Image",image);
    waitKey(5000);
    //return a.exec();
    return 0;
}
