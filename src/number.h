#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
using namespace std;

//The Number class stores numbers as a string. 
//The TT_INT Token may ALSO store the Integer value if it is smaller than 32-bits
//The string could represent a "default value," a feature very few languages have!

class Number {
    private:
        string value;
        int dot_count;
        bool isInteger;
        int start;
        int end;
    public:
        Number();
        Number(string num_string, int dot_count);
        void set_value(string);
        void set_dot_count(int);
        string get_value();
        int get_dot_count();
        int make_int();
        bool isInt();
        bool isBig();
        double string_to_float();
        Number set_position(int start, int end);
        Number added_to(Number other);
        bool addition_overflow(int, int);
};

#endif