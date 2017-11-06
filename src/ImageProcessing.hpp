#include <opencv2/opencv.hpp>


class ImageProcessing{
public:
    //ImageProcessing(const cv::Mat & image) : _image(image){}

    static void findRegion(const cv::Mat & image,unsigned int i,unsigned int j,double distance,
			   cv::Mat & output);
    
protected:
    static double sqDistance(const cv::Vec3b & vec1,const cv::Vec3b & vec2);
    
    // const cv::Mat & _image;
    
    ImageProcessing(){}

};
