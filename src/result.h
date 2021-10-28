#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include "error.h"
using namespace std;

class Result
{
private:
    string value = NULL;
    Except error;
public:
    Result();
    ~Result();
    string record(Result);
    Result success(string);
    Result failure(string);
};

#endif