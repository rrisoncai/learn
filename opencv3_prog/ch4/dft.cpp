#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    if(argc != 2) {
        cout << "Usage: dft path_of_image" << endl;
        return 1;
    }

    Mat img = imread(argv[1], 0);
    if(!img.data) {
        cout << "invalid image." << endl;
        return 1;
    }
    imshow("image", img);
    waitKey(0);

    // padding
    int m = getOptimalDFTSize(img.rows);
    int n = getOptimalDFTSize(img.cols);
    Mat pad;
    copyMakeBorder(
        img, pad,
        0, m - img.rows,
        0, n - img.cols,
        BORDER_CONSTANT, Scalar::all(0));

    cout << "padding:" << m << "\t" << n << endl;
    imshow("padding", pad);
    waitKey(0);

    Mat planes[] = {Mat_<float>(pad), Mat::zeros(pad.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);

    dft(complexI, complexI);
    split(complexI, planes);
    magnitude(planes[0], planes[1], planes[0]);
    Mat magImg = planes[0];
    magImg += Scalar::all(1);
    log(magImg, magImg);

    // trim to even row and col
    magImg = magImg(Rect(0,0,magImg.cols & -2, magImg.rows & -2));
    int cx = magImg.cols / 2;
    int cy = magImg.rows / 2;
    Mat q0(magImg, Rect(0,0,cx,cy));
    Mat q1(magImg, Rect(cx,0,cx,cy));
    Mat q2(magImg, Rect(0,cy,cx,cy));
    Mat q3(magImg, Rect(cx,cy,cx,cy));

    // switch, q0<->q3, q1<->q2
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magImg, magImg, 0, 1, NORM_MINMAX);
    imshow("freq", magImg);
    waitKey(0);

    return 0;
}
