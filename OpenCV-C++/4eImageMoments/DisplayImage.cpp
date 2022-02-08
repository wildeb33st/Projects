#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>


using namespace cv;
using namespace std;

int thresh = 100;
int max_thresh = 255;
RNG rng(12345);
void thresh_callback(int, void* );

Mat EqIm, dst;


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

    blur( EqIm, EqIm, Size(3,3) );

    const char* source_window = "Equalised Image";
    namedWindow( source_window, WINDOW_NORMAL );
    imshow( source_window, EqIm );
    createTrackbar( " Canny thresh:", "Equalised Image", &thresh, max_thresh, thresh_callback );
    thresh_callback( 0, 0 );

    waitKey(0);
    return 0;
}

void thresh_callback(int, void* )
{
  Mat canny_output;
  vector<vector<Point> > contours;
  Canny( EqIm, canny_output, thresh, thresh*2, 3 );
  findContours( canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE );
  vector<Moments> mu(contours.size() );
  for( size_t i = 0; i < contours.size(); i++ )
     { mu[i] = moments( contours[i], false ); }
  vector<Point2f> mc( contours.size() );
  for( size_t i = 0; i < contours.size(); i++ )
     { mc[i] = Point2f( static_cast<float>(mu[i].m10/mu[i].m00) , static_cast<float>(mu[i].m01/mu[i].m00) ); }
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  for( size_t i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours, (int)i, color, 2, LINE_8 );
       circle( drawing, mc[i], 4, color, -1, 8, 0 );
     }
  namedWindow( "Contours", WINDOW_NORMAL );
  imshow( "Contours", drawing );
  printf("\t Info: Area and Contour Length \n");
  for( size_t i = 0; i< contours.size(); i++ )
     {
       printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", (int)i, mu[i].m00, contourArea(contours[i]), arcLength( contours[i], true ) );
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours, (int)i, color, 2, LINE_8 );
       circle( drawing, mc[i], 4, color, -1, 8, 0 );
     }
}
