#include "ImageProcessing.hpp"
#include <vector>
#include <stack>
#include <math.h>

void ImageProcessing::findRegion(const cv::Mat & image,unsigned int row,unsigned int col,
				 double distance,cv::Mat & output){
    std::vector<std::vector<bool> >  done_pixels(image.rows);
    for(unsigned int i = 0; i < image.rows; ++i){
	done_pixels[i].resize(0,image.cols);
	for(unsigned int j = 0; j < image.cols; ++j)
	    done_pixels[i][j] = false;

    }

    std::stack<std::pair<int,int> > pixel_stack;
	
    cv::Vec3b ref_pixel_val = image.at<cv::Vec3b>(row,col);
    std::pair<int,int> cur_pixel(row,col);
    
       
    double dist2 = distance*distance;

    bool end = false;

    while(pixel_stack.size() > 0){
	if(cur_pixel.first != -1){
	    if(!done_pixels[cur_pixel.first][cur_pixel.second]){
		done_pixels[cur_pixel.first][cur_pixel.second] = true;
		pixel_stack.push(cur_pixel);
	    }

	    cur_pixel = undoneNeighbour(cur_pixel,done_pixels,image,ref_pixel_val,dist2);
	}
	else{
	    cur_pixel = pixel_stack.top();
	    pixel_stack.pop();
	}
    }

    output = image;

    for(unsigned int i = 0; i < image.rows; ++i){
	for(unsigned int j = 0; j < image.cols; ++j){
	    if(done_pixels[i][j])
		output.at<cv::Vec3b>(i,j) = cv::Vec3b(0,0,0);
	    else
		output.at<cv::Vec3b>(i,j) = ref_pixel_val;
	}
    }	    
}


double ImageProcessing::sqDistance(const cv::Vec3b & vec1,const cv::Vec3b & vec2){
    return pow(vec1[0] - vec2[0],2) + pow(vec1[1] - vec2[1],2) +
	pow(vec1[2] - vec2[2],2);
}


std::pair<int,int> ImageProcessing::undoneNeighbour(const std::pair<int,int> & cur_pix,
					      const std::vector<std::vector<bool> > & done_pix,
					      const cv::Mat & image, const cv::Vec3b & ref_pixel_val,
					      double sqDist){
    std::pair<int,int> ret(-1,-1);
    
    int nrows = done_pix.size();
    int ncols = done_pix[0].size();
    
    int i = cur_pix.first;
    int j = cur_pix.second;

    if(i - 1 > 0 && j - 1 >= 0 && !done_pix[i - 1][j - 1] &&
       sqDistance(image.at<cv::Vec3b>(i - 1,j - 1),ref_pixel_val) < sqDist)
	return std::pair<int,int>    (i - 1,j - 1);

    if(j - 1 >= 0 && !done_pix[i][j - 1] &&
       sqDistance(image.at<cv::Vec3b>(i,j - 1),ref_pixel_val) < sqDist)
	return std::pair<int,int>    (i,j - 1);

    if(i + 1 < nrows && j - 1 >= 0 && !done_pix[i + 1][j - 1] &&
       sqDistance(image.at<cv::Vec3b>(i + 1,j - 1),ref_pixel_val) < sqDist)
	return std::pair<int,int>    (i + 1,j - 1);

    if(i + 1 < nrows && !done_pix[i + 1][j] &&
       sqDistance(image.at<cv::Vec3b>(i + 1,j),ref_pixel_val) < sqDist)
	return std::pair<int,int>    (i + 1,j);

    if(i + 1 < nrows && j + 1 < ncols && !done_pix[i + 1][j + 1] &&
       sqDistance(image.at<cv::Vec3b>(i + 1,j + 1),ref_pixel_val) < sqDist)
	return std::pair<int,int>    (i + 1,j + 1);

    if(j + 1 < ncols && !done_pix[i][j + 1] &&
       sqDistance(image.at<cv::Vec3b>(i,j + 1),ref_pixel_val) < sqDist)
	return std::pair<int,int>    (i,j + 1);

    if(i - 1 >= 0 && j + 1 < ncols && !done_pix[i - 1][j + 1] &&
       sqDistance(image.at<cv::Vec3b>(i - 1,j + 1),ref_pixel_val) < sqDist)
	return std::pair<int,int>    (i - 1,j + 1);

    if(i - 1 >= 0 && !done_pix[i - 1][j] &&
       sqDistance(image.at<cv::Vec3b>(i - 1,j),ref_pixel_val) < sqDist)
	return std::pair<int,int>    (i - 1,j);

    return std::pair<int,int>(-1,-1);
}
