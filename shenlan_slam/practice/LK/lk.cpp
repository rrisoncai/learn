#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <chrono>

using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/video/tracking.hpp>

int main(int argc, int** argv)
{
    if(argc != 2)
    {
        return 1;
    }
    string path_to_dataset = argv[1];
    string associate_file = path_to_dataset + "/associate.txt";

    ifstream fin(associate_file);
    if(!fin)
    {
        return 1;
    }

    string rgb_file, depth_file, time_rgb, time_depth;
    list<cv::Point2f> keypoints;
    cv::Mat color, depth, last_color;

    for(int index = 0; index != 100; ++index)
    {
        fin >> time_rgb >> rgb_file >> time_depth >> depth_file;
        color = cv::imread(path_to_dataset + "/" + rgb_file);
        depth = cv::imread(path_to_dataset + "/" + depth_file, -1);

        if(index == 0)
        {
            vector<cv::Keypoint> kps;
            cv::Ptr<cv::FastFeatureDetector> detector = cv::FastFeatureDetector::create();
            detector->detect(color,kps);
            for(auto kp:kps)
            {
                keypoints.push_back(kp.pt);
            }
            last_color = color;
            continue;
        }
        if(color.data == nullptr || depth.data == nullptr)
        {
            continue;
        }

        vector<cv::Point2f> next_keypoints;
        vector<cv::Point2f> prev_keypoints;

        for(auto kp:keypoints)
        {
            prev_keypoints.push_back(kp);
        }
        vector<unsigned char> status;
        vector<float> error;
        cv::calcOpticalFlowPyrLK(
            last_color,
            color,
            prev_keypoints,
            next_keypoints,
            status,
            error);

    }
}
