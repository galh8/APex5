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
    static std::vector<std::string> SeperateArgs(std::string args,std::string seprator);
    static bool isMartialStatus(std::string martialInput);
    static bool isCarManufacturer(std::string manufacturerInput);
    static bool isColor(std::string colorInput);
    static bool checkClient(std::string input);
};


#endif //PLAYWITHSOCKETS_CHECKARGS_H
