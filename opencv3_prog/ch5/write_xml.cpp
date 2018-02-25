#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    FileStorage fs("test.yaml", FileStorage::WRITE);

    fs << "frameCount" << 5;
    time_t rawtime;
    time(&rawtime);

    fs << "calibrationData" << asctime(localtime(&rawtime));
    Mat cameraMat = (Mat_<double>(3,3) << 1000,0, 320, 0, 1000, 240, 0, 0, 1);
    Mat distCoef = (Mat_<double>(5,1) << 0.1, 0.01, -0.001, 0, 0);
    fs << "cameraMat" << cameraMat << "distCoef" << distCoef;
    fs << "features" << "[";
    for(int i = 0; i < 3; ++i) {
        int x = rand() % 640;
        int y = rand() % 480;
        uchar lbp = rand() %256;

        fs << "{:" << "x" << x << "y" << y << "lbp" << "[:";
        for(int j = 0; j < 8; ++j) {
            fs << ((lbp >> j) & i);
        }
        fs << "]" << "}";
    }
    fs << "]";
    fs.release();
    printf("output done\n");
    getchar();
    return 0;
}
