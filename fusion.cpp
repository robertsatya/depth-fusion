#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
	if(argc < 3)
	{
		cout << "Usage : fusion <depthimage1> <depthimage2>" << endl;
		exit(1);
	}

	Mat img1, img2, trans1, final;
	img1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	img2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);

	Mat trans = Mat::zeros(img1.rows,img1.cols,CV_8U);

	if(! img1.data )
	{
		cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}

	if(! img2.data )
	{
		cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}

	for(int i=0;i<img1.rows;i++) 
	{
		for (int j=0;j<img1.cols;j++)
		{
			//img1.at<uchar>(i,j) = 255; //white
			if(img1.at<uchar>(i,j) > img2.at<uchar>(i,j))
				trans.at<uchar>(i,j) = img1.at<uchar>(i,j);
			else
				trans.at<uchar>(i,j) = img2.at<uchar>(i,j);
		}
	}

	namedWindow( "LaserDepth", WINDOW_NORMAL );
	imshow( "LaserDepth", img1 );


	namedWindow( "ComputedDepth", WINDOW_NORMAL );
	imshow( "ComputedDepth", img2 );

	namedWindow( "FusedDepth", WINDOW_NORMAL );
	imshow( "FusedDepth", trans );

	waitKey(0);

	return 0;
}
