#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;

int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;
const char* window_name = "Morphology Transformations Demo";
void Morphology_Operations( int, void* );

Mat dst, EqIm;

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
//    Mat EqIm; /*Defining new Matrix for the Equalised Image*/
    equalizeHist( crop, EqIm );

    namedWindow( window_name, WINDOW_NORMAL ); // Create window
     createTrackbar("Operator:\n 0: Opening - 1: Closing  \n 2: Gradient - 3: Top Hat \n 4: Black Hat", window_name, &morph_operator, max_operator, Morphology_Operations );
     createTrackbar( "Element:\n 0: Rect - 1: Cross - 2: Ellipse", window_name,
                     &morph_elem, max_elem,
                     Morphology_Operations );
     createTrackbar( "Kernel size:\n 2n +1", window_name,
                     &morph_size, max_kernel_size,
                     Morphology_Operations );
     Morphology_Operations( 0, 0 );



    waitKey(0);
    return 0;
}


void Morphology_Operations( int, void* )
{
  // Since MORPH_X : 2,3,4,5 and 6
  int operation = morph_operator + 2;
  Mat element = getStructuringElement( morph_elem, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
  morphologyEx( EqIm, dst, operation, element );
  imshow( window_name, dst );
}
