#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    if(argc != 2) {
        cout << "usage: filter path_of_image." << endl;
        return 1;
    }

    Mat src = imread(argv[1]);
    Mat dst, edge, gray;

    dst.create(src.size(), src.type());
    cvtColor(src, gray, COLOR_RGB2GRAY);
    blur(gray, edge, Size(3,3));
    Canny(edge, edge, 3, 9, 3);
    dst = Scalar::all(0);
    src.copyTo(dst, edge);
    imshow("edge", dst);
    waitKey(0);

    Mat grad_x, grad_y, abs_grad_x, abs_grad_y;
    Sobel(src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);
    imshow("x sobel", abs_grad_x);


    Sobel(src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);
    imshow("y sobel", abs_grad_y);

    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5,0, dst);
    imshow("sobel", dst);
    waitKey(0);

    return 0;
}
