#pragma once

#include <opencv2/opencv.hpp>


class FindRegion{
public:
    /**
     * Find a contiguous patch of pixels that are similar in color to the first pixel
     * at position (i,j).
     * @param image the input image
     * @param i row index of the first pixel
     * @param j column index of the first pixel
     * @param distance the maximum distance allowed to pixels belongging to the same region
     */
    FindRegion(const cv::Mat & image,unsigned int i,unsigned int j,double distance);

    /**
     *Result accessor.
     */
    inline const std::vector<std::vector<bool> > & result()const{return _done_pixels;}

protected:
    const cv::Mat & _image;
    double _sqDist;
    cv::Vec3b _ref_pixel_val;
    std::vector<std::vector<bool> > _done_pixels;
    
    static double sqDistance(const cv::Vec3b & vec1,const cv::Vec3b & vec2);

    std::pair<int,int> undoneNeighbour(const std::pair<int,int> & cur_pix);
};

class FindPerimeter{
public:
    /**
     * FindPerimeter provides the perimeter from the FindRegion result.
     * @ param input the input binnary image representing the set of pixels.
     */
    FindPerimeter(const std::vector<std::vector<bool> > & input);

    /**
     *Result accessor.
     */
    inline const std::vector<std::vector<bool> > & result()const{return _output;}

protected:
    bool isInside(int i,int j)const;
    
    const std::vector<std::vector<bool> > & _input;
    std::vector<std::vector<bool> > _output;
};


class FindSmoothPerimeter{
public:
    FindSmoothPerimeter(const std::vector<std::vector<bool> > & input,int nsmoothing = 1);

    inline cv::Mat & result(){return _output_image;}
protected:
    double gaussFilterValue(int row,int col,const cv::Mat & image);
    
    cv::Mat _output_image;

    std::vector<std::vector<double> > _filter;
};
