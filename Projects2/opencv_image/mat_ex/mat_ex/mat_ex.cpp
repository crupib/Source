// mat_ex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
int _tmain(int argc, _TCHAR* argv[])
{
	Mat N;
	Mat M(2,2, CV_8UC3, Scalar(0,255,255));
    cout << "M = " << endl << " " << M << endl << endl;
	N.create(2,2, CV_8UC(3));
    cout << "N = "<< endl << " "  << N << endl << endl;
	Mat E = Mat::eye(4, 4, CV_64F);
    cout << "E = " << endl << " " << E << endl << endl;
	Mat C = (Mat_<double>(3,3) << 0, -1.5, 0, -1.3, 5, -1, 0, -1, 0);
    cout << "C = " << endl << " " << C << endl << endl;
	Mat RowClone = C.row(1).clone();
    cout << "RowClone = " << endl << " " << RowClone << endl << endl;
	Mat R = Mat(3, 2, CV_8UC3);
    randu(R, Scalar::all(0), Scalar::all(255));
	cout << "R = " << endl << " " << R << endl << endl;
    cout << "R (python)  = " << endl << format(R,"python") << endl << endl;
	cout << "R (csv)     = " << endl << format(R,"csv"   ) << endl << endl;

	return 0;
}

