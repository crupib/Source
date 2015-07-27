
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

using namespace cv;

double alpha; /**< Simple contrast control */
int beta;  /**< Simple brightness control */
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
int main(int argc, char** argv)
{
	/// Read image given by user
	Mat image = imread(argv[1]);
	Mat new_image = Mat::zeros(image.size(), image.type());
	Mat new_Sharp_image = Mat::zeros(image.size(), image.type());
	Mat thumbnail = Mat::zeros(image.size(), image.type());
	Mat rotate = Mat::zeros(image.size(), image.type());

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
				new_image.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}
	Size size(32, 32);
	cv::resize(image, thumbnail, size);
	cv::GaussianBlur(image, new_Sharp_image, cv::Size(0, 0), 3);
	cv::addWeighted(image, 1.5, new_Sharp_image, -0.5, 0, new_Sharp_image);
	myrotate(image, 90, rotate);
	/// Create Windows
	namedWindow("Original Image", 1);
	namedWindow("Gamma", 1);
	namedWindow("Sharpen", 1);
	namedWindow("thumbnail", 1);
	namedWindow("rotate", 1);


	/// Show stuff
	imshow("Original Image", image);
	imshow("New Image", new_image);
	imshow("thumbnail Image", thumbnail);
	imshow("Sharpen Image", new_Sharp_image);
	imshow("rotate image", rotate);
	/// Wait until user press some key
	waitKey();
	return 0;
}