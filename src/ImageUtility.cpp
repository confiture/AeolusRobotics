#include "ImageUtility.hpp"
#include <iostream>

namespace ImageUtility{

    void displayImage(const cv::Mat & image,std::string win_name){
	namedWindow(win_name, cv::WINDOW_AUTOSIZE);
	cv::imshow(win_name, image);
	cv::waitKey(0);
    }

    void displayPixels(const std::vector<std::vector<bool> > & input,std::string win_name){
	cv::Mat output;
	buildImage(input,output);

	displayImage(output,win_name);
    }

    void buildImage(const std::vector<std::vector<bool> > & input,cv::Mat & output){
	int nrows,ncols;
	nrows = input.size();
	ncols = input[0].size();

	output = cv::Mat(nrows,ncols,CV_8UC1);

	for(unsigned int i = 0; i < nrows; ++i){
	    for(unsigned int j = 0; j < ncols; ++j){
		if(!input[i][j])
		    output.at<uchar>(i,j) = 0;//cv::Vec3b(0,0,0);
		else
		    output.at<uchar>(i,j) = 255;//_ref_pixel_val;
	    }
	}
    }
}
