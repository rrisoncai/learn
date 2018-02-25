#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define WINDOW_NAME "window"

int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_grayImage, g_dstImage;

static void ShowHelpText();
void on_Threshold(int, void*);

int main(int argc, char** argv) {
    if(argc != 2) {
        cout << "usage: filter path_of_image." << endl;
        return 1;
    }
    g_srcImage = imread(argv[1]);
    cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);

    createTrackbar("mode",WINDOW_NAME,&g_nThresholdType,4,on_Threshold);
    createTrackbar("param",WINDOW_NAME,&g_nThresholdValue,255,on_Threshold);

    on_Threshold(0,0);

    while(true) {
        int key = waitKey(20);
        if((char)key == 27) {break;}
    }
    return 0;
}

void on_Threshold(int, void*) {
    threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
    imshow(WINDOW_NAME, g_dstImage);
}
