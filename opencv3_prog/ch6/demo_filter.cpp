#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3, g_dstImage4, g_dstImage5;
int g_nBoxfilterValue = 3;
int g_nMeanBlurValue = 3;
int g_nGaussianBlurValue = 3;
int g_nMedianBlurValue = 10;
int g_nBilateralFilterValue = 10;

string BOX_WINDOW("box filter");
string MEA_WINDOW("mean window");
string GAU_WINDOW("gauss window");
string MED_WINDOW("median window");
string BIL_WINDOW("bilateral filter");

static void on_BoxFilter(int, void*);
static void on_MeanBlur(int, void*);
static void on_GaussianBlur(int, void*);
static void on_MedianBlur(int, void*);
static void on_BilateralFilter(int, void*);

int main(int argc, char** argv)
{
    if(argc != 2) {
        cout << "usage: demo_filter path_of_image." << endl;
        return 1;
    }
    g_srcImage = imread(argv[1], 1);
    if(!g_srcImage.data) {
        cout << "invalid file." << endl;
        return 1;
    }
    g_dstImage1 = g_srcImage.clone();
    g_dstImage2 = g_srcImage.clone();
    g_dstImage3 = g_srcImage.clone();

    namedWindow("original",1);
    imshow("original", g_srcImage);

    namedWindow(BOX_WINDOW,1);
    createTrackbar("kernel:",BOX_WINDOW, &g_nBoxfilterValue, 40, on_BoxFilter);
    on_BoxFilter(g_nBoxfilterValue,0);
    //imshow("Box filter", g_dstImage1);

    namedWindow(MEA_WINDOW,1);
    createTrackbar("kernel:",MEA_WINDOW, &g_nMeanBlurValue, 40, on_MeanBlur);
    on_MeanBlur(g_nMeanBlurValue,0);

    namedWindow(GAU_WINDOW,1);
    createTrackbar("kernel:",GAU_WINDOW, &g_nGaussianBlurValue, 40, on_GaussianBlur);
    on_GaussianBlur(g_nGaussianBlurValue,0);

    namedWindow(MED_WINDOW,1);
    createTrackbar("param:",MED_WINDOW, &g_nMedianBlurValue, 50, on_MedianBlur);
    on_GaussianBlur(g_nMedianBlurValue,0);

    namedWindow(BIL_WINDOW,1);
    createTrackbar("param:",BIL_WINDOW, &g_nBilateralFilterValue, 50, on_BilateralFilter);
    on_GaussianBlur(g_nBilateralFilterValue,0);

    cout << "press q to quit" << endl;
    while(char(waitKey(1)) != 'q') {}
    return 0;
}

static void on_BoxFilter(int, void*) {
    boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxfilterValue+1,g_nBoxfilterValue+1));
    imshow(BOX_WINDOW, g_dstImage1);
}
static void on_MeanBlur(int, void*) {
    blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurValue+1, g_nMeanBlurValue+1),Point(-1,-1));
    imshow(MEA_WINDOW, g_dstImage2);
}
static void on_GaussianBlur(int, void*) {
    GaussianBlur(
        g_srcImage, g_dstImage3,
        Size(g_nGaussianBlurValue*2+1,g_nGaussianBlurValue*2+1),
        0,0);
    imshow(GAU_WINDOW, g_dstImage3);
}
static void on_MedianBlur(int, void*) {
    medianBlur(g_srcImage, g_dstImage4, g_nMedianBlurValue*2+1);
    imshow(MED_WINDOW, g_dstImage4);
}
static void on_BilateralFilter(int, void*) {
    bilateralFilter(g_srcImage, g_dstImage5,g_nBilateralFilterValue,g_nBilateralFilterValue*2,g_nBilateralFilterValue/2);
    imshow(BIL_WINDOW,g_dstImage5);
}
