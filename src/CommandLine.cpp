#include "ImageProcessing.hpp"

#include <tuple>
#include <iostream>
#include <string>
#include <sstream>

enum State{
    UNKNOWN,
    FIND_REGION,
    FIND_REGION_INPUT_IMAGE,
    FIND_REGION_ROW,
    FIND_REGION_COL,
    FIND_REGION_DIST,
    FIND_REGION_READY,
    WAITING,
    ANALYZE_COMMAND,
    QUIT
};


int main(){
    std::tuple<cv::Mat,unsigned int,unsigned int,double> find_region_params;
	
    State cur_state = WAITING;
    std::string quit_str("quit");
    std::string find_region_str("find_region");
    
    std::stringstream commands_stream;
    std::string cur_word;
    
    bool end = false;

    while(!end){
	switch(cur_state){

	case WAITING:
	    if(!(commands_stream >> cur_word))
		end = true;

	    cur_state = ANALYZE_COMMAND;
	    break;

        case ANALYZE_COMMAND:
	    if(cur_word == find_region_str)
		cur_state = FIND_REGION;
	    else{
		std::cerr<<"unknown command: "<<cur_word<<std::endl;
		return -1;
	    }

	    break;

	case FIND_REGION:
	    if(!(commands_stream >> cur_word)){
		std::cerr<<"Wrong parameter for graph command"<<std::endl;
		return -1;
	    }

	    cur_state = FIND_REGION_INPUT_IMAGE;
	    break;
	    
	}
    }

    
    return 0;
}
