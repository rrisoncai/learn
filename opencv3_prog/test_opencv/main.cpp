#include <iostream>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat srcImage = imread(argv[1], 0);

    if(srcImage.data == nullptr)
    {
      cerr << "file not exist" << endl;
      return 0;
    }
    imshow("image",srcImage);
    waitKey(0);

    return 0;
}
