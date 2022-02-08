#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
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
    Mat EqIm; /*Defining new Matrix for the Equalised Image*/
    equalizeHist( crop, EqIm );

    /*
    namedWindow ("crop", WINDOW_NORMAL);
    namedWindow ("EqIm", WINDOW_NORMAL);
    imshow( "crop", crop );
    imshow( "EqIm", EqIm );
    */

    double alpha; /*This is for contrast control*/
    int beta;    /*This parameter is for brightness adjustment*/
    /*These are also referred to as the gain and bias respectively. They are related by a simple linear formula g(x)= alpha*f(x) + beta*/


    Mat adjIm = Mat::zeros( image.size(), image.type() ); /*This is for the processed image. It is a matrix of zeros similar to initialising an int as zero*/

    /// Initialize values
    std::cout<<" Basic Linear Transforms "<<std::endl;
    std::cout<<"-------------------------"<<std::endl;
    std::cout<<"* Enter the alpha value [1.0-3.0]: ";std::cin>>alpha;
    std::cout<<"* Enter the beta value [0-100]: "; std::cin>>beta;

    /// Do the operation new_image(i,j) = alpha*image(i,j) + beta
    EqIm.convertTo(adjIm, -1, alpha, beta);

    /// Create Windows
    namedWindow("EqIm", WINDOW_NORMAL);
    namedWindow("Adjusted Image", WINDOW_NORMAL);

    /// Show stuff
    imshow("EqIm", EqIm);
    imshow("Adjusted Image", adjIm);

    waitKey(0);
    return 0;
}
