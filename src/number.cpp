#include "number.h"

Number::Number() {

}

Number::Number(string value, vector<string> errors) {
    this->value = value;
    this->errors = errors;
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

double Number::make_float() {
    isInteger = false;
    if (isBigFloat()) {
        return 0.0;
    } else {
        if (value != "")
            return value_to_float();
        else
            return NULL;
    }
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
    string absolute_value = value;

    if (absolute_value.length() > 10)
        return true;
    else if (absolute_value.length() == 10) {
        string max = "2147483647";
        for (int i = 0; i < 10; i++)
        {
            if (absolute_value.at(i) - '0' < max.at(i) - '0')
                return false;
            else if (absolute_value.at(i) - '0' == max.at(i) - '0') {
                //do nothing
            } else
                return true;
        }
    }
    return false;
}

bool Number::isBigFloat() {
    return false;
}

double Number::value_to_float(int precision) {
    
    double d = 0;
    int sign = 1; // -1 for negatives
    int start = 0;
    bool f = false; //when true, numbers are after the dot
    int p = 1; //count digits after dot
    if (value.at(0) == '-') {
        sign = -1;
        start = 1; //start at index 1
    }
    int decimal_places = 0; //limit precision of floats
    for (int i = start; i < value.size(); i++) {
        if (value.at(i) == '.') {
            f = true;
            continue;
        }
        if (!f) {
            d = d*10 + (value.at(i) - '0');
        } else if (decimal_places < precision) {
            d = d + (value.at(i) - '0') / (p*10.0);
            p*=10;
            decimal_places++;
        }
    }
    if (sign == -1)
        return d * -1;
    else
        return d;
}

void Number::remove_trailing_zeros() {
    int length = value.length();
    for (int i = length - 1; i > 0; i--) {
        if (value.at(i) == '.') {
            value.pop_back();
            isInteger = true;
            dot_count = 0;
            return;
        } else if (value.at(i) != '0') {
            return;
        } else {
            value.pop_back();
        }
    }
}

bool Number::addition_overflow(int a, int b) {
    if ((b > 0) && (a > 2147483647 - b)) 
        return true;
    if ((b < 0) && (a < -2147483647 - b)) 
        return true;
    return false;
}

bool Number::subtraction_overflow(int a, int b) {

    if ((b < 0) && (a > 2147483647 + b)) 
        return true;
    if ((b > 0) && (a < -2147483647 + b)) 
        return true;
    if ((b > 0) && (a > 2147483647 - b)) 
        return false;
    return false;
}

bool Number::multiplication_overflow(int a, int b) {
    int x = a * b;
    if (a != 0 && x / a != b) {
        return true;
    }
    return false;
}

bool Number::is_greater_than(string val1, string val2) {
    
    bool t = true;
    bool f = false;
    if (val1.at(0) == '-' && val2.at(0) != '-') {
        return false;
    }
    if (val1.at(0) != '-' && val2.at(0) == '-') {
        return true;
    }
    if (val1.at(0) == '-' && val2.at(0) == '-') {
        t = false; //opposite rules if two negatives
        f = true;
        val1.erase(0,1);
        val2.erase(0,1);
    }
    if (val1.length() > val2.length()) {
        return t;
    } else if (val1.length() < val2.length()) {
        return f;
    } else {
        for (int i = 0; i < val1.length(); i++) {
            if (val1.at(i) > val2.at(i))
                return t;
            else if (val1.at(i) < val2.at(i))
                return f;
        }
    }
    return false;
}

string Number::big_summation(Number other)
{
    string num1 = value;
    string num2 = other.get_value();
    string state = "++";

    //first is negative
    if (num1.at(0) == '-' && num2.at(0) != '-') {
        state = "-+";
        num1.erase(0,1);
    }
    //second is negative
    if (num1.at(0) != '-' && num2.at(0) == '-') {
        state = "+-";
        num2.erase(0,1);
    }
    //both are negative
    if (num1.at(0) == '-' && num2.at(0) == '-') {
        state = "--";
        num1.erase(0,1);
        num2.erase(0,1);
    }

    bool biggest_absolute_value_is_from_a_negative_number = false; //significant for unary arithmatic
    if (is_greater_than(num1, num2)) {
        swap(num1, num2);
        if (value.at(0) == '-')
            biggest_absolute_value_is_from_a_negative_number = true;
    } else {
        if (other.get_value().at(0) == '-')
            biggest_absolute_value_is_from_a_negative_number = true;
    }
 
    string result = "";
 
    int n1 = num1.length(), n2 = num2.length();
 
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
 
    int carry = 0;
    if (state == "++" || state == "--") {
        for (int i=0; i<n1; i++)
        {
            int sum;
            sum = ((num1[i]-'0')+(num2[i]-'0')+carry);
            result.push_back(sum%10 + '0');
            carry = sum/10;
        }
    
        for (int i=n1; i<n2; i++)
        {
            int sum = ((num2[i]-'0')+carry);
            result.push_back(sum%10 + '0');
            carry = sum/10;
        }
    
        if (carry)
            result.push_back(carry+'0');
    } else {
        for (int i=0; i<n1; i++)
        {
            int dif;
            dif = ((num2[i]-'0')-(num1[i]-'0')) + carry;
            if (dif < 0) {
                carry = -1;
                dif += 10;
            } else {
                carry = 0;
            }
            result.push_back(dif + '0');
        }
    
        for (int i=n1; i<n2; i++)
        {
            int dif = ((num2[i]-'0')+carry);
            if (dif < 0) {
                carry = -1;
                dif += 10;
            } else {
                carry = 0;
            }
            result.push_back(dif + '0');
        }
    }
 
    reverse(result.begin(), result.end());
 
    if (state == "--")
        result = "-"+result;
    if (state == "+-" && biggest_absolute_value_is_from_a_negative_number) 
        result = "-"+result;
    if (state == "-+" && biggest_absolute_value_is_from_a_negative_number)
        result = "-"+result;

    result = remove_leading_zeros(result);

    return result;
}

string Number::remove_leading_zeros(string num_string) {
    for (int i = 0; i < num_string.length(); i++) {
        if (num_string.at(i) == '-') {
            continue;
        }
        if (num_string.at(i) == '0') {
            num_string.erase(i, 1);
            i--;
        } else {
            break;
        }
    }
    return num_string;
}

Number Number::added_to(Number other) {
    if (dot_count ==  0 || other.dot_count == 0) {
        //check if either number is bigger than 2^31-1
        if (isBig() || other.isBig()) {
            return Number(big_summation(other), 0);
        }
        int num1 = make_int();
        int num2 = other.make_int();
        //check if adding the two numbers would be bigger than 2^31-1
        if (addition_overflow(num1, num2)) {
            return Number(big_summation(other), 0);
        }
        return Number(to_string(num1 + num2), 0);
    } else {
        double num1 = make_float();
        double num2 = other.make_float();
        //check if adding the two numbers would be bigger than 2^31-1
        //convert with max precision
        stringstream stream;
        stream << fixed << setprecision(16) << (num1+num2);
        string s = stream.str();
        Number n = Number(s, 1);
        n.remove_trailing_zeros();
        return n;
    }
}

Number Number::subtracted_from(Number other) {
    if (dot_count ==  0 || other.dot_count == 0) {
        //check if either number is bigger than 2^31-1
        if (isBig() || other.isBig()) {
            Number negative_other = Number("-"+other.get_value(), 0);
            return Number(big_summation(negative_other), 0);
        }
        int num1 = make_int();
        int num2 = other.make_int();
        //check if adding the two numbers would be bigger than 2^31-1
        if (subtraction_overflow(num1, num2)) {
            Number negative_other = Number("-"+other.get_value(), 0);
            return Number(big_summation(negative_other), 0);;
        }
        return Number(to_string(num1 - num2), 0);
    } else {
        double num1 = make_float();
        double num2 = other.make_float();
        //TODO: check if numbers overflow
        //convert with max precision
        stringstream stream;
        stream << fixed << setprecision(16) << (num1-num2);
        string s = stream.str();
        Number n = Number(s, 1);
        n.remove_trailing_zeros();
        return n;
    }
    
}


Number Number::multiplied_by(Number other) {
    if (dot_count ==  0 || other.dot_count == 0) {
        int num1 = make_int();
        int num2 = other.make_int();
        if (multiplication_overflow(num1, num2)) {
            cout << "The two numbers multiplied together are too big: TODO handle big numbers." << endl;
            return Number("0", 0);
        }
        return Number(to_string(num1 * num2), 0);
    } else {
        double num1 = make_float();
        double num2 = other.make_float();
        //convert with max precision
        stringstream stream;
        stream << fixed << setprecision(16) << (num1*num2);
        string s = stream.str();
        Number n = Number(s, 1);
        n.remove_trailing_zeros();
        return n;
    }
}

Number Number::divided_by(Number other) {
    double num1 = make_float();
    double num2 = other.make_float();
    //convert with max precision
    stringstream stream;
    stream << fixed << setprecision(16) << (num1/num2);
    string s = stream.str();
    Number n = Number(s, 1);
    n.remove_trailing_zeros();
    return n;
}

Number Number::power_of(Number other) {
    if ((dot_count ==  0 || other.dot_count == 0) && other.get_value().at(0) != '-') {
        int num1 = make_int();
        int num2 = other.make_int();
        if (multiplication_overflow(num1, num2)) {
            cout << "The numbers are too big: TODO handle big numbers." << endl;
            return Number("0", 0);
        }
        return Number(to_string(static_cast<int>(pow(num1, num2))), 0);
    } else {
        float num1 = make_float();
        float num2 = other.make_float();
        //convert with max precision
        stringstream stream;
        stream << fixed << setprecision(16) << static_cast<double>(pow(num1, num2));
        string s = stream.str();
        Number n = Number(s, 1);
        n.remove_trailing_zeros();
        return n;
    }

}

vector<string> Number::get_errors() {
    return errors;
}