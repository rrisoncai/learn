#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

void createAlphaMat(Mat &mat)
{
    for(int i = 0; i < mat.rows; ++i)
    {
        for(int j = 0; j < mat.cols; ++j)
        {
            Vec4b& rgba = mat.at<Vec4b>(i,j);
            rgba[0] = UCHAR_MAX;
            rgba[1] = saturate_cast<uchar>((float(mat.cols - j)) /
                    ((float)mat.cols) * UCHAR_MAX);
            rgba[2] = saturate_cast<uchar>((float(mat.rows - i)) /
                    ((float)mat.rows) * UCHAR_MAX);
            rgba[3] = saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
        }
    }
}


int main()
{
    Mat mat(480, 640, CV_8UC4);
    createAlphaMat(mat);

    vector<int> compression_params;
    compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);

    try
    {
        imwrite("alpha.png", mat, compression_params);
        imshow("png", mat);
        fprintf(stdout, "PNG alpha\n");
        waitKey(0);

    }
    catch(runtime_error& ex)
    {
        fprintf(stderr," error png:%s\n", ex.what());
        return 1;
    }

    // image loading and show
    Mat girl = imread("air.png");
    namedWindow("anime");
    imshow("anime", girl);
    waitKey(0);
    return 0;
}
