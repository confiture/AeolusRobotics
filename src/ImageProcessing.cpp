#include "ImageProcessing.hpp"
#include <vector>
#include <stack>
#include <math.h>
#include <iostream>

FindRegion::FindRegion(const cv::Mat & image,unsigned int row,unsigned int col,
			    double distance) : _image(image){    
    _done_pixels.resize(image.rows);

    for(unsigned int i = 0; i < _image.rows; ++i){
    	_done_pixels[i].resize(image.cols,false);
    }

    std::stack<std::pair<int,int> > pixel_stack;
	
    _ref_pixel_val = _image.at<cv::Vec3b>(row,col);
    std::pair<int,int> cur_pixel(row,col);
    
       
    _sqDist = distance*distance;

    do{
    	if(cur_pixel.first != -1){
    	    if(!_done_pixels[cur_pixel.first][cur_pixel.second]){
    		_done_pixels[cur_pixel.first][cur_pixel.second] = true;
    		pixel_stack.push(cur_pixel);
    	    }

    	    cur_pixel = undoneNeighbour(cur_pixel);
    	}
    	else{
    	    cur_pixel = pixel_stack.top();
    	    pixel_stack.pop();
    	}
    }
    while(pixel_stack.size() > 0);
}


double FindRegion::sqDistance(const cv::Vec3b & vec1,const cv::Vec3b & vec2){
    return pow(vec1[0] - vec2[0],2) + pow(vec1[1] - vec2[1],2) +
	pow(vec1[2] - vec2[2],2);
}


std::pair<int,int> FindRegion::undoneNeighbour(const std::pair<int,int> & cur_pix){
    int nrows = _done_pixels.size();
    int ncols = _done_pixels[0].size();
    
    int i = cur_pix.first;
    int j = cur_pix.second;

    if(i - 1 > 0 && j - 1 >= 0 && !_done_pixels[i - 1][j - 1] &&
       sqDistance(_image.at<cv::Vec3b>(i - 1,j - 1),_ref_pixel_val) < _sqDist)
	return std::pair<int,int>    (i - 1,j - 1);

    if(j - 1 >= 0 && !_done_pixels[i][j - 1] &&
       sqDistance(_image.at<cv::Vec3b>(i,j - 1),_ref_pixel_val) < _sqDist)
	return std::pair<int,int>    (i,j - 1);

    if(i + 1 < nrows && j - 1 >= 0 && !_done_pixels[i + 1][j - 1] &&
       sqDistance(_image.at<cv::Vec3b>(i + 1,j - 1),_ref_pixel_val) < _sqDist)
	return std::pair<int,int>    (i + 1,j - 1);

    if(i + 1 < nrows && !_done_pixels[i + 1][j] &&
       sqDistance(_image.at<cv::Vec3b>(i + 1,j),_ref_pixel_val) < _sqDist)
	return std::pair<int,int>    (i + 1,j);

    if(i + 1 < nrows && j + 1 < ncols && !_done_pixels[i + 1][j + 1] &&
       sqDistance(_image.at<cv::Vec3b>(i + 1,j + 1),_ref_pixel_val) < _sqDist)
	return std::pair<int,int>    (i + 1,j + 1);

    if(j + 1 < ncols && !_done_pixels[i][j + 1] &&
       sqDistance(_image.at<cv::Vec3b>(i,j + 1),_ref_pixel_val) < _sqDist)
	return std::pair<int,int>    (i,j + 1);

    if(i - 1 >= 0 && j + 1 < ncols && !_done_pixels[i - 1][j + 1] &&
       sqDistance(_image.at<cv::Vec3b>(i - 1,j + 1),_ref_pixel_val) < _sqDist)
	return std::pair<int,int>    (i - 1,j + 1);

    if(i - 1 >= 0 && !_done_pixels[i - 1][j] &&
       sqDistance(_image.at<cv::Vec3b>(i - 1,j),_ref_pixel_val) < _sqDist)
	return std::pair<int,int>    (i - 1,j);

    return std::pair<int,int>(-1,-1);
}

FindPerimeter::FindPerimeter(const std::vector<std::vector<bool> > & input){
    
}
