#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;
void salt(cv::Mat &image, int n);
void printUsage();
int parseCmdArgs(int argc, char** argv);
bool try_use_gpu = false;
vector<Mat> imgs;
vector<Mat>::iterator myIimgs;
string result_name = "result.jpg";

int main(int argc, char *argv[])
{
  int height,width,step,channels;
  uchar *data;
  int i,j,k;
  cv::Mat image;
  int retval = parseCmdArgs(argc, argv);
  if (retval) return -1;
  int count = 0; 
  char buf[10];
  myIimgs = imgs.begin();
  while (myIimgs != imgs.end())
  {
		height    = myIimgs->size().height;
		width     = myIimgs->size().width;
		step      = myIimgs->step;
		channels  = myIimgs->channels();
		data      = (uchar *)myIimgs->data;
		// salt image
		salt(*myIimgs,10000);	
		//count = 0
		// print image
		_itoa(count,buf,10);
		strcat(buf,"_.jpg");
		cv::namedWindow(buf);
		cv::imshow(buf, *myIimgs);
		cv::imwrite(buf,*myIimgs);
//---------------------------------------------------------------------------------
		//reverse image
		count++;
        int PLAY = 100;
		for(i=0;i<height;i++)
			for(j=0;j<width;j++) 
				for(k=0;k<channels;k++)
					data[i*step+j*channels+k]=PLAY-data[i*step+j*channels+k];
		//-------------------------		
		_itoa(count,buf,10);
		strcat(buf,"_.jpg");
		cv::imwrite(buf,*myIimgs);
		cv::namedWindow(buf); 
		cv::imshow(buf, *myIimgs);
		//-------------------------
		// flip
		count++;		
		cv::Mat result; 
		cv::flip(*myIimgs,result,1);
		_itoa(count,buf,10);
		strcat(buf,"_.jpg");
		cv::imwrite(buf,result);
		cv::namedWindow(buf); 
		cv::imshow(buf, result);
		//-------------------------
		count++;		
		//--------------------------------------
		Size dynSize(0, 0);
		dynSize.width = width;
		dynSize.height = height;
		int dynType = CV_8UC1;
		cv::Mat dst(dynSize,dynType);
		cv::Size s;
		s.height = height/2;
		s.width = width/2;
		cv::resize(*myIimgs, dst,s,0.0,0.0,1);  
		_itoa(count,buf,10);
		strcat(buf,"_.jpg");
		cv::imwrite(buf,dst);
		cv::namedWindow(buf); 
		cv::imshow(buf, dst);
		count++;		

		myIimgs++;
  }
  cv::waitKey(0);	
 
  return 0;
}
void printUsage()
{
    cout <<
        "\n";
}


int parseCmdArgs(int argc, char** argv)
{
	
    if (argc == 1)
    {
        printUsage();
        return -1;
    }
    for (int i = 1; i < argc; ++i)
    {
            Mat img = imread(argv[i]);
            if (img.empty())
            {
                cout << "Can't read image '" << argv[i] << "'\n";
                return -1;
            }
            imgs.push_back(img);
    }
	
    return 0;
}
void salt(cv::Mat &image, int n)
{ 
	for (int k=0; k<n; k++) 
	{ 
		int i= rand()%image.cols;
		int j= rand()%image.rows; 
		if (image.channels() == 1) 
		{ 
			image.at<uchar>(j,i)= 255;
		} 
		else
		if (image.channels() == 3) 
		{ 
			image.at<cv::Vec3b>(j,i)[0]= 255;
			image.at<cv::Vec3b>(j,i)[1]= 0;
			image.at<cv::Vec3b>(j,i)[2]= 255; 			
		} 
	}
}

