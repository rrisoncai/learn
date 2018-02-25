#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage;
int g_nTrackbarNumer = 0;
int g_nStructElementSize = 3;

void Process(void);
void on_TrackbarNumChange(int,void*);
void on_ElementSizeChange(int,void*);

int main(int argc, char** argv) {
    if(argc != 2) {
        cout << "usage: moph path_of_image." << endl;
        return 1;
    }

    g_srcImage = imread(argv[1]);
    if(!g_srcImage.data) {
        cout << "Invalid image." << endl;
        return 1;
    }
    namedWindow("original");
    imshow("original", g_srcImage);

    namedWindow("erode");
    Mat element = getStructuringElement(
        MORPH_RECT,
        Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1),
        Point(g_nStructElementSize,g_nStructElementSize));
    erode(g_srcImage,g_dstImage,element);
    imshow("erode",g_dstImage);

    createTrackbar("erode/dialate","erode",&g_nTrackbarNumer,1,on_TrackbarNumChange);
    createTrackbar("kernel","erode",&g_nStructElementSize,21,on_ElementSizeChange);

    while(char(waitKey(1)) != 'q') {}
    return 0;
}

void Process(void) {
    Mat element = getStructuringElement(
        MORPH_RECT,
        Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1),
        Point(g_nStructElementSize,g_nStructElementSize));
    if(g_nTrackbarNumer == 0) {
        erode(g_srcImage,g_dstImage,element);
    }
    else {
        dilate(g_srcImage,g_dstImage,element);
    }
    imshow("erode",g_dstImage);
}

void on_TrackbarNumChange(int,void*) {
    Process();
}
void on_ElementSizeChange(int,void*) {
    Process();
}
