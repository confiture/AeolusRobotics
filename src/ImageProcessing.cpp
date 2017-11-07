#include "ImageProcessing.hpp"
#include <vector>
#include <stack>
#include <math.h>
#include <iostream>
#include "ImageUtility.hpp"

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

    if(i - 1 >= 0 && j - 1 >= 0 && !_done_pixels[i - 1][j - 1] &&
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

FindPerimeter::FindPerimeter(const std::vector<std::vector<bool> > & input) : _input(input){
    int nrows,ncols;
    nrows = input.size();
    ncols = input[0].size();

    _output = input;

    for(int i = 0; i < nrows; ++i)
	for(int j = 0; j < ncols; ++j)
	    if(isInside(i,j))
		_output[i][j] = false;
    
}


bool FindPerimeter::isInside(int i,int j)const{
    int nrows,ncols;
    nrows = _input.size();
    ncols = _input[0].size();
    
    
    if(!_input[i][j])
	return false;

    if(i > 0 && !(_input[i - 1][j]))
	return false;

    if(j > 0 && !(_input[i][j - 1]))
	return false;

    if(i + 1 < nrows && !(_input[i + 1][j]))
	return false;

    if(j + 1 < ncols && !(_input[i][j + 1]))
	return false;
    
    return true;
}


FindSmoothPerimeter::FindSmoothPerimeter(const std::vector<std::vector<bool> > & input,int nsmoothing){
    int nrows,ncols;
    nrows = input.size();
    ncols = input[0].size();
    
    _filter.resize(3);
    for(int i = 0; i < 3; ++i)
	_filter[i].resize(3);

    _filter[0][0] = _filter[2][0] = _filter[2][2] = _filter[0][2] = 1.0/16.0;
    _filter[0][1] = _filter[1][0] = _filter[2][1] = _filter[1][2] = 1.0/8.0;
    _filter[1][1] = 0.25;
    
    FindPerimeter find_sharp_perim(input);

    cv::Mat input_image;
    ImageUtility::buildImage(find_sharp_perim.result(),input_image);


    _output_image = input_image;
    
    //gaussian 3x3 filter
    for(int k = 0; k < nsmoothing; ++k)
    {
	for(int i = 1; i < nrows - 1; ++i){
	    for(int j = 1; j < ncols - 1; ++j){
		_output_image.at<uchar>(i,j) = gaussFilterValue(i,j,input_image);
	    }
	}
	input_image = _output_image;
    }
}


double FindSmoothPerimeter::gaussFilterValue(int row,int col,const cv::Mat & image){
    double val = 0;
    
    for(int i_filter = 0; i_filter < 3; ++i_filter)
	for(int j_filter = 0; j_filter < 3; ++j_filter)
	    val += _filter[i_filter][j_filter] *
		((double)image.at<uchar>(row - 1 + i_filter,col - 1 + j_filter));

    return val;
}
