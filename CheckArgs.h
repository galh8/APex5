//
// Created by galhuta on 27/01/17.
//

#ifndef PLAYWITHSOCKETS_CHECKARGS_H
#define PLAYWITHSOCKETS_CHECKARGS_H

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#define CLIENT_ARGS_NUMBER 5

class CheckArgs {
public:
    static std::vector<std::string> SeperateArgs(std::string args,std::string seprator,int argsNum);
    static bool isMartialStatus(std::string martialInput);
    static bool isCarManufacturer(std::string manufacturerInput);
    static bool isColor(std::string colorInput);
    static std::vector<std::string> checkClient(std::string input);
    static int countChar(std::string args,char whatToCount);
};


#endif //PLAYWITHSOCKETS_CHECKARGS_H
