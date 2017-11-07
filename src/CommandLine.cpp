#include "ImageProcessing.hpp"
#include "ImageUtility.hpp"

#include <tuple>
#include <iostream>
#include <string>
#include <sstream>
#include <map>


enum State{
    UNKNOWN,
    LOAD_IMAGE,
    DISPLAY_IMAGE,
    DISPLAY_PIXELS,    
    FIND_REGION,
    FIND_PERIMETER,
    SAVE_PIXELS,
    SAVE_PIXELS_TXT,
    WAITING,
    ANALYZE_COMMAND,
    QUIT
};

int main(){
    //loaded images variable names
    std::map<std::string,cv::Mat> loadedImages;

    //results from find region and find perimeter
    std::map<std::string,std::vector<std::vector<bool> > > pixelResults;

    //parameters for executing find_region
    std::tuple<cv::Mat,unsigned int,unsigned int,double> find_region_params;
    std::tuple<std::string,std::string> load_image_params;

    // param for display image
    cv::Mat * display_image_input;

    // param for display pixels
    std::vector<std::vector<bool> > * display_pixels_input;

    // used in the below state machine
    State cur_state = WAITING;

    std::string quit_str("quit");
    std::string load_image_str("load_image");
    std::string find_region_str("find_region");
    std::string find_perimeter_str("find_perimeter");
    std::string display_image_str("display_image");
    std::string display_pixels_str("display_pixels");
    std::string save_pixels_str("save_pixels");
    std::string save_pixels_txt_str("save_pixels_txt");

    std::string cur_word;
    
    bool end = false;

    while(!end){
    	switch(cur_state){

    	case WAITING:
    	    if(!(std::cin >> cur_word))
		cur_state == WAITING;
	    else
		cur_state = ANALYZE_COMMAND;
    	    break;

        case ANALYZE_COMMAND:
    	    if(cur_word == find_region_str)
    		cur_state = FIND_REGION;
    	    else if(cur_word == load_image_str)
    		cur_state = LOAD_IMAGE;
	    else if(cur_word == display_image_str)
		cur_state = DISPLAY_IMAGE;
	    else if(cur_word == display_pixels_str)
		cur_state = DISPLAY_PIXELS;
	    else if(cur_word == find_perimeter_str)
		cur_state = FIND_PERIMETER;
	    else if(cur_word == save_pixels_str)
		cur_state = SAVE_PIXELS;
	    else if(cur_word == save_pixels_txt_str)
		cur_state = SAVE_PIXELS_TXT;
	    else if(cur_word == quit_str)
		cur_state = QUIT;
    	    else{
    		std::cerr<<"unknown command: "<<cur_word<<std::endl;
    		cur_state = WAITING;
    	    }

    	    break;

	case QUIT:
	    end = true;
	    break;
	    
	case LOAD_IMAGE:
	    {
		std::string input_filename;
		std::cin>>input_filename;

		std::string var_name;
		std::cin>>var_name;

		ImageUtility::loadImage(input_filename,
					loadedImages[var_name]);

		cur_state = WAITING;
		break;
		
	    }

	case DISPLAY_IMAGE:
	    {
		std::string image_name;
		std::cin>>image_name;

		ImageUtility::displayImage(loadedImages[image_name]);

		cur_state = WAITING;
		break;
	    }

	case DISPLAY_PIXELS:
	    {
		std::string pixel_name;
		std::cin>>pixel_name;

		ImageUtility::displayPixels(pixelResults[pixel_name]);

		cur_state = WAITING;
		break;
	    }

	case FIND_REGION:
	    {
		std::cin>>cur_word;
		const cv::Mat & image = loadedImages[cur_word];

		int i,j;
		std::cin>>i;
		std::cin>>j;

		double distance;
		std::cin>>distance;

		std::string output_pixels_name;
		std::cin>>output_pixels_name;

		FindRegion find_region(image,i,j,distance);

		pixelResults[output_pixels_name] = find_region.result();

		cur_state = WAITING;
		break;
	    }
	    
	case FIND_PERIMETER:
	    {
		std::cin>>cur_word;
		const std::vector<std::vector<bool> > & pixels = pixelResults[cur_word];

		std::string output_pixels_name;
		std::cin>>output_pixels_name;

		FindPerimeter find_perim(pixels);

		pixelResults[output_pixels_name] = find_perim.result();

		cur_state = WAITING;
		break;
	    }

	case SAVE_PIXELS:
	    {
		std::cin>>cur_word;
		const std::vector<std::vector<bool> > & pixels = pixelResults[cur_word];

		std::string output_filename;
		std::cin>>output_filename;

		ImageUtility::savePixels(pixels,output_filename);
		
		cur_state = WAITING;
		break;
	    }

	case SAVE_PIXELS_TXT:
	    {
		std::cin>>cur_word;
		const std::vector<std::vector<bool> > & pixels = pixelResults[cur_word];

		std::string output_filename;
		std::cin>>output_filename;

		ImageUtility::savePixelsTxt(pixels,output_filename);
		
		cur_state = WAITING;
		break;
	    }
    	}

    }

    
    return 0;
}
