#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define WINDOW_NAME "sample"

/* track bar variable */
const int g_nMaxAlphaValue = 100;
int g_nAlphaValueSlide;
double g_dAlphaValue;
double g_dBetaVAlue;

Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;
/* track bar variable */
void on_trackbar(int, void*)
{
    g_dAlphaValue = (double)g_nAlphaValueSlide / g_nMaxAlphaValue;
    g_dBetaVAlue = (1.0 - g_dAlphaValue);

    addWeighted(
        g_srcImage1,
        g_dAlphaValue,
        g_srcImage2,
        g_dBetaVAlue,
        0.0,
        g_dstImage);

        imshow(WINDOW_NAME, g_dstImage);
}

/* mouse event variable */
void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(cv::Mat& img, Rect box);
void ShowHelpText();

Rect g_rectangle;
bool g_bDrawingBox = false;
RNG g_rng(12345);
/* mouse event variable */
int main(int argc, char** argv)
{
    if(argc != 3)
    {
        printf("invalid argc\n");
        printf("./trackbar 1.png 2.png\n");
        return -1;
    }
    g_srcImage1 = imread(argv[1]);
    g_srcImage2 = imread(argv[2]);

    if(!g_srcImage1.data)
    {
        printf("image1 fail\n");
        return -1;
    }
    if(!g_srcImage2.data)
    {
        printf("image2 fail\n");
        return -1;
    }

    g_nAlphaValueSlide = 70;

    namedWindow(WINDOW_NAME, 1);

    char TracebarName[50];
    sprintf(TracebarName, "alpha value %d", g_nMaxAlphaValue);

    createTrackbar(
        TracebarName,
        WINDOW_NAME,
        &g_nAlphaValueSlide,
        g_nMaxAlphaValue,
        on_trackbar);

    on_trackbar(g_nAlphaValueSlide, 0);
    waitKey(0);

    // begin mouse event sample
    g_rectangle = Rect(-1, -1, 0, 0);
    Mat srcImage(600, 800, CV_8UC3), tmpImage;
    srcImage.copyTo(tmpImage);
    srcImage = Scalar::all(0);

    namedWindow(WINDOW_NAME);
    setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&srcImage);

    while(true)
    {
        srcImage.copyTo(tmpImage);
        if(g_bDrawingBox)
        {
            DrawRectangle(tmpImage, g_rectangle);
        }
        imshow(WINDOW_NAME, tmpImage);
        if(waitKey(10) == 27)
        {
            break;
        }
    }
    return 0;
}

void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
    Mat& image = *(Mat*)param;
    switch(event)
    {
        case EVENT_MOUSEMOVE:
        {
            if(g_bDrawingBox)
            {
                g_rectangle.width = x - g_rectangle.x;
                g_rectangle.height = y - g_rectangle.y;
            }
        }
        break;
        case EVENT_LBUTTONDOWN:
        {
            g_bDrawingBox = true;
            g_rectangle = Rect(x, y, 0, 0);
        }
        break;

        case EVENT_LBUTTONUP:
        {
            g_bDrawingBox = false;
            if(g_rectangle.width < 0)
            {
                g_rectangle.x += g_rectangle.width;
                g_rectangle.width *= -1;
            }
            if(g_rectangle.height < 0)
            {
                g_rectangle.y += g_rectangle.height;
                g_rectangle.height *= -1;
            }
            DrawRectangle(image, g_rectangle);
        }
        break;
    }
}

void DrawRectangle(Mat& img, Rect box)
{
    rectangle(
        img,
         box.tl(),
         box.br(),
         Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}
