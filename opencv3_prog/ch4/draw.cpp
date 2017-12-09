#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#include <iostream>
using namespace std;

#define WINDOW_WIDTH 600
#define WINDOW_NAME1 "Image 1"
#define WINDOW_NAME2 "Image 2"

void DrawEllipse(Mat img, double angle)
{
    int thickness = 2;
    int lineType = 8;

    ellipse(
        img,
        Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),
        Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),
        angle,
        0,
        360,
        Scalar(255, 129, 0),
        thickness,
        lineType);
}

void DrawFilledCircle(Mat img, Point center)
{
    int thickness = -1;
    int lineType = 8;

    circle(
        img,
        center,
        WINDOW_WIDTH / 32,
        Scalar(0, 0, 255),
        thickness,
        lineType
    );
}

int main()
{
    Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
    Mat rookImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

    DrawEllipse(atomImage, 90);
    DrawEllipse(atomImage, 0);
    DrawEllipse(atomImage, 45);
    DrawEllipse(atomImage, -45);

    DrawFilledCircle(atomImage, Point(WINDOW_WIDTH/2, WINDOW_WIDTH/2));

    imshow(WINDOW_NAME1, atomImage);
    moveWindow(WINDOW_NAME1, 0, 200);
    waitKey(0);
    return 0;
}
