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
    // 7 ways of Mat init
    double time0 = static_cast<double>(getTickCount());
    Mat M(2,2,CV_8UC3,Scalar(0,0,255));
    cout << "M=" << endl << " " << M << endl << endl;

    Mat L;
    L.create(4,4,CV_8UC(2));
    cout << "L=" << endl << " " << L << endl << endl;

    Mat E = Mat::eye(4,4,CV_64F);
    cout << "E=" << endl << E << endl << endl;
    Mat O = Mat::ones(2,2,CV_32F);
    cout << "O=" << endl << O << endl << endl;
    Mat Z = Mat::zeros(3,3,CV_8UC1);
    cout << "Z=" << endl << Z << endl << endl;

    Mat C = (Mat_<double>(3,3) << 0,-1,0,-1,5,-1,0,-1,0);
    cout << "C=" << endl << C << endl << endl;
    Mat R = C.row(1).clone();
    cout << "R=" << endl << R << endl << endl;

    Mat r = Mat(10,3,CV_8UC3);
    randu(r,Scalar::all(0),Scalar::all(255));
    cout << "r=" << format(r,Formatter::FMT_PYTHON) << endl << endl;
    
    time0 = ((double)getTickCount() - time0) / getTickFrequency();
    cout << "running time:" << time0 << endl;

    return 0;
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
