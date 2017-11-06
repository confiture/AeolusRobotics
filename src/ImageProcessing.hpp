#include <opencv2/opencv.hpp>


class FindRegion{
public:
    FindRegion(const cv::Mat & image,unsigned int i,unsigned int j,double distance);

    inline cv::Mat & resultVizualisation()const{return _output_visualization;}
	    
protected:
    const cv::Mat & _image;
    double _sqDist;
    mutable cv::Mat _output_visualization;
    cv::Vec3b _ref_pixel_val;
    std::vector<std::vector<bool> > _done_pixels;
    
    static double sqDistance(const cv::Vec3b & vec1,const cv::Vec3b & vec2);

    std::pair<int,int> undoneNeighbour(const std::pair<int,int> & cur_pix);
};
