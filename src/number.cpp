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
        if (value != "")
            return stoi(value);
        else
            return NULL;
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

bool Number::addition_overflow(int a, int b) {
    int overflow;
    int max = 2147483647;
    if (a^b < 0) 
        overflow=0; /* opposite signs can't overflow */
    else if (a>0) 
        overflow=(b>max-a);
    else 
        overflow=(b<max-a);
    return overflow;
}

bool Number::multiplication_overflow(int a, int b) {
    int x = a * b;
    if (a != 0 && x / a != b) {
        return true;
    }
    return false;
}

Number Number::added_to(Number other) {
    //check if either number is bigger than 2^31-1
    if (isBig() || other.isBig()) {
        cout << "Number too big: TODO handle big numbers." << endl;
        return Number("0", 0);
    }
    int num1 = make_int();
    int num2 = other.make_int();
    //check if adding the two numbers would be bigger than 2^31-1
    if (addition_overflow(num1, num2)) {
        cout << "The two numbers added together are too big: TODO handle big numbers." << endl;
        return Number("0", 0);
    }
    return Number(to_string(num1 + num2), 0);
}

Number Number::subtracted_from(Number other) {
    //check if either number is bigger than 2^31-1
    if (isBig() || other.isBig()) {
        cout << "Number too big: TODO handle big numbers." << endl;
        return Number("0", 0);
    }
    int num1 = make_int();
    int num2 = other.make_int();
    //check if adding the two numbers would be bigger than 2^31-1
    if (addition_overflow(num1, num2)) {
        cout << "The two numbers added together are too big: TODO handle big numbers." << endl;
        return Number("0", 0);
    }
    return Number(to_string(num1 - num2), 0);
}


Number Number::multiplied_by(Number other) {
    int num1 = make_int();
    int num2 = other.make_int();
    if (multiplication_overflow(num1, num2)) {
        cout << "The two numbers multiplied together are too big: TODO handle big numbers." << endl;
        return Number("0", 0);
    }
    return Number(to_string(num1 * num2), 0);
}

Number Number::power_of(Number other) {
    int num1 = make_int();
    int num2 = other.make_int();
    if (multiplication_overflow(num1, num2)) {
        cout << "The numbers are too big: TODO handle big numbers." << endl;
        return Number("0", 0);
    }

    return Number(to_string(pow(num1, num2)), 0);

}