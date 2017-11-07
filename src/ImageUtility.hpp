#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>

namespace ImageUtility{
    void displayImage(const cv::Mat & image,std::string win_name = "default");

    void displayPixels(const std::vector<std::vector<bool> > & input,std::string win_name = "default");

    void buildImage(const std::vector<std::vector<bool> > & input,cv::Mat & output);
    
}
