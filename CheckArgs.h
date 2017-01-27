//
// Created by galhuta on 27/01/17.
//

#ifndef PLAYWITHSOCKETS_CHECKARGS_H
#define PLAYWITHSOCKETS_CHECKARGS_H

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#define TRIP_ARGS_NUMBER 8
#define CLIENT_ARGS_NUMBER 5
#define TAXI_ARGS_NUMBER 4
#define OBSTACLE_ARGS_NUMBER 2

class CheckArgs {
public:
    static std::vector<std::string> SeperateArgs(std::string args,std::string seprator);
    static bool isMartialStatus(std::string martialInput);
    static bool isCarManufacturer(std::string manufacturerInput);
    static bool isColor(std::string colorInput);
    static int countChar(std::string args,char whatToCount);
    static std::vector<std::string> checkIntgerInput(std::string input,int numberOfArgs);
    static std::vector<std::string> checkClient(std::string input);
    static std::vector<std::string> checkTaxiArguments(std::string input);
    static std::vector<std::string> checkObstacleArguments(std::string input);
    static std::vector<std::string> checkTripInfoArguments(std::string input);

};


#endif //PLAYWITHSOCKETS_CHECKARGS_H
