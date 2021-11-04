#ifndef RESULT_H
#define RESULT_H

#include <iostream>
#include <optional>
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
    string _register(Result);
    Result success(string);
    Result failure(string);
    string get_value();
};

#endif