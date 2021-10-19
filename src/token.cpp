#include "token.h"
#include <iostream>

Token::Token() {
    
}

void Token::set(TT tt) {
    type = tt;
}

string Token::to_string() {
    switch (type) {
        case TT_END:
            return "END";
        case TT_PLUS:
            return "add";
        case TT_MINUS:
            return "subtract";
        case TT_MUL:
            return "multiply";
        case TT_DIV:
            return "divide";
        case TT_POW:
            return "exponent";
        case TT_LBRAK:
            return "[";
        case TT_RBRAK:
            return "]";
        case TT_LPAREN:
            return "(";
        case TT_RPAREN:
            return ")";
        case TT_INT:
            return "int:" + std::to_string(int_value);
        case TT_FLOAT:
            return "float:" + value;
        case TT_BOOL:
            return "bool:" + std::to_string(bool_value);
        case TT_NULL:
            return "null";
    }
    return "undefined";
}

void Token::set_value(int value) {
    this->int_value = value;
}

void Token::set_value(bool value) {
    this->bool_value = value;
}
void Token::set_value(string value) {
    this->value = value;
}
/*
void Token::set_value(void* value) {
    this->value = value;
}
*/
int Token::get_int_value() {
    return int_value;
}

bool Token::get_bool_value() {
    return bool_value;
}

string Token::get_value() {
    return value;
}

string Token::get_name() {
    return name;
}

void Token::set_type(TT type) {
    this->type = type;
}

TT Token::get_type() {
    return type;
}