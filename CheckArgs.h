//
// Created by galhuta on 27/01/17.
//

#ifndef PLAYWITHSOCKETS_CHECKARGS_H
#define PLAYWITHSOCKETS_CHECKARGS_H

#include <string.h>
#include <iostream>
#include <vector>

class CheckArgs {
public:
    static std::vector<std::string> SeperateArgs(std::string args);

};


#endif //PLAYWITHSOCKETS_CHECKARGS_H
