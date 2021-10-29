#include "result.h"

Result::Result() {

}

Result::~Result() {

}

string Result::record(Result result) {
    return result.value;
}

Result Result::success(string) {
    return Result();
}

Result Result::failure(string) {
    return Result();

}