#include "number.h"

Number::Number() {

}

Number::Number(string num_string, int dot_count) {
    set_value(num_string);
    set_dot_count(dot_count);
}

void Number::set_value(string value) {
    this->value = value;
}

void Number::set_dot_count(int count) {
    this->dot_count = count;
}

string Number::get_value() {
    return value;
}

int Number:: get_dot_count() {
    return dot_count;
}

int Number::make_int() {

    if (isBig()) {
        isInteger = false;
        return 0;
    } else {
        isInteger = true;
        return stoi(value);
    }
}

bool Number::isInt() {
    return isInteger;
}

bool Number::isBig() {
    //check if number is larger than 2147483647 (without converting to an int)
    if (value.length() > 10)
        return true;
    else if (value.length() == 10) {
        string max = "2147483647";
        for (int i = 0; i < 10; i++)
        {
            if (value.at(i) - '0' < max.at(i) - '0')
                return false;
            else if (value.at(i) - '0' == max.at(i) - '0')
                return true;
        }
    }
    return false;
}

double Number::string_to_float() {
    double d = 0;
    bool f = false; //when true, numbers are after the dot
    int p = 1; //count digits after dot
    for (int i = 0; i < value.size(); i++) {
        if (value.at(i) == '.') {
            f = true;
            continue;
        }
        if (!f) {
            d = d*10 + (value.at(i) - '0');
        } else {
            d = d + (value.at(i) - '0') / (p*10.0);
            p*=10;
        }
    }
    return d;
}