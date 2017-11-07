#include "ImageProcessing.hpp"

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
    FIND_REGION,
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

    //parameters for executing find_region
    std::tuple<cv::Mat,unsigned int,unsigned int,double> find_region_params;
    std::tuple<std::string,std::string> load_image_params;

    // used in the below state machine
    State cur_state = WAITING;

    std::string quit_str("quit");
    std::string load_image_str("load_image");
    std::string find_region_str("find_region");
    
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
    	    else if(cur_state == load_image_str)
    		cur_state = LOAD_IMAGE;
    	    else{
    		std::cerr<<"unknown command: "<<cur_word<<std::endl;
    		cur_state = WAITING;
    	    }

    	    break;

    	case LOAD_IMAGE:
	    cur_state = LOAD_IMAGE_INPUT;
	    break;

	case LOAD_IMAGE_INPUT:
    	    if(!(std::cin >> cur_word)){
    		std::cerr<<"Wrong use of load image : load_image input_filename output_name"<<std::endl;
		cur_state = WAITING;
	    }

	    load_image_params.get<0> = cur_word;
	    cur_state = LOAD_IMAGE_OUTPUT;

	    break;
	    
	case LOAD_IMAGE_OUTPUT:
    	    if(!(std::cin >> cur_word)){
    		std::cerr<<"Wrong use of load image : load_image input_filename output_name"<<std::endl;
		cur_state = WAITING;
	    }

	    load_image_params.get<1> = cur_word;
	    cur_state = LOAD_IMAGE_EXEC;

	    break;

	case LOAD_IMAGE_EXEC:
	    

    	case FIND_REGION:
    	    if(!(std::cin >> cur_word)){
    		std::cerr<<"find_region : wrong number of parameters"<<std::endl;
    		cur_state = WAITING;
    		break;
    	    }

    	    cur_state = FIND_REGION_INPUT_IMAGE;
    	    break;
	    
    	}
    }

    
    return 0;
}
