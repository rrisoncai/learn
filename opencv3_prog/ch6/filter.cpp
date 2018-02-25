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

    Mat img = imread(argv[1]);
    Mat out;

    imshow("original", img);
    waitKey(0);

    boxFilter(img, out, -1, Size(5,5));
    imshow("average filter", out);
    waitKey(0);

    blur(img, out, Size(7,7));
    imshow("blur filter", out);
    waitKey(0);

    GaussianBlur(img, out, Size(3,3),0,0);
    imshow("gauss blur filter", out);
    waitKey(0);


    return 0;
}
