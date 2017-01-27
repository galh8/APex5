//
// Created by galhuta on 27/01/17.
//

#include "CheckArgs.h"

std::vector<std::string> CheckArgs::SeperateArgs(std::string args) {

    return std::vector<std::string>();
}

bool CheckArgs::isMartialStatus(std::string martialInput) {

    if(strcmp(martialInput.c_str(),"H")==0) {
        return true;
    }else if(strcmp(martialInput.c_str(),"M")==0) {
        return true;
    }else if(strcmp(martialInput.c_str(),"W")==0) {
        return true;
    }else if(strcmp(martialInput.c_str(),"D")==0) {
        return true;
    }
    return false;
}

bool CheckArgs::isCarManufacturer(std::string manufacturerInput) {
    if(strcmp(manufacturerInput.c_str(),"H")==0) {
        return true;
    }else if(strcmp(manufacturerInput.c_str(),"S")==0) {
        return true;
    }else if(strcmp(manufacturerInput.c_str(),"T")==0) {
        return true;
    }else if(strcmp(manufacturerInput.c_str(),"F")==0) {
        return true;
    }
    return false;
}

bool CheckArgs::isColor(std::string colorInput) {
    if(strcmp(colorInput.c_str(),"R")==0) {
        return true;
    }else if(strcmp(colorInput.c_str(),"B")==0) {
        return true;
    }else if(strcmp(colorInput.c_str(),"G")==0) {
        return true;
    }else if(strcmp(colorInput.c_str(),"P")==0) {
        return true;
    }else if(strcmp(colorInput.c_str(),"W")==0) {
        return true;
    }
    return false;
}

