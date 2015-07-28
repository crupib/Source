
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

using namespace cv;

double alpha; /**< Simple contrast control */
int beta;  /**< Simple brightness control */
Mat gamma;

/**
* Rotate an image
*/
void myrotate(cv::Mat& src, double angle, cv::Mat& dst)
{
	int len = std::max(src.cols, src.rows);
	cv::Point2f pt(len / 2., len / 2.);
	cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);
	cv::warpAffine(src, dst, r, cv::Size(len, len));
}
void  on_trackbar(int position)
{
	int TP;
	Mat tmp = Mat::zeros(gamma.size(), gamma.type());
	TP = getTrackbarPos("Alpha", "Gamma");
	for (int y = 0; y < gamma.rows; y++)
	{
		for (int x = 0; x < gamma.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				tmp.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha*(gamma.at<Vec3b>(y, x)[c]) + TP);
			}
		}
	}
	gamma = tmp.clone();
}

int main(int argc, char** argv)
{
	/// Read image given by user
	Mat image = imread(argv[1]);
	gamma = Mat::zeros(image.size(), image.type());
	Mat new_Sharp_image = Mat::zeros(image.size(), image.type());
	Mat thumbnail = Mat::zeros(image.size(), image.type());
	Mat rotate = Mat::zeros(image.size(), image.type());
	Mat contrast_stretch = Mat::zeros(image.size(), image.type());

	double imagesize;
	/// Initialize values
	std::cout << " Basic Linear Transforms " << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "* Enter the alpha value [1.0-3.0]: "; std::cin >> alpha;
	std::cout << "* Enter the beta value [0-100]: "; std::cin >> beta;

	/// Do the operation new_image(i,j) = alpha*image(i,j) + beta
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				gamma.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}
	Size size(32, 32);
	cv::resize(image, thumbnail, size);
	cv::GaussianBlur(image, new_Sharp_image, cv::Size(0, 0), 3);
	cv::addWeighted(image, 1.5, new_Sharp_image, -0.5, 0, new_Sharp_image);
	cv::normalize (image, contrast_stretch, 0, 1000, CV_MINMAX);
	myrotate(image, 90, rotate);
	/// Create Windows
	namedWindow("Original Image", WINDOW_NORMAL);
	namedWindow("Gamma", WINDOW_NORMAL);
	resizeWindow("Gamma", 800, 400);
	namedWindow("Sharpen", 1);
	namedWindow("thumbnail", 1);
	namedWindow("rotate", 1);
	namedWindow("Contrast Stretch", 1);

	// Create Trackbar
	cvCreateTrackbar("Alpha", "Gamma", 0, 100, on_trackbar);
	/// Show stuff
	cvSetTrackbarPos("Alpha", "Gamma", beta);
	imshow("Original Image", image);
	imshow("Gamma", gamma);
	imshow("thumbnail Image", thumbnail);
	imshow("Sharpen Image", new_Sharp_image);
	imshow("Rotate Image", rotate);
	imshow("Contrast Stretch", contrast_stretch);
	
	/// Wait until user press some key
	waitKey();
	return 0;
}