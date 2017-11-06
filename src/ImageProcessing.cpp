#include "ImageProcessing.hpp"
#include <vector>
#include <stack>
#include <math.h>

void ImageProcessing::findRegion(const cv::Mat & image,unsigned int row,unsigned int col,
				 double distance,cv::Mat & output){
    std::vector<std::vector<int> >  done_pixels(image.rows);
    for(unsigned int i = 0; i < image.rows; ++i){
	done_pixels[i].resize(0,image.cols);
	for(unsigned int j = 0; j < image.cols; ++j)
	    done_pixels[i][j] = 0;

    }

    cv::Vec3b ref_pixel = image.at<cv::Vec3b>(row,col);
       
    double dist2 = distance*distance;

    bool end = false;

    while(!end){
	
    }
}


double ImageProcessing::sqDistance(const cv::Vec3b & vec1,const cv::Vec3b & vec2){
    return pow(vec1[0] - vec2[0],2) + pow(vec1[1] - vec2[1],2) +
	pow(vec1[2] - vec2[2],2);
}
