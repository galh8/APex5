//
// Created by galhuta on 27/01/17.
//

#include "CheckArgs.h"

std::vector<std::string> CheckArgs::SeperateArgs(std::string args,std::string separator) {
    char *str = new char[args.length()+1];
    char *currentSeparator = new char[separator.length()+1];
    std::strcpy (currentSeparator, separator.c_str());
    std::strcpy (str, args.c_str());
    std::vector<std::string> argsAfterSeperation;
    char* part = std::strtok (str,currentSeparator);
    argsAfterSeperation.push_back(part);
    while (part != NULL)
    {
        part = strtok (NULL,currentSeparator);
        argsAfterSeperation.push_back(part);
    }

    delete[] str;
    delete[] currentSeparator;
    return argsAfterSeperation;
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
static bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

static bool isNonNegativeInteger(std::string s) {
    if(!is_number(s)) {
        return false;
    }
    return(atoi(s)>=0);
}//