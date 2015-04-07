#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

cv::Mat image;
void onMouse(int event, int x, int y, int flags, void* param)
{
    char text[20];
    cv::Mat img2, img3;

    img2 = image.clone();

    if (event == CV_EVENT_LBUTTONDOWN)
    {
        cv::Vec3b p = img2.at<cv::Vec3b>(y,x);
        sprintf(text, "R=%d, G=%d, B=%d", p[2], p[1], p[0]);
    }
    else if (event == CV_EVENT_RBUTTONDOWN)
    {
        cvtColor(image, img3, CV_BGR2HSV);
        cv::Vec3b p = img3.at<cv::Vec3b>(y,x);
        sprintf(text, "H=%d, S=%d, V=%d", p[0], p[1], p[2]);
    }
    else
        sprintf(text, "x=%d, y=%d", x, y);

    putText(img2, text, cv::Point(5,15), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,0,0));
    cv::imshow("My Image", img2);
}

int main (void)
{
	image = cv::imread("img.jpg");
	cv::namedWindow("My Image");
	cv::setMouseCallback("My Image", onMouse, 0);
	cv::imshow("My Image",image);
	
	cv::waitKey(0);
	cvDestroyWindow("image");
	image.release();
	return 0;
}