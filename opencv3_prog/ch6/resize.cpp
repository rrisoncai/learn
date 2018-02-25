#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    if(argc != 2) {
        cout << "usage: filter path_of_image." << endl;
        return 1;
    }
    Mat srcImage = imread(argv[1]);
    Mat tmpImage = srcImage;
    Mat dstImage1, dstImage2;

    resize(tmpImage, dstImage1, Size(tmpImage.cols/2,tmpImage.rows/2),(0,0),(0,0),3);
    resize(tmpImage, dstImage2, Size(tmpImage.cols*2,tmpImage.rows*2),(0,0),(0,0),3);

    imshow("1",dstImage1);
    imshow("2",dstImage2);
    waitKey(0);
    return 0;
}
