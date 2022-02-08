#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;


Mat dst, EqIm, adIm;

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


    int kernel_size = 3;
    int scale = 1;
    int delta = 10;
    int ddepth = CV_8U;//CV_16S;
    const char* window_name = "Laplace Demo";


    // Reduce noise by blurring with a Gaussian filter ( kernel size = 3 )
   // GaussianBlur( EqIm, EqIm, Size(3, 3), 0, 0, BORDER_DEFAULT );
    Mat abs_dst;
    Laplacian( EqIm, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
    // converting back to CV_8U
    convertScaleAbs( dst, abs_dst );
    namedWindow(window_name, WINDOW_NORMAL);
    imshow( window_name, abs_dst );

    double alpha = 0.5; double beta; double input;
    namedWindow("Linear Blend", WINDOW_NORMAL);
    beta = ( 1.0 - alpha );
    addWeighted( EqIm, alpha, dst, beta, 0.0, adIm);
    imshow( "Linear Blend", adIm );


    waitKey(0);
    return 0;
}

