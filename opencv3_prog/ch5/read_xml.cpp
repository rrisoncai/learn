#include <opencv2/opencv.hpp>
#include <time.h>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int main() {
    system("color 6F");

    FileStorage fs("test.yaml", FileStorage::READ);

    int frameCount = (int)fs["frameCount"];
    string date;
    fs["calibrationData"] >> date;

    Mat cameraMat, distCoef;
    fs["cameraMat"] >> cameraMat;
    fs["distCoef"] >> distCoef;

    cout << "frameCount:" << frameCount << endl
    << "calibrationData:" << date << endl
    << "cameraMat:" << cameraMat << endl
    << "distCoef: " << distCoef << endl;

    FileNode features = fs["features"];
    FileNodeIterator it = features.begin(), it_end = features.end();
    int idx = 0;
    vector<uchar> lbpval;

    for(;it != it_end; ++it, ++idx) {
        cout << "features #" << idx << ": ";
        cout << "x=" << (int)(*it)["x"] << ",y=" << (int)(*it)["y"] << ",lbp:(";
        (*it)["lbp"] >> lbpval;
        for(int i = 0; i < (int)lbpval.size(); ++i) {
            cout << " " << (int)lbpval[i];
        }
        cout << ")" << endl;
    }
    fs.release();
    printf("\n read done\n");
    getchar();
    return 0;

}
