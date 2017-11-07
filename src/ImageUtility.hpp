#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>

/**
 * Provides set of utility functions for visualization and result saving.
 */
namespace ImageUtility{
    void displayImage(const cv::Mat & image,std::string win_name = "default");

    void displayPixels(const std::vector<std::vector<bool> > & input,std::string win_name = "default");

    void buildImage(const std::vector<std::vector<bool> > & input,cv::Mat & output);

    void savePixels(const std::vector<std::vector<bool> > & input,const std::string & filename);

    /**
     * Saves the binnary image input as a text file, filling it with "0" and "1".
     */
    void savePixelsTxt(const std::vector<std::vector<bool> > & input,const std::string & filename);

    void loadImage(const std::string & filename,cv::Mat & output);
}
