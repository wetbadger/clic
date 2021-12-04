#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include <string>
#include <cctype>
#include <math.h>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

//The Number class stores numbers as a string. 
//The TT_INT Token may ALSO store the Integer value if it is smaller than 32-bits
//The string could represent a "default value," a feature very few languages have!

class Number {
    private:
        string value;
        int dot_count;
        bool isInteger;

        bool isBig();
        
        //TODO: Read this https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html
        double make_float();
        bool isBigFloat();
        double value_to_float(int precision = 16);
        void remove_trailing_zeros();
        string remove_leading_zeros(string);

        bool is_greater_than(string, string);
        string big_summation(Number);


    public:
        Number();
        Number(string num_string, int dot_count);
        void set_value(string);
        void set_dot_count(int);
        string get_value();
        int get_dot_count(); 

        int make_int();
        bool isInt();

        Number added_to(Number other);
        Number subtracted_from(Number other);
        Number multiplied_by(Number other);
        Number divided_by(Number other);
        Number power_of(Number other);
        bool addition_overflow(int, int);
        bool subtraction_overflow(int, int);
        bool multiplication_overflow(int, int);
};

#endif