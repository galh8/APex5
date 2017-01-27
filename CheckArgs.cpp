//
// Created by galhuta on 27/01/17.
//

#include "CheckArgs.h"


std::vector<std::string> CheckArgs::SeperateArgs(std::string args,std::string separator,int argsNumber) {
    char *str = new char[args.length()+1];
    char *currentSeparator = new char[separator.length()+1];
    std::strcpy (currentSeparator, separator.c_str());
    std::strcpy (str, args.c_str());
    std::vector<std::string> argsAfterSeperation;
    char* part = std::strtok (str,currentSeparator);
    while (part != NULL)
    {
        argsAfterSeperation.push_back(part);
        part = strtok (NULL,currentSeparator);
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
    int input = stoi(s);
    return(input >= 0);
}

std::vector<std::string> CheckArgs::checkClient(std::string input) {
    std::vector<std::string> argsAfterSeperation = SeperateArgs(input,",",CLIENT_ARGS_NUMBER);
    int i;
    unsigned long size = argsAfterSeperation.size();
    //checks if there are the supposed number of args.
    if (size != CLIENT_ARGS_NUMBER) {
        return std::vector<std::string>();
    }

    //if there were more separators than supposed to be.
    int numberOfSeparator = countChar(input,',');
    if (numberOfSeparator > (CLIENT_ARGS_NUMBER - 1) ) {
        return std::vector<std::string>();
    }

    //checks if the first two arguments are integers
    for (i = 0; i < 2; i++) {
        if (!(isNonNegativeInteger(argsAfterSeperation.at(i)))) {
            return std::vector<std::string>();
        }
    }
    //checks if the third argument is martial status.
    if (!(isMartialStatus(argsAfterSeperation.at(i)))) {
        return std::vector<std::string>();
    }

    //checks if the last two arguments are integers
    for (i = 3; i < size; i++) {
        if (!(isNonNegativeInteger(argsAfterSeperation.at(i)))) {
            return std::vector<std::string>();
        }
    }

    return argsAfterSeperation;
}

int CheckArgs::countChar(std::string args,char whatToCount) {
    int count = 0;

    for (int i = 0; i < args.size(); i++)
        if (args[i] == whatToCount) count++;

    return count;
}

