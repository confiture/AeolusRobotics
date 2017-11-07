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
    LOAD_IMAGE_INPUT,
    LOAD_IMAGE_OUTPUT,
    LOAD_IMAGE_EXEC,
    DISPLAY_IMAGE,
    DISPLAY_IMAGE_INPUT,
    DISPLAY_IMAGE_EXEC,
    DISPLAY_PIXELS,
    DISPLAY_PIXELS_INPUT,
    DISPLAY_PIXELS_EXEC,
    
    FIND_REGION,
    FIND_PERIMETER,
    FIND_REGION_INPUT,
    FIND_REGION_ROW,
    FIND_REGION_COL,
    FIND_REGION_DIST,
    FIND_REGION_READY,
    WAITING,
    ANALYZE_COMMAND,
    QUIT
};

void tests(){
    std::string input;
    std::string output;
    std::stringstream ss;

    std::cin>>input;
    std::cout<<input<<std::endl;
    std::cin>>input;
    std::cout<<input<<std::endl;
    std::cin>>input;
    std::cout<<input<<std::endl;
}

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

    
    
    std::stringstream commands_stream;
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
    	    else{
    		std::cerr<<"unknown command: "<<cur_word<<std::endl;
    		cur_state = WAITING;
    	    }

    	    break;

    	case LOAD_IMAGE:
	    std::cout<<"load image state"<<std::endl;
	    cur_state = LOAD_IMAGE_INPUT;
	    break;

	case LOAD_IMAGE_INPUT:
	    std::cout<<"load image input state"<<std::endl;
    	    if(!(std::cin >> cur_word)){
    		std::cerr<<"Wrong use of load image : load_image input_filename output_name"<<std::endl;
		cur_state = WAITING;

		break;
	    }

	    std::get<0>(load_image_params) = cur_word;

	    cur_state = LOAD_IMAGE_OUTPUT;
	    break;
	    
	case LOAD_IMAGE_OUTPUT:
	    std::cout<<"load image output state"<<std::endl;
	    
    	    if(!(std::cin >> cur_word)){
    		std::cerr<<"Wrong use of load image : load_image input_filename output_name"<<std::endl;
		cur_state = WAITING;

		break;
	    }

	    std::get<1>(load_image_params) = cur_word;
	    
	    cur_state = LOAD_IMAGE_EXEC;
	    break;

	case LOAD_IMAGE_EXEC:
	    std::cout<<"load image exec state"<<std::endl;
	    ImageUtility::loadImage(std::get<0>(load_image_params),
				    loadedImages[std::get<1>(load_image_params)]);

	    cur_state = WAITING;
	    break;

	case DISPLAY_IMAGE:
	    cur_state = DISPLAY_IMAGE_INPUT;
	    break;

	case DISPLAY_IMAGE_INPUT:
	    if(!(std::cin >> cur_word)){
    		std::cerr<<"Wrong use of display_image : display_image input_image_name"<<std::endl;
		cur_state = WAITING;

		break;
	    }

	    display_image_input = &loadedImages[cur_word];
	    cur_state = DISPLAY_IMAGE_EXEC;
	    break;

	case DISPLAY_IMAGE_EXEC:
	    ImageUtility::displayImage(*display_image_input);

	    cur_state = WAITING;
	    break;

	case DISPLAY_PIXELS:
	    cur_state = DISPLAY_PIXELS_INPUT;
	    break;

	case DISPLAY_PIXELS_INPUT:
	    std::cin >> cur_word;

	    display_pixels_input = &(pixelResults[cur_word]);

	    cur_state = DISPLAY_PIXELS_EXEC;
	    break;

	case DISPLAY_PIXELS_EXEC:
	    ImageUtility::displayPixels(*display_pixels_input);

	    cur_state = WAITING;
	    break;

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
    	}
    }

    
    return 0;
}
