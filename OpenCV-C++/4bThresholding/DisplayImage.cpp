#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>


using namespace cv;


Mat EqIm, dst, dst2;
int lowerb = 30;
int upperb = 197;

void mouseHandler(int event, int x, int y, int flags, void* param);


int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    Mat image;
    Mat grey; /* This is the matrix to hold the grey scaled image*/

    image = imread( argv[1], 1 );
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

    cvtColor (image, grey, COLOR_BGR2GRAY);

    /* The next lines will be for cropping the grey image*/

    /*The offsets represen the centre of the cropping operation. The initial image size is 3280x2464*/
    int offset_x = 0;
    int offset_y = 0;
    int width = 2000;
    int height = 1500;

    cv::Rect roi; /*Establishing the region of interest i.e. how much of the image is to be cropped.*/
    roi.x = offset_x;
    roi.y = offset_y;
    roi.width  = width;
    roi.height = height;

    /*Actual cropping of the image to the defined ROI */
    cv::Mat crop = grey(roi);

    /*The next step is Histogram Equalization*/
    equalizeHist( crop, EqIm );

    namedWindow("Equalised Image", WINDOW_NORMAL);
    imshow("Equalised Image", EqIm);





/*this is for bit plane plicing operation. you can view the different planes depenting on the uchar you & in the out1.at<uchar>(y, x) = line */
/*
    int cols, rows, x, y;
    cols = EqIm.cols;
    rows = EqIm.rows;
    printf("%d %d \n", EqIm.rows, EqIm.cols);
    Mat out1(rows, cols, CV_8UC1, Scalar(0));


    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            out1.at<uchar>(y, x) = (EqIm.at<uchar>(y, x) & uchar(128)) ? uchar(255) : uchar(0); //Here's where I AND by either 1,2,4,8,16,32,64, or 128 to get the corresponding bit planes
        }
    }

    namedWindow("out1", WINDOW_NORMAL);
    imshow("out1", out1);
*/


/*This is for applying Contrast Limited Adaptive Histogram Equalisation*/
Ptr<CLAHE> clahe = createCLAHE();
clahe->setClipLimit(10); /*Changing the Cliplimit to higher values, generally gives better contrast but may add to the noise */


clahe->apply(EqIm,dst);
namedWindow("CLAHE", WINDOW_NORMAL);
imshow("CLAHE",dst);

int mouseParam= CV_EVENT_FLAG_LBUTTON;
cvSetMouseCallback("CLAHE",mouseHandler, &dst);





    waitKey(0);
    return 0;
}

/* This function is used in determining the mouse event for detection and what to do after that event has occurred. It takes the left button to determine the lower boundary and the right button for the upper boundary. the image is displayed only after the right button is pressed */
void mouseHandler(int event, int x, int y, int flags, void* param)
{

if (event == CV_EVENT_LBUTTONDOWN)
    {
      lowerb = (int)dst.at<uchar>(Point(x, y));
      printf ("%d \n", lowerb );
    }
else if (event == CV_EVENT_RBUTTONDOWN)
   {
     upperb = (int)dst.at<uchar>(Point(x, y));
     printf ("%d \n", upperb);

    inRange (dst, lowerb, upperb, dst2);
    namedWindow("Threshold in Range", WINDOW_NORMAL);
    imshow("Threshold in Range", dst2);
   }
}
