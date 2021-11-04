#include "result.h"

Result::Result() {

}

Result::~Result() {

}

string Result::_register(Result result) {
    //if (result.error) {

    //} else {
    return result.get_value();
}

Result Result::success(string) {
    return Result();
}

Result Result::failure(string) {
    return Result();

}

string Result::get_value() {
    return value;
}