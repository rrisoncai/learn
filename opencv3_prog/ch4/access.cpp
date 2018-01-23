#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include<vector>

using namespace std;
using namespace cv;

void colorReduce(Mat& input, Mat& output, int div);
int main()
{
    vector<int> vi;
    vector<Mat> vm;
    /*
    Mat srcImage = imread("samurai.jpg");

    Mat dstImage;
    dstImage.create(srcImage.rows,srcImage.cols,srcImage.type());

    double time0 = static_cast<double>(getTickCount());
    colorReduce(srcImage,dstImage,32);
    time0 = ((double)getTickCount() - time0)/getTickFrequency();
    cout << "running time:" << time0 << endl;

    imshow("dstImg",dstImage);

    */
    Mat srcImage = imread("samurai.jpg");
    Mat logoImage = imread("logo.png");
    
    if(!srcImage.data)
        return 1;
    if(!logoImage.data)
        return 1;


    Mat imageROI = srcImage(Rect(200,250,logoImage.cols,logoImage.rows));
    Mat mask = imread("logo.png",0);
    logoImage.copyTo(imageROI,mask);

    namedWindow("roi");
    imshow("roi",srcImage);
    waitKey(0);

    return 0;
}

void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
    outputImage = inputImage.clone();

    // c style
    int rowNum = outputImage.rows;
    int colNum = outputImage.cols * outputImage.channels();

    for(int i = 0; i < rowNum; ++i)
    {
        uchar* data = outputImage.ptr<uchar>(i);
        for(int j = 0; j < colNum; ++j)
        {
            data[j] = data[j] / div * div + div / 2;
        }
    }
    // using iterator
    Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();
    Mat_<Vec3b>::iterator end = outputImage.end<Vec3b>();

    for(;it != end; ++it)
    {
        (*it)[0] = (*it)[0]/div*div+div/2;
        (*it)[1] = (*it)[1]/div*div+div/2;
        (*it)[2] = (*it)[2]/div*div+div/2;
    }
}
