#include <iostream>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// image processing header file
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    VideoCapture capture(argv[1]);

    while(true)
    {
        Mat frame;
        capture >> frame;
        imshow("read video", frame);
        waitKey(30);
    }
    return 0;
}
