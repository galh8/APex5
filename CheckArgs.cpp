//
// Created by galhuta on 27/01/17.
//

#include "CheckArgs.h"

/**
 * @param args - the input.
 * @param separator - the char that separate the different inputs.
 * @return - a vector with the different inputs.
 */
std::vector<std::string> CheckArgs::SeperateArgs(std::string args,std::string separator) {
    char *str = new char[args.length()+1];
    char *currentSeparator = new char[separator.length()+1];
    std::strcpy (currentSeparator, separator.c_str());
    std::strcpy (str, args.c_str());
    std::vector<std::string> argsAfterSeparation;
    char* part = std::strtok (str,currentSeparator);
    while (part != NULL)
    {
        argsAfterSeparation.push_back(part);
        part = strtok (NULL,currentSeparator);
    }

    delete[] str;
    delete[] currentSeparator;

    return argsAfterSeparation;
}

/**
 *
 * @param martialInput - the martial input we got.
 * @return if it is an actual martial status.
 */
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

/**
 *
 * @param manufacturerInput - the CarManufacturer input we got.
 * @return if it is an actual CarManufacturer.
 */
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

/**
 *
 * @param colorInput - the color input we got.
 * @return if it is an actual color.
 */
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

/**
 *
 * @param s  - string.
 * @return - if the string is a number.
 */
static bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

/**
 *
 * @param s - a number.
 * @return - if the number is non negative.
 */
static bool isNonNegativeInteger(std::string s) {
    if(!is_number(s)) {
        return false;
    }
    int input = stoi(s);
    return(input >= 0);
}

/**
 * @param args - the string we want to count in.
 * @param whatToCount
 * @return how many times what to count was.
 */
int CheckArgs::countChar(std::string args,char whatToCount) {
    int count = 0;

    for (int i = 0; i < args.size(); i++)
        if (args[i] == whatToCount) count++;

    return count;
}

/**
 *
 * @param input - the input of the client.
 * @return - a vector of the input - if the input is correct.
 */
std::vector<std::string> CheckArgs::checkClient(std::string input) {
    std::vector<std::string> argsAfterSeperation = SeperateArgs(input,",");
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

/**
 *
 * @param input - taxi arguments.
 * @return - - a vector of the input - if the input is correct.
 */
std::vector<std::string> CheckArgs::checkTaxiArguments(std::string input) {
    std::vector<std::string> argsAfterSeperation = SeperateArgs(input,",");
    int i;
    unsigned long size = argsAfterSeperation.size();
    //checks if there are the supposed number of args.
    if (size != TAXI_ARGS_NUMBER) {
        return std::vector<std::string>();
    }

    //if there were more separators than supposed to be.
    int numberOfSeparator = countChar(input,',');
    if (numberOfSeparator > (TAXI_ARGS_NUMBER - 1) ) {
        return std::vector<std::string>();
    }

    //checks if the first two arguments are integers
    for (i = 0; i < 2; i++) {
        if (!(isNonNegativeInteger(argsAfterSeperation.at(i)))) {
            return std::vector<std::string>();
        }
    }

    //checks if the third argument is CarManufacturer.
    if (!(isCarManufacturer(argsAfterSeperation.at(i)))) {
        return std::vector<std::string>();
    }

    ++i;

    //checks if the third argument is Color.
    if (!(isColor(argsAfterSeperation.at(i)))) {
        return std::vector<std::string>();
    }

    return argsAfterSeperation;
}

/**
 *
 * @param input - integer arguments(Trip or obstacle for now).
 * @return - a vector of the input - if the input is correct.
 */
std::vector<std::string> CheckArgs::checkIntgerInput(std::string input,int argsNum) {
    std::vector<std::string> argsAfterSeperation = SeperateArgs(input,",");
    int i;
    unsigned long size = argsAfterSeperation.size();
    //checks if there are the supposed number of args.
    if (size != argsNum) {
        return std::vector<std::string>();
    }

    //if there were more separators than supposed to be.
    int numberOfSeparator = countChar(input,',');
    if (numberOfSeparator > (argsNum - 1) ) {
        return std::vector<std::string>();
    }

    //checks if the first two arguments are integers
    for (i = 0; i < argsNum; i++) {
        if (!(isNonNegativeInteger(argsAfterSeperation.at(i)))) {
            return std::vector<std::string>();
        }
    }

    return argsAfterSeperation;
}


/**
 *
 * @param input - the input.
 * @return - a vector of the input - if the input is correct.
 */
std::vector<std::string> CheckArgs::checkTripInfoArguments(std::string input) {
    return checkIntgerInput(input,TRIP_ARGS_NUMBER);
}

/**
 *
 * @param input - the input.
 * @return - a vector of the input - if the input is correct.
 */
std::vector<std::string> CheckArgs::checkObstacleArguments(std::string input) {
    return checkIntgerInput(input,OBSTACLE_ARGS_NUMBER);
}








