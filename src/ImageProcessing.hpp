#include <opencv2/opencv.hpp>


class ImageProcessing{
public:
    //ImageProcessing(const cv::Mat & image) : _image(image){}

    static void findRegion(const cv::Mat & image,unsigned int i,unsigned int j,double distance,
			   cv::Mat & output);
    
protected:
    static double sqDistance(const cv::Vec3b & vec1,const cv::Vec3b & vec2);

    static std::pair<int,int> undoneNeighbour(const std::pair<int,int> & cur_pix,
					      const std::vector<std::vector<bool> > & done_pix,
					      const cv::Mat & image, const cv::Vec3b & ref_pixel_val,
					      double sqDist);

    // const cv::Mat & _image;
    
    ImageProcessing(){}

};
