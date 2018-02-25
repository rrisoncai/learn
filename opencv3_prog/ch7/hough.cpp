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

    Mat src, dst, mid;
    src = imread(argv[1]);

    Canny(src, mid, 50, 200, 3);
    cvtColor(mid, dst, CV_GRAY2BGR);

    vector<Vec2f> lines;
    HoughLines(mid, lines, 1, CV_PI/180, 150, 0, 0);

    for(int i = 0; i < lines.size(); ++i) {
        float rho = lines[i][0];
        float theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta);
        double b = sin(theta);
        double x0 = a * rho;
        double y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * a);
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * a);
        line(dst, pt1, pt2, Scalar(55,100,195),1,LINE_AA);
    }
    imshow("hough", mid);
    imshow("effect", dst);
    waitKey(0);
    return 0;
}
