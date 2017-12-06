#include <iostream>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

// image processing header file
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat srcImage = imread(argv[1], 1);

    if(srcImage.data == nullptr)
    {
      cerr << "file not exist" << endl;
      return 0;
    }
    imshow("image",srcImage);
    waitKey(0);
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    Mat dstImage, edge, grayImage;

    // erode
    erode(srcImage, dstImage, element);
    imshow("erode", dstImage);
    waitKey(0);

    // blur
    blur(srcImage, dstImage, Size(7, 7));
    imshow("blur", dstImage);
    waitKey(0);

    // canny operator
    dstImage.create(srcImage.size(), srcImage.type());
    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

    blur(grayImage, edge, Size(3, 3));
    Canny(edge, edge, 3, 9, 3);
    imshow("canny", edge);
    waitKey(0);
    return 0;
}
